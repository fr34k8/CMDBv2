#include "PartnerInfoController.h"
#include "../Model/PartnerInfoModel.h"
#include "../Common/DBCommon.h"

CPartnerInfoController::CPartnerInfoController(void)
{
	m_strTableName = TBL_PARTNER_INFO;
}

CPartnerInfoController::~CPartnerInfoController(void)
{
	PartnerName2PartnerInfoMap::iterator it = m_mapPartnerName2PartnerInfo.begin();
	while (it != m_mapPartnerName2PartnerInfo.end())
	{
		delete (*it).second;
		it++;
	}

	m_mapPartnerName2PartnerInfo.clear();
}

CPartnerInfoModel* CPartnerInfoController::GetPartnerInfoByPartnerName(const string& strPartnerName)
{
	CPartnerInfoModel* pPartnerInfo = NULL;
	PartnerName2PartnerInfoMap::iterator it = m_mapPartnerName2PartnerInfo.find(strPartnerName);
	if (it != m_mapPartnerName2PartnerInfo.end())
	{
		pPartnerInfo = (*it).second;
	}
	else
	{
		pPartnerInfo = new CPartnerInfoModel();		
		m_mapPartnerName2PartnerInfo[strPartnerName] = pPartnerInfo;
	}

	return pPartnerInfo;
}

bool CPartnerInfoController::LoadPartnerInfo()
{
	bool bResult = false;
	string strPartnerName;
	string strTableName;
	string strLibraryName;
	string strAPIName;
	// Load all data from database
	auto_ptr<DBClientCursor> ptrResultCursor = Find();
	if ((ptrResultCursor.get() != NULL) && (ptrResultCursor->more()))
	{
		bResult = true;
		while (ptrResultCursor->more()) {
			BSONObj oPartnerInfo = ptrResultCursor->nextSafe();
			// Get partner info
			strPartnerName = oPartnerInfo.getStringField("partner_name");
			CPartnerInfoModel* pPartnerInfo = GetPartnerInfoByPartnerName(strPartnerName);
			// Register API to table for getting notification
			strTableName = oPartnerInfo.getStringField("table_name");
			strAPIName = oPartnerInfo.getStringField("api_name");
			strLibraryName = oPartnerInfo.getStringField("library_name");
			pPartnerInfo->RegisterNotification(strLibraryName, strAPIName, strTableName, strPartnerName);
		}

		ptrResultCursor.reset();
	}
	return bResult;
}

CNotificationModel* 
CPartnerInfoController::GetNotificationModel(const string& strPartnerName, 
											 const string& strTableName)
{
	CNotificationModel* pNotificationModel = NULL;

	CPartnerInfoModel* pPartnerInfo = GetPartnerInfoByPartnerName(strPartnerName);

	if (NULL != pPartnerInfo)
	{
		pNotificationModel = pPartnerInfo->GetNotificationModel(strTableName);
	}

	return pNotificationModel;
}

bool CPartnerInfoController::IsPartnerName(const string& strPartnerName)
{
	PartnerName2PartnerInfoMap::iterator it = m_mapPartnerName2PartnerInfo.find(strPartnerName);
	if (it != m_mapPartnerName2PartnerInfo.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}