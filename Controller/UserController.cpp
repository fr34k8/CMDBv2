#include "UserController.h"
#include "../Common/DBCommon.h"
#include "../Model/JsonModel.h"
#include "../Model/CollectorModel.h"
#include "../Model/UserModel.h"

CUserController::CUserController(void)
{
	m_strTableName = TBL_USER;
}

CUserController::~CUserController(void)
{
	ClearMapUserInfo();
}

void CUserController::ClearMapUserInfo()
{
	HRAccountDomain2UserInfoMap::iterator it = m_mapAccountDomain2UserInfoMap.begin();
	while(it != m_mapAccountDomain2UserInfoMap.end())
	{
		delete (*it).second;
		it++;
	}
}

CUserModel* CUserController::GetUserInfoByAccountDomain(const std::string &strAccountDomain)
{
	CUserModel* pUserInfo = NULL;
	HRAccountDomain2UserInfoMap::iterator it = m_mapAccountDomain2UserInfoMap.find(strAccountDomain);
	
	if (it != m_mapAccountDomain2UserInfoMap.end())
	{
		pUserInfo = (*it).second;
	}
	else
	{
		pUserInfo = new CUserModel();		
		m_mapAccountDomain2UserInfoMap[strAccountDomain] = pUserInfo;
	}

	return pUserInfo;
}

void CUserController::CompareFullData(CCollectorModel *pCollectorInfo, char *pData)
{
	CJsonModel objJsonModel; 
	string strJsonData = "";

	if (NULL != pData)
		strJsonData = pData;
	
	string strEmail;
	string strAccountDomain;
	string strOrgDepartment;
	string strDirtyTable;

	strDirtyTable = pCollectorInfo->GetDirtyTableName();

	try
	{
		Json::Value jRootValue;
		jRootValue = objJsonModel.parseValueRootJson(strJsonData);
		
		if (!jRootValue.isNull() && jRootValue.isArray())
		{

			for(Json::Value::UInt index = 0 ; index < jRootValue.size(); index ++)
			{
				strEmail = strAccountDomain = strOrgDepartment = "";
				
				if (!jRootValue[index]["email"].isNull())
				{
					strEmail		 = jRootValue[index]["email"].asString();
					strAccountDomain = CUtilities::GetAccountDomainByEmail(strEmail);
				}
									
				if (!jRootValue[index]["department"].isNull())
					strOrgDepartment = jRootValue[index]["department"].asString();
				
				if (strAccountDomain == "")
					continue;
				

				if (IsMatchUser(strAccountDomain))
				{
					cout << "match" << endl;
					cout << "email:" << strEmail << endl;
					cout << "account:" << strAccountDomain << endl;
					BSONObj boOrgUserInfo = BSON("$set" << BSON("department" << strOrgDepartment << "is_match" << MATCH));
					Query qCondition = QUERY("username" << strAccountDomain);

					cout << "data:" << boOrgUserInfo.toString();
					cout << "condition:" << qCondition.toString();

					Update(boOrgUserInfo, qCondition);

					PushDirtyUserOrgChart(strDirtyTable, strAccountDomain, strOrgDepartment, MATCH);
				}
				else
				{
					//cout << "not match" << endl;
					PushDirtyUserOrgChart(strDirtyTable, strAccountDomain, strOrgDepartment, NOTMATCH);
				}
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CUserController", "CompareData","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(strLog);
	}
}

bool CUserController::IsMatchUser(const string& strAccountDomain)
{
	Query qCondition = QUERY("username" << strAccountDomain);
	return IsExisted(qCondition);
}

void CUserController::PushDirtyUserOrgChart(const string& strDirtyTable, 
											   const string& strAccountDomain, 
											   const string& strOrgDepartment, 
											   int iFlag)
{
	BSONObj boDataInfo = BSON("account" << strAccountDomain << "department" << strOrgDepartment << "is_match" << iFlag);
	BSONObj boCondition = BSON("account" << strAccountDomain);
	Insert(strDirtyTable, boDataInfo, boCondition);
}

bool CUserController::FindOperatingUser(std::auto_ptr<DBClientCursor> &ptrCursor)
{
	bool bResult = Find(ptrCursor,
		QUERY(
			"deleted" << 0)
		);
	return bResult;
}