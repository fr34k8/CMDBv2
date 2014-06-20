#pragma once
#include "NotificationModel.h"

class CServerNotificationModel: public CNotificationModel
{
public:
	CServerNotificationModel(void);
	~CServerNotificationModel(void);

	BSONObj GetNotificationInfo(BSONObj boCIInfo, BSONObj boNewCIInfo);
};
