#pragma once
#include "NotificationProcessor.h"

class CServerNotificationProcessor :
	public CNotificationProcessor
{
public:
	CServerNotificationProcessor(const string& strFileName);
	~CServerNotificationProcessor(void);
protected:
	auto_ptr<DBClientCursor> LoadNotificationInfo();
	static void* StartDispatcher(void *pData);
};
