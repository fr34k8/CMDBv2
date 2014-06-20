#include "DepartmentController.h"
#include "../Common/DBCommon.h"
#include "../Model/JsonModel.h"
#include "../Model/CollectorModel.h"
#include "../Model/DepartmentDefenseInfoModel.h"
#include "../Model/DepartmentModel.h"
#include "DivisionController.h"

CDepartmentController::CDepartmentController(void)
{
	m_strTableName = TBL_DEPARTMENT;
}

CDepartmentController::~CDepartmentController(void)
{
	ClearMapDepartmentInfo();
	ClearMapDepartmentDefenseInfo();
}

CDepartmentModel* CDepartmentController::GetDepartmentInfoByHRCode(const std::string &strHRCode)
{
	CDepartmentModel* pDepartmentInfo = NULL;
	HRCode2DepartmentInfoMap::iterator it = m_mapHRCode2DepartmentInfoMap.find(strHRCode);
	
	if (it != m_mapHRCode2DepartmentInfoMap.end())
	{
		pDepartmentInfo = (*it).second;
	}
	else
	{
		pDepartmentInfo = new CDepartmentModel();		
		m_mapHRCode2DepartmentInfoMap[strHRCode] = pDepartmentInfo;
	}

	return pDepartmentInfo;
}

CDepartmentDefenseInfoModel* CDepartmentController::GetDepartmentDefenseInfoByHRCode(const std::string &strHRCode)
{
	CDepartmentDefenseInfoModel* pDepartmentDefInfo = NULL;
	HRCode2DepartmentDefenseInfoMap::iterator it = m_mapHRCode2DepartmentDefenseInfo.find(strHRCode);
	
	if (it != m_mapHRCode2DepartmentDefenseInfo.end())
	{
		pDepartmentDefInfo = (*it).second;
	}
	else
	{
		pDepartmentDefInfo = new CDepartmentDefenseInfoModel();		
		m_mapHRCode2DepartmentDefenseInfo[strHRCode] = pDepartmentDefInfo;
	}

	return pDepartmentDefInfo;
}

void CDepartmentController::ClearMapDepartmentInfo()
{
	HRCode2DepartmentInfoMap::iterator it = m_mapHRCode2DepartmentInfoMap.begin();
	while(it != m_mapHRCode2DepartmentInfoMap.end())
	{
		delete (*it).second;
		it++;
	}
}

void CDepartmentController::ClearMapDepartmentDefenseInfo()
{
	HRCode2DepartmentDefenseInfoMap::iterator it = m_mapHRCode2DepartmentDefenseInfo.begin();
	while(it != m_mapHRCode2DepartmentDefenseInfo.end())
	{
		delete (*it).second;
		it++;
	}
}

