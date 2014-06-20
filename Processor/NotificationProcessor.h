#pragma once
#include "Processor.h"

class CPartnerInfoController;
class CNotificationController;
class CNotificationModel;
typedef vector<CNotificationModel*> NotificationModelArray;
typedef void* (*StartDispatcherFunc)(void *);
class CNotificationProcessor :
	public CProcessor
{
public:
	CNotificationProcessor(const string& strFileName);
	virtual ~CNotificationProcessor(void);

	void ProceedNotifyInfo();
protected:
	bool Connect();	
	void GetPartnersFromRecord(const BSONObj& boRecord);
	void DispatchToPartners(const BSONObj& boRecord);
	virtual auto_ptr<DBClientCursor> LoadNotificationInfo();
	bool IsAllPartnersNotified(BSONObj boRecord);
protected:
	CPartnerInfoController* m_pPartnerInfoController;
	CNotificationController* m_pNotificationController;
	NotificationModelArray m_arrNotificationModel;
	StartDispatcherFunc m_pFuncStartDispatcher;
};
