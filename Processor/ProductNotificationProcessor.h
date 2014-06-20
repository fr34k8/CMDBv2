#pragma once
#include "NotificationProcessor.h"

class CProductNotificationProcessor :
	public CNotificationProcessor
{
public:
	CProductNotificationProcessor(const string& strFileName);
	~CProductNotificationProcessor(void);
protected:
	static void* StartDispatcher(void *pData);
};
