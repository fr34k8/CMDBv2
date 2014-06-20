#include "PartnerInfoModel.h"
#include "NotificationModel.h"

CPartnerInfoModel::CPartnerInfoModel(void)
{
}

CPartnerInfoModel::~CPartnerInfoModel(void)
{
	TableName2NotificationModelMap::iterator it = m_mapTableName2NotificationModel.begin();
	while (it != m_mapTableName2NotificationModel.end())
	{
		delete (*it).second;
		it++;
	}

	m_mapTableName2NotificationModel.clear();
}

void CPartnerInfoModel::RegisterNotification(const string& strLibraryName, 
											 const string& strAPIName, 
											 const string& strTableName,
											 const string& strPartnerName)
{
	// Create notification model
	CNotificationModel* pNotificationModel = new CNotificationModel();
	pNotificationModel->SetAPIName(strAPIName);
	pNotificationModel->SetLibraryName(strLibraryName);
	pNotificationModel->SetPartnerName(strPartnerName);

	m_mapTableName2NotificationModel[strTableName] = pNotificationModel;
}

CNotificationModel* CPartnerInfoModel::GetNotificationModel(const string& strTableName)
{
	TableName2NotificationModelMap::iterator it = m_mapTableName2NotificationModel.find(strTableName);
	if (it != m_mapTableName2NotificationModel.end())
	{
		return (*it).second;
	}
	else
	{
		return NULL;
	}
}