void CDepartmentController::CompareFullData(CCollectorModel *pCollectorInfo, char *pData)
{
	CJsonModel objJsonModel; 
	string strJsonData = "";

	if (NULL != pData)
		strJsonData = pData;
	
	string strOrgId;
	string strOrgCode;
	string strOrgDivId;
	string strOrgDivCode;

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
				strOrgId = strOrgCode = strOrgDivId = strOrgDivCode ="";

				if (!jRootValue[index]["orgID"].isNull())
					strOrgId = jRootValue[index]["orgID"].asString();
				if (!jRootValue[index]["orgCode"].isNull())
					strOrgCode = jRootValue[index]["orgCode"].asString();
				if (!jRootValue[index]["parentID"].isNull())
					strOrgDivId = jRootValue[index]["parentID"].asString();
				if (!jRootValue[index]["parentCode"].isNull())
					strOrgDivCode = jRootValue[index]["parentCode"].asString();

				if (!jRootValue[index]["active"].isNull())
					bActive = jRootValue[index]["active"].asBool();

				if (strOrgCode == "" && strOrgId == "")
					continue;
				
				if (!bActive)
					continue;

				if (IsMatchDepartmentInfo(strOrgCode, strOrgDivCode))
				{
					BSONObj boOrgDepartmentInfo = BSON("$set" << BSON("hr_id" << strOrgId << "hr_code" << strOrgCode <<
																	"division_hr_code" << strOrgDivCode));
					//Query qCondition = QUERY("alias" << strOrgCode << "status" << 1 << "deleted" << 0);
					Query qCondition = QUERY("alias" << strOrgCode << "status" << ACTIVE << "deleted" << UNDELETED_FLAG);
					Update(boOrgDepartmentInfo, qCondition);

					PushDirtyDepartmentOrgChart(strDirtyTable, strOrgCode, strOrgId, strOrgDivCode, strOrgDivId, MATCH);
				}
				else
				{
					PushDirtyDepartmentOrgChart(strDirtyTable, strOrgCode, strOrgId, strOrgDivCode, strOrgDivId, NOTMATCH);
				}
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CDepartmentController", "CompareData","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

bool CDepartmentController::IsMatchDepartmentInfo(const string& strOrgCode, const string& strOrgDivisionCode)
{
	Query qCondition = QUERY("alias" << strOrgCode << "division_alias" << strOrgDivisionCode <<
							"status" << ACTIVE << "deleted" << UNDELETED_FLAG);
	return IsExisted(qCondition);
}

void CDepartmentController::PushDirtyDepartmentOrgChart(const std::string &strDirtyTable, 
														const std::string &strOrgCode, 
														const std::string &strOrgId, 
														const std::string &strOrgDivisionCode, 
														const std::string &strOrgDivisionId, 
														int iFlag)
{
	BSONObj boDataInfo = BSON("orgId" << strOrgId << "orgCode" << strOrgCode <<
							"orgDivisionId"<< strOrgDivisionId << "orgDivisionCode" << strOrgDivisionCode <<
							"is_match" << iFlag);
	BSONObj boCondition = BSON("orgId" << strOrgId);
	Insert(strDirtyTable, boDataInfo, boCondition);
}

void CDepartmentController::CompareChangeData(CCollectorModel *pCollectorInfo, char *pData)
{
	CJsonModel objJsonModel; 
	
	string strJsonData = "";

	if (NULL == pData)
		return;

	strJsonData = pData;
	
	string strOrgId;
	string strOrgCode;
	string strOrgDivId;
	string strOrgDivCode;

	string strDirtyTable;
	string strHRCode;
	string strDivisionAlias;
	string strDivisionHRCode;

	bool bActive = true;
	int iStatus;

	int iActionType;

	strDirtyTable = pCollectorInfo->GetDirtyTableName();
	CDepartmentDefenseInfoModel *pDepartmentDefenseModel;
	CDepartmentModel *pDepartmentModel;

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
				strOrgId = strOrgCode = strHRCode = strDivisionHRCode = "";
				iActionType = iStatus = UNKNOWN;

				if (!jRootValue[index]["orgID"].isNull())
					strOrgId = jRootValue[index]["orgID"].asString();
				if (!jRootValue[index]["orgCode"].isNull())
					strOrgCode = jRootValue[index]["orgCode"].asString();
				if (!jRootValue[index]["parentID"].isNull())
					strOrgDivId = jRootValue[index]["parentID"].asString();
				if (!jRootValue[index]["parentCode"].isNull())
					strOrgDivCode = jRootValue[index]["parentCode"].asString();
				if (!jRootValue[index]["active"].isNull())
					bActive = jRootValue[index]["active"].asBool();

				if (strOrgCode == "" && strOrgId == "")
					continue;

				pDepartmentDefenseModel = GetDepartmentDefenseInfoByHRCode(strOrgCode);	

				auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
				auto_ptr<DBClientCursor> ptrSecondResultCursor = auto_ptr<DBClientCursor>();
				auto_ptr<DBClientCursor> ptrDivisionResultCursor = auto_ptr<DBClientCursor>();

				try
				{
					BSONObj oDepartmentInfo;
					BSONObj oDivisionInfo;
					
					oDivisionInfo = GetDivisionObjectByAlias(ptrDivisionResultCursor, strOrgDivCode);
					if (oDivisionInfo.isEmpty())
						continue;
					
					BSONElement beDivisionId;
					BSONElement beDepartmentId;
					
					beDivisionId		= oDivisionInfo["_id"];
					strDivisionAlias	= oDivisionInfo.hasField("alias") ? oDivisionInfo.getStringField("alias") : "";

					//Query qCondition = QUERY("hr_id" << strOrgId << "status" << 1 << "deleted" << 0);
					Query qCondition = QUERY("hr_id" << strOrgId << "deleted" << UNDELETED_FLAG);
					
					ptrResultCursor = Find(qCondition);

					if (!ptrResultCursor->more())
					{
						// New Department
						if (bActive)
						{
							iActionType = ACTION_INSERT;
							pDepartmentModel = GetDepartmentInfoByHRCode(strOrgCode);
							
							pDepartmentModel->SetHRId(strOrgId);
							pDepartmentModel->SetHRCode(strOrgCode);
							pDepartmentModel->SetAlias(strOrgCode);
							pDepartmentModel->SetDivisionId(beDivisionId);
							//pDepartmentModel->SetDivisionAlias(strOrgDivCode);
							pDepartmentModel->SetDivisionAlias(strDivisionAlias);
							pDepartmentModel->SetDivisionHRCode(strOrgDivCode);
							pDepartmentModel->SetStatus(ACTIVE);
							//Insert New Department
							SaveDepartmentInfo(pDepartmentModel);
							
							ptrSecondResultCursor = Find(qCondition);
							if (ptrSecondResultCursor->more())
								oDepartmentInfo = ptrSecondResultCursor->nextSafe();
						}
					}
					else
					{
						oDepartmentInfo = ptrResultCursor->nextSafe();
					}
					
					if (oDepartmentInfo.isEmpty())
						continue;
					
					strHRCode = oDepartmentInfo.getStringField("hr_code");
					strDivisionHRCode = oDepartmentInfo.getStringField("division_hr_code");
					
					//Get department status 
					iStatus = oDepartmentInfo.getIntField("status");

					//Found & Delete
					if ((!bActive && (iStatus == ACTIVE)) || (bActive && (iStatus == INACTIVE)))
					{
						iActionType = ACTION_UPDATE;
					}
					//Found & Update
					else 
					{
						if ((strHRCode != strOrgCode) || (strDivisionHRCode != strOrgDivCode))
						{
							iActionType = ACTION_UPDATE;
						}
					}
					
					if (iActionType == UNKNOWN)
						continue;
					
					//oDepartmentInfo.getObjectID(beDepartmentId);
					beDepartmentId = oDepartmentInfo["_id"];
					pDepartmentDefenseModel->SetHRId(oDepartmentInfo.getStringField("hr_id"));

					if (iActionType == ACTION_UPDATE)
					{
						pDepartmentDefenseModel->SetHRCode(strOrgCode);
						pDepartmentDefenseModel->SetDivisionHRCode(strOrgDivCode);
						//pDepartmentDefenseModel->SetDivisionAlias(strOrgDivCode);
						pDepartmentDefenseModel->SetDivisionAlias(strDivisionAlias);
					}
					else
					{
						pDepartmentDefenseModel->SetHRCode(oDepartmentInfo.getStringField("hr_code"));
						pDepartmentDefenseModel->SetDivisionHRCode(oDepartmentInfo.getStringField("division_hr_code"));
						pDepartmentDefenseModel->SetDivisionAlias(oDepartmentInfo.getStringField("division_alias"));
					}

					pDepartmentDefenseModel->SetAlias(oDepartmentInfo.getStringField("alias"));
					pDepartmentDefenseModel->SetDivisionId(beDivisionId);
					pDepartmentDefenseModel->SetChangeBy(COLLECTOR_MIS);

					if (!bActive)
						pDepartmentDefenseModel->SetStatus(INACTIVE);
					else
						pDepartmentDefenseModel->SetStatus(ACTIVE);

					pDepartmentDefenseModel->SetCIId(beDepartmentId);
					pDepartmentDefenseModel->SetActionType(iActionType);
					pDepartmentDefenseModel->SetClock(now);
					SaveDepartmentDefenseInfo(strDirtyTable, pDepartmentDefenseModel);
					
					ptrSecondResultCursor.reset();
					ptrResultCursor.reset();
					ptrDivisionResultCursor.reset();
				}
				catch(exception& ex)
				{	
					stringstream strErrorMess;
					strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
					strLog = CUtilities::FormatLog(ERROR_MSG, "CDepartmentController", "CompareData","exception:" + strErrorMess.str());
					CUtilities::WriteErrorLog(ERROR_MSG, strLog);
				}
			}
		}
		else
		{
			strLog = CUtilities::FormatLog(ERROR_MSG, "CDepartmentController", "CompareData","Data Exception:" + strJsonData);
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CDepartmentController", "CompareData","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CDepartmentController::SaveDepartmentInfo(CDepartmentModel *pDepartmentModel)
{
	BSONObj boDepartmentInfo;
	boDepartmentInfo = pDepartmentModel->GetDepartmentInfo();
	cout << boDepartmentInfo.toString() << endl;
	BSONObj boCondition;

	Insert(boDepartmentInfo, boCondition);
}

void CDepartmentController::SaveDepartmentDefenseInfo(const string& strTableName, CDepartmentDefenseInfoModel *pDepartmentDefenseModel)
{
	BSONObj boDepartmentDefenseInfo;
	
	boDepartmentDefenseInfo = pDepartmentDefenseModel->GetDepartmentDefenseInfo();
	
	BSONObj boCondition;
	boCondition = boDepartmentDefenseInfo;
	boCondition = boCondition.removeField("clock");
	
	cout << "Data:" << boCondition.toString() << endl;
	Insert(strTableName, boDepartmentDefenseInfo, boCondition);
}

BSONObj CDepartmentController::GetDivisionObjectByAlias(auto_ptr<DBClientCursor> &ptrDivisionResultCursor, const string& strAlias)
{
	BSONObj boResultData;
				
	try
	{
		//Query qCondition = QUERY("alias" << strAlias << "status" << ACTIVE << "deleted" << UNDELETED_FLAG);
		Query qCondition = QUERY("hr_code" << strAlias << "status" << ACTIVE << "deleted" << UNDELETED_FLAG);
		ptrDivisionResultCursor = Find(TBL_DIVISION, qCondition);
		
		if (ptrDivisionResultCursor->more())
		{
			boResultData = ptrDivisionResultCursor->nextSafe();
		}
	}
	catch(exception& ex)
	{	
		stringstream ssErrorMsg;
		string strLog;
		ssErrorMsg << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CDivisionController", "GetDivisionObjectByAlias","exception:" + ssErrorMsg.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return boResultData;
}