#pragma once
#include "NotificationAPI.h"

class CSnSServerNotificationAPI :
	public CNotificationAPI
{
public:
	CSnSServerNotificationAPI(void);
	~CSnSServerNotificationAPI(void);
protected:
	void Convert2JSON(CNotificationModel* pData, BSONObj &boRecord);
};
