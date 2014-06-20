#pragma once
#include "NotificationAPI.h"

class CMISProductNotificationAPI :
	public CNotificationAPI
{
public:
	CMISProductNotificationAPI(void);
	~CMISProductNotificationAPI(void);

	//void CreateMailInfo(CNotificationModel* pData);

protected:
	void Convert2JSON(CNotificationModel* pData, BSONObj &boRecord);
};