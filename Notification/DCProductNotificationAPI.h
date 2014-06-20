#pragma once
#include "NotificationAPI.h"

class CDCProductNotificationAPI :
	public CNotificationAPI
{
public:
	CDCProductNotificationAPI(void);
	~CDCProductNotificationAPI(void);

	//void CreateMailInfo(CNotificationModel* pData);

protected:
	void Convert2JSON(CNotificationModel* pData, BSONObj &boRecord);
};
