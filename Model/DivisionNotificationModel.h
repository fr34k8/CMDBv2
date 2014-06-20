#pragma once
#include "NotificationModel.h"

class CDivisionNotificationModel: public CNotificationModel
{
public:
	CDivisionNotificationModel(void);
	~CDivisionNotificationModel(void);

	BSONObj GetNotificationInfo(BSONObj boCIInfo, BSONObj boNewCIInfo);
};
