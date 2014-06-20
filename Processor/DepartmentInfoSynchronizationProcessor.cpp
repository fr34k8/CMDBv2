#include "DepartmentInfoSynchronizationProcessor.h"
#include "../Controller/CollectorController.h"
#include "../Controller/DepartmentController.h"
#include "../Controller/MailboxController.h"
#include "../Model/CollectorModel.h"
#include "../Synchronization/MISDepartmentSynchronization.h"
#include "../Common/ExternalCommon.h"

CDepartmentInfoSynchronizationProcessor::CDepartmentInfoSynchronizationProcessor(const string& strCfgFile)
:CSynchronizationProcessor(strCfgFile)
{	
	m_pMISDepartmentSync = new CMISDepartmentSynchronization();
	m_bIsMailNotification = true;
}

CDepartmentInfoSynchronizationProcessor::~CDepartmentInfoSynchronizationProcessor(void)
{	
	if (NULL != m_pMISDepartmentSync)
		delete m_pMISDepartmentSync;
}

void CDepartmentInfoSynchronizationProcessor::CompareFullDepartmentData(CCollectorModel* pCollectorInfo)
{
	char *pData;
	char *pTmpDataInfo;
	char *pUrlParameter;
	
	pUrlParameter = (char*)"?active=true\\&orgLevel=DEPT";
	
	cout << pUrlParameter << endl;
	if (m_pMISDepartmentSync->Synchronize(pUrlParameter, pCollectorInfo, &pTmpDataInfo))
	{
		pData = pTmpDataInfo;
		if (NULL != pData)
		{
			//cout << "Data:" << pData << endl;
			m_pDepartmentController->CompareFullData(pCollectorInfo, pData);
			delete pData;
		}
	}
	cout << "Finished" << endl;
}

void CDepartmentInfoSynchronizationProcessor::CompareChangeDepartmentData(CCollectorModel* pCollectorInfo)
{
	char *pData;
	char *pTmpDataInfo;

	time_t tFromDate;
	struct tm* tmFrom;
	string strUrlParameter;
	string strFromDate;
	string strToDate;
	
	//Used to write log & notify
	string strLog;		
	string strLogUrl = "";

	tFromDate = CUtilities::GetDateAgo(400*SEC_PER_DAY);
	tmFrom = CUtilities::GetLocalTime(&tFromDate);
	
	strFromDate = CUtilities::GetSpecialTime("%Y-%m-%d", tmFrom);
	strToDate = CUtilities::GetCurrTime("%Y-%m-%d");

	strUrlParameter = "?from=" + strFromDate + "\\&to=" + strToDate + "\\&orgLevel=DEPT";

	strLogUrl += MIS_ORGCHART_URL + strUrlParameter;
	if (m_pMISDepartmentSync->Synchronize((char*)strUrlParameter.c_str(), pCollectorInfo, &pTmpDataInfo))
	{
		pData = pTmpDataInfo;
		if (NULL != pData)
		{
			//cout << "Data:" << pData << endl;
			m_pDepartmentController->CompareChangeData(pCollectorInfo, pData);
			delete pData;
		}
		else
		{
			strLog = "Lost data from API";		
			strLog = CUtilities::FormatLog(ERROR_MSG, "CDepartmentInfoSynchronizationProcessor", "CompareChangeDepartmentData",strLog);
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);

			BSONObj boIssueInfo = BSON("url" << strLogUrl << "msg_error" << strLog);
			m_pMailboxController->NotifyMISServiceProblem(boIssueInfo);
		}
	}
	else
	{
		strLog = "Cannot load library connect to webservice of MIS";
		strLog = CUtilities::FormatLog(ERROR_MSG, "CDepartmentInfoSynchronizationProcessor", "CompareChangeDepartmentData",strLog);
		BSONObj boIssueInfo = BSON("url" << strLogUrl << "msg_error" << strLog);
		m_pMailboxController->NotifyMISServiceProblem(boIssueInfo);
	}
	cout << "Finished" << endl;
}