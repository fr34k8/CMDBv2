#pragma once
#include "NotificationProcessor.h"

class CPhysicalServerNotificationProcessor :
	public CNotificationProcessor
{
public:
	CPhysicalServerNotificationProcessor(const string& strFileName);
	~CPhysicalServerNotificationProcessor(void);
protected:
	static void* StartDispatcher(void *pData);
};
