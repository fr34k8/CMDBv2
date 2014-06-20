#pragma once
#include "NotificationAPI.h"

class CDCServerNotificationAPI :
	public CNotificationAPI
{
public:
	CDCServerNotificationAPI(void);
	~CDCServerNotificationAPI(void);
protected:
	void Convert2JSON(CNotificationModel* pData, BSONObj &boRecord);
};
