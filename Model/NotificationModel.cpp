#include "NotificationModel.h"

CNotificationModel::CNotificationModel(void)
{
	//m_bIsFieldMapping = false;
	m_iIsNotified = API_ACTION_ERROR;
	m_strLibraryName = "";
	m_strAPIName = "";
	m_strPartnerName = "";
	m_strResponse = "";
}

CNotificationModel::~CNotificationModel(void)
{
}

BSONObj CNotificationModel::GetHistoricalNotiRecord(BSONObj boRecord, BSONObj boStatus)
{
	BSONObj boHistoricalRecord;
	long long lCreatedData = atol(CUtilities::GetCurrTimeStamp().c_str());
	BSONObj boCreateDate = BSON("created_date" << lCreatedData);
	boHistoricalRecord = CMongodbModel::MergeBSONObj(&boRecord, &boStatus);
	boHistoricalRecord = CMongodbModel::MergeBSONObj(&boHistoricalRecord, &boCreateDate);
	return boHistoricalRecord;
}
