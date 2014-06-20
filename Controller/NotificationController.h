#pragma once
#include "CMDBController.h"

class CNotificationController :
	public CCMDBController
{
public:
	CNotificationController(void);
	virtual ~CNotificationController(void);

	bool SetStatus();
	bool InsertHistory(BSONObj boHistoricalRecord);
};
