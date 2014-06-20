#pragma once
#include "../Common/Common.h"

class CNotificationModel;
typedef map<string, CNotificationModel*> TableName2NotificationModelMap;
class CPartnerInfoModel
{
public:
	CPartnerInfoModel(void);
	virtual ~CPartnerInfoModel(void);

	void RegisterNotification(const string& strLibraryName, const string& strAPIName, 
								const string& strTableName, const string& strPartnerName);
	CNotificationModel* GetNotificationModel(const string& strTableName);

protected:
	TableName2NotificationModelMap m_mapTableName2NotificationModel;
};
