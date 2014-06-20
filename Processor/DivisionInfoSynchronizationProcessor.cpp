#include "DivisionInfoSynchronizationProcessor.h"
#include "../Controller/CollectorController.h"
#include "../Controller/DivisionController.h"
#include "../Controller/MailboxController.h"
#include "../Model/CollectorModel.h"
#include "../Synchronization/MISDivisionSynchronization.h"
#include "../Common/ExternalCommon.h"

CDivisionInfoSynchronizationProcessor::CDivisionInfoSynchronizationProcessor(const string& strCfgFile)
:CSynchronizationProcessor(strCfgFile)
{	
	m_pMISDivisionSync = new CMISDivisionSynchronization();
	m_bIsMailNotification = true;
}

CDivisionInfoSynchronizationProcessor::~CDivisionInfoSynchronizationProcessor(void)
{	
	if (NULL != m_pMISDivisionSync)
		delete m_pMISDivisionSync;
}

void CDivisionInfoSynchronizationProcessor::CompareFullDivisionData(CCollectorModel* pCollectorInfo)
{
	char *pData;
	char *pTmpDataInfo;
	char *pUrlParameter;
	
	pUrlParameter = (char*)"?active=true\\&orgLevel=DIV";
		
	if (m_pMISDivisionSync->Synchronize(pUrlParameter, pCollectorInfo, &pTmpDataInfo))
	{
		pData = pTmpDataInfo;
		if (NULL != pData)
		{
			cout << "Data:" << pData << endl;
			m_pDivisionController->CompareFullData(pCollectorInfo, pData);
			delete pData;
		}
	}
	cout << "Finished" << endl;
}

void CDivisionInfoSynchronizationProcessor::CompareChangeDivisionData(CCollectorModel* pCollectorInfo)
{
	char *pData;
	char *pTmpDataInfo;

	time_t tFromDate;
	struct tm* tmFrom;
	string strUrlParameter;
	string strFromDate;
	string strToDate;
	
	//Use write log & notify
	string strLog;		
	string strLogUrl = "";

	tFromDate = CUtilities::GetDateAgo(400*SEC_PER_DAY);
	tmFrom = CUtilities::GetLocalTime(&tFromDate);
	
	strFromDate = CUtilities::GetSpecialTime("%Y-%m-%d", tmFrom);
	strToDate = CUtilities::GetCurrTime("%Y-%m-%d");

	strUrlParameter = "?from=" + strFromDate + "\\&to=" + strToDate + "\\&orgLevel=DIV";
	
	strLogUrl += MIS_ORGCHART_URL + strUrlParameter;
	if (m_pMISDivisionSync->Synchronize((char*)strUrlParameter.c_str(), pCollectorInfo, &pTmpDataInfo))
	{
		pData = pTmpDataInfo;
		if (NULL != pData)
		{
			//cout << "Data:" << pData << endl;
			m_pDivisionController->CompareChangeData(pCollectorInfo, pData);
			delete pData;
		}
		else
		{
			strLog = "Lost data from API";
			strLog = CUtilities::FormatLog(ERROR_MSG, "CDivisionInfoSynchronizationProcessor", "CompareChangeDivisionData",strLog);
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);

			BSONObj boIssueInfo = BSON("url" << strLogUrl << "msg_error" << strLog);
			m_pMailboxController->NotifyMISServiceProblem(boIssueInfo);
		}
	}
	else
	{
		strLog = "Cannot load library connect to webservice of MIS";
		strLog = CUtilities::FormatLog(ERROR_MSG, "CDivisionInfoSynchronizationProcessor", "CompareChangeDivisionData",strLog);
		BSONObj boIssueInfo = BSON("url" << strLogUrl << "msg_error" << strLog);
		m_pMailboxController->NotifyMISServiceProblem(boIssueInfo);
	}
	
	cout << "Finished" << endl;
}