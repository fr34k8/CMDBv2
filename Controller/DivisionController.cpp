#include "DivisionController.h"
#include "../Common/DBCommon.h"
#include "../Model/JsonModel.h"
#include "../Model/CollectorModel.h"
#include "../Model/DivisionDefenseInfoModel.h"
#include "../Model/DivisionModel.h"

CDivisionController::CDivisionController(void)
{
	m_strTableName = TBL_DIVISION;
}

CDivisionController::~CDivisionController(void)
{
	ClearMapDivisionDefenseInfo();
	ClearMapDivisionInfo();
}

void CDivisionController::ClearMapDivisionDefenseInfo()
{
	HRCode2DivisionDefenseInfoMap::iterator it = m_mapHRCode2DivisionDefenseInfo.begin();
	while(it != m_mapHRCode2DivisionDefenseInfo.end())
	{
		delete (*it).second;
		it++;
	}
}

void CDivisionController::ClearMapDivisionInfo()
{
	HRCode2DivisionInfoMap::iterator it = m_mapHRCode2DivisionInfoMap.begin();
	while(it != m_mapHRCode2DivisionInfoMap.end())
	{
		delete (*it).second;
		it++;
	}
}

void CDivisionController::CompareFullData(CCollectorModel *pCollectorInfo, char *pData)
{
	CJsonModel objJsonModel; 
	string strJsonData = "";

	if (NULL != pData)
		strJsonData = pData;
	
	string strOrgId;
	string strOrgCode;
	string strParentCode;
	string strCreatedAt;
	string strLastUpdated;
	string strDivisionAlias;
	int iIsVirtual;

	bool bActive;

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
				strOrgId = strOrgCode = strParentCode = strDivisionAlias = "";
				strCreatedAt = strLastUpdated = "";
				iIsVirtual = 0;

				//--------orgID---------//
				if (!jRootValue[index]["orgID"].isNull())
					strOrgId = jRootValue[index]["orgID"].asString();
				//--------orgCode---------//
				if (!jRootValue[index]["orgCode"].isNull())
					strOrgCode = jRootValue[index]["orgCode"].asString();
				//--------parentCode---------//
				if (!jRootValue[index]["parentCode"].isNull())
					strParentCode = jRootValue[index]["parentCode"].asString();
				//--------createdDate---------//
				if (!jRootValue[index]["createdDate"].isNull())
					strCreatedAt = jRootValue[index]["createdDate"].asString();
				//--------lastUpdated---------//
				if (!jRootValue[index]["lastUpdated"].isNull())
					strLastUpdated = jRootValue[index]["lastUpdated"].asString();
				//--------active---------//
				if (!jRootValue[index]["active"].isNull())
					bActive = jRootValue[index]["active"].asBool();

				if (strOrgCode == "" && strOrgId == "")
					continue;
				
				if (!bActive)
					continue;
				
				cout << "org code:" << strOrgCode << "parent code:" << strParentCode << endl;
				strDivisionAlias = GetDivisionAlias(strOrgCode, strParentCode);
				
				cout << "private division alias: " << strDivisionAlias << endl;
				if (strDivisionAlias != strOrgCode)
					iIsVirtual = 1;

				if (IsMatchDivisionAlias(strOrgCode))
				{
					BSONObj boOrgDivisionInfo = BSON("$set" << BSON("hr_id" << strOrgId << "hr_code" << strOrgCode <<
																	"hr_parent_code" << strParentCode << "hr_created_at" << strCreatedAt <<
																	"hr_last_updated" << strLastUpdated << "alias" << strDivisionAlias <<
																	"is_virtual" << iIsVirtual));
					//Query qCondition = QUERY("alias" << strOrgCode << "status" << 1 << "deleted" << 0);
					Query qCondition = QUERY("mis_alias" << strOrgCode << "status" << ACTIVE << "deleted" << UNDELETED_FLAG);
					Update(boOrgDivisionInfo, qCondition);

					PushDirtyDivisionOrgChart(strDirtyTable, strOrgCode, strOrgId, strParentCode, MATCH);
				}
				else
				{
					PushDirtyDivisionOrgChart(strDirtyTable, strOrgCode, strOrgId, strParentCode, NOTMATCH);
				}
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CDivisionController", "CompareData","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

bool CDivisionController::IsMatchDivisionAlias(std::string strOrgCode)
{
	//Query qCondition = QUERY("alias" << strOrgCode << "status" << 1 << "deleted" << 0);
	Query qCondition = QUERY("mis_alias" << strOrgCode << "status" << ACTIVE << "deleted" << UNDELETED_FLAG);
	return IsExisted(qCondition);
}

void CDivisionController::PushDirtyDivisionOrgChart(std::string strDirtyTable, std::string strOrgCode, std::string strOrgId, std::string strParentCode, int iFlag)
{
	BSONObj boDataInfo = BSON("orgId" << strOrgId << "orgCode" << strOrgCode << "parentCode" << strParentCode << "is_match" << iFlag);
	BSONObj boCondition = BSON("orgId" << strOrgId);
	Insert(strDirtyTable, boDataInfo, boCondition);
}

void CDivisionController::CompareChangeData(CCollectorModel *pCollectorInfo, char *pData)
{
	CJsonModel objJsonModel; 
	string strJsonData = "";

	if (NULL == pData)
		return;

	strJsonData = pData;
	
	string strOrgId;
	string strOrgCode;
	string strDirtyTable;
	string strHRCode;

	string strParentCode;
	string strCreatedAt;
	string strLastUpdated;
	string strDivisionAlias;	
	int iIsVirtual;
	int iStatus;

	bool bActive = true;
	int iActionType;

	strDirtyTable = pCollectorInfo->GetDirtyTableName();
	CDivisionDefenseInfoModel *pDivisionDefenseModel;
	CDivisionModel *pDivisionModel;

	time_t now;
	now = time(NULL);
	
	string strLog;
	try
	{
		Json::Value jRootValue;
		jRootValue = objJsonModel.parseValueRootJson(strJsonData);
		
		if (!jRootValue.isNull() && jRootValue.isArray())
		{
			for(Json::Value::UInt index = 0 ; index < jRootValue.size(); index ++)
			{
				
				strOrgId = strOrgCode = strHRCode = "";
				strParentCode = strDivisionAlias = "";
				strCreatedAt = strLastUpdated = "";
				iIsVirtual = 0;
				iActionType = iStatus = UNKNOWN;
				
				try
				{
					if (!jRootValue[index]["orgID"].isNull())
						strOrgId = jRootValue[index]["orgID"].asString();
					if (!jRootValue[index]["orgCode"].isNull())
						strOrgCode = jRootValue[index]["orgCode"].asString();
					//--------parentCode---------//
					if (!jRootValue[index]["parentCode"].isNull())
						strParentCode = jRootValue[index]["parentCode"].asString();
					//--------createdDate---------//
					if (!jRootValue[index]["createdDate"].isNull())
						strCreatedAt = jRootValue[index]["createdDate"].asString();
					//--------lastUpdated---------//
					if (!jRootValue[index]["lastUpdated"].isNull())
						strLastUpdated = jRootValue[index]["lastUpdated"].asString();
				
					if (!jRootValue[index]["active"].isNull())
						bActive = jRootValue[index]["active"].asBool();

					if (strOrgCode == "" && strOrgId == "")
						continue;
					
					//Get Division alias
					cout << "org code:" << strOrgCode << "parent code:" << strParentCode << endl;
					strDivisionAlias = GetDivisionAlias(strOrgCode, strParentCode);					
					cout << "private division alias: " << strDivisionAlias << endl;
					
					if (strDivisionAlias != strOrgCode)
						iIsVirtual = 1;

					pDivisionDefenseModel = GetDivisionDefenseInfoByHRCode(strOrgCode);	
					auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
					auto_ptr<DBClientCursor> ptrSecondResultCursor = auto_ptr<DBClientCursor>();

					//Query qCondition = QUERY("hr_id" << strOrgId << "status" << 1 << "deleted" << 0);
					Query qCondition = QUERY("hr_id" << strOrgId << "deleted" << UNDELETED_FLAG);
					ptrResultCursor = Find(qCondition);

					if (ptrResultCursor.get() == NULL)
					{
						continue;
					}

					BSONObj oDivisionInfo;

					if (!ptrResultCursor->more())
					{
						// New Division
						if (bActive)
						{
							iActionType = ACTION_INSERT;

							pDivisionModel = GetDivisionInfoByHRCode(strOrgCode);
							pDivisionModel->SetHRId(strOrgId);
							pDivisionModel->SetHRCode(strOrgCode);
							pDivisionModel->SetStatus(ACTIVE);
							//--------- New Feature -----------//
							pDivisionModel->SetAlias(strDivisionAlias);
							pDivisionModel->SetMISAlias(strOrgCode);
							pDivisionModel->SetHRCreatedAt(strCreatedAt);
							pDivisionModel->SetHRLastUpdated(strLastUpdated);
							pDivisionModel->SetHRParentCode(strParentCode);
							pDivisionModel->SetIsVirtual(iIsVirtual);

							//Insert New Division
							SaveDivisionInfo(pDivisionModel);

							ptrSecondResultCursor = Find(qCondition);
							if ((ptrSecondResultCursor.get() != NULL) && (ptrSecondResultCursor->more()))
							{
								oDivisionInfo = ptrSecondResultCursor->nextSafe();
							}
						}
					}
					else
					{
						oDivisionInfo = ptrResultCursor->nextSafe();
					}
					
					if (oDivisionInfo.isEmpty())
						continue;
					
					strHRCode = oDivisionInfo.getStringField("hr_code");
					cout << "HRCode:" << strHRCode << endl;
					cout << "Active:" << bActive << endl;

					iStatus = oDivisionInfo.getIntField("status");
					//Found & Delete
					if ((!bActive && (iStatus == ACTIVE)) || (bActive && (iStatus == INACTIVE)))
					{
						iActionType = ACTION_UPDATE;
					}
					//Found & Update
					else 
					{
						if (strHRCode != strOrgCode)
						{
							iActionType = ACTION_UPDATE;
						}
					}
					
					cout << "Action Type:" << iActionType << endl;
					if (iActionType == UNKNOWN)
						continue;

					BSONElement beDivisionId;
					//oDivisionInfo.getObjectID(beDivisionId);
					beDivisionId = oDivisionInfo["_id"];
					
					//-----Update division virtual -----//
					cout << "update virtual:" << strOrgCode << endl;
					UpdateDivisionVirtualInfo(beDivisionId, strParentCode, strOrgCode, iIsVirtual);
					//----------------------------------//

					pDivisionDefenseModel->SetHRId(oDivisionInfo.getStringField("hr_id"));

					if (iActionType == ACTION_UPDATE)
					{
						pDivisionDefenseModel->SetHRCode(strOrgCode);
					}
					else
					{
						pDivisionDefenseModel->SetHRCode(oDivisionInfo.getStringField("hr_code"));
					}
					//pDivisionDefenseModel->SetAlias(oDivisionInfo.getStringField("alias"));
					pDivisionDefenseModel->SetAlias(strDivisionAlias);
					pDivisionDefenseModel->SetChangeBy(COLLECTOR_MIS);

					if (!bActive)
						pDivisionDefenseModel->SetStatus(INACTIVE);
					else
						//pDivisionDefenseModel->SetStatus(oDivisionInfo.getIntField("status"));
						pDivisionDefenseModel->SetStatus(ACTIVE);

					pDivisionDefenseModel->SetCIId(beDivisionId);
					pDivisionDefenseModel->SetActionType(iActionType);
					pDivisionDefenseModel->SetClock(now);
					SaveDivisionDefenseInfo(strDirtyTable, pDivisionDefenseModel);
					
					ptrSecondResultCursor.reset();
					ptrResultCursor.reset();
				}
				catch(exception& ex)
				{	
					stringstream strErrorMess;
					strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
					strLog = CUtilities::FormatLog(ERROR_MSG, "CDivisionController", "CompareData","exception:" + strErrorMess.str());
					CUtilities::WriteErrorLog(ERROR_MSG, strLog);
				}
			}
		}
		else
		{
			strLog = CUtilities::FormatLog(ERROR_MSG, "CDivisionController", "CompareData","Data Exception:" + strJsonData);
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CDivisionController", "CompareData","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

CDivisionModel* CDivisionController::GetDivisionInfoByHRCode(const std::string &strHRCode)
{
	CDivisionModel* pDivisionInfo = NULL;
	HRCode2DivisionInfoMap::iterator it = m_mapHRCode2DivisionInfoMap.find(strHRCode);
	
	if (it != m_mapHRCode2DivisionInfoMap.end())
	{
		pDivisionInfo = (*it).second;
	}
	else
	{
		pDivisionInfo = new CDivisionModel();		
		m_mapHRCode2DivisionInfoMap[strHRCode] = pDivisionInfo;
	}

	return pDivisionInfo;
}

CDivisionDefenseInfoModel* CDivisionController::GetDivisionDefenseInfoByHRCode(const std::string &strHRCode)
{
	CDivisionDefenseInfoModel* pDivisionDefInfo = NULL;
	HRCode2DivisionDefenseInfoMap::iterator it = m_mapHRCode2DivisionDefenseInfo.find(strHRCode);
	
	if (it != m_mapHRCode2DivisionDefenseInfo.end())
	{
		pDivisionDefInfo = (*it).second;
	}
	else
	{
		pDivisionDefInfo = new CDivisionDefenseInfoModel();		
		m_mapHRCode2DivisionDefenseInfo[strHRCode] = pDivisionDefInfo;
	}

	return pDivisionDefInfo;
}

void CDivisionController::SaveDivisionDefenseInfo(const string& strTableName, CDivisionDefenseInfoModel *pDivisionDefenseModel)
{
	BSONObj boDivisionDefenseInfo;
	BSONObj boCondition;

	boDivisionDefenseInfo = pDivisionDefenseModel->GetDivisionDefenseInfo();
	cout << "Save Data:" << boDivisionDefenseInfo.toString();
	boCondition = boDivisionDefenseInfo;
	boCondition = boCondition.removeField("clock");	
	Insert(strTableName, boDivisionDefenseInfo, boCondition);
}

void CDivisionController::SaveDivisionInfo(CDivisionModel *pDivisionModel)
{
	BSONObj boDivisionInfo;

	boDivisionInfo = pDivisionModel->GetDivisionInfo();
	BSONObj boCondition;

	Insert(boDivisionInfo, boCondition);
}

string CDivisionController::GetDivisionAlias(const string& strOrgCode, const string& strParentCode)
{
	string strDivisionAlias;
	string strParentCodeTmp;

	if (strParentCode == "")
	{
		strDivisionAlias = strOrgCode;
		return strDivisionAlias;
	}

	strParentCodeTmp = CUtilities::ToUpperString(strParentCode);

	if (strParentCodeTmp == VNG_DIVISION)
		strDivisionAlias = strOrgCode;
	else
		strDivisionAlias = strParentCode;
	
	return strDivisionAlias;
}

void CDivisionController::UpdateDivisionVirtualInfo(BSONElement beDivisionId, const string& strParentCode, const string& strMisAlias, int iIsVirtual)
{
	BSONObj boData = BSON("$set" << BSON("mis_alias" << strMisAlias << 
										 "hr_parent_code" << strParentCode << 
										 "is_virtual" << iIsVirtual));
	Query qCond = QUERY("_id" << beDivisionId);
	
	cout << "query:" << qCond.toString() << endl;
	Update(boData, qCond);
}