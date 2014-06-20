#pragma once
#include "../Common/Common.h"
#include "../Model/MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CNotificationModel;
class CMailboxController;
//typedef int (*NotifyInfoChange)(const char*, int, int);
typedef int(*NotifyInfoChange)(string, string &);
class CNotificationAPI
{
public:
	CNotificationAPI(void);
	virtual ~CNotificationAPI(void);

	int Notify(CNotificationModel* pData);
	//virtual void CreateMailInfo(CNotificationModel* pData) { };
protected:
	//bool Connect();
	//CMailboxController *m_pMailboxController;
	virtual void Convert2JSON(CNotificationModel* pData, BSONObj &boRecord) { }
};
