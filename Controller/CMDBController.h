#pragma once
#include "MongodbController.h"

class CCMDBController :
	public CMongodbController
{
public:
	CCMDBController(void);
	virtual ~CCMDBController(void);

	virtual auto_ptr<DBClientCursor> LoadData();
	bool FindSendMailConfig(BSONObj &boConfigRecord, BSONObj boNewCIInfo, string strApp);
	bool FindOperatingPhysicalServer(auto_ptr<DBClientCursor>& ptrCursor);
	bool FindOperatingVirtualServer(auto_ptr<DBClientCursor>& ptrCursor);
	bool FindOperatingAllServer(auto_ptr<DBClientCursor>& ptrCursor);
	bool FindOperatingChassis(auto_ptr<DBClientCursor>& ptrCursor);
	bool FindOperatingAccessSwitch(auto_ptr<DBClientCursor>& ptrCursor);
	bool FindOperatingAggregationSwitch(auto_ptr<DBClientCursor>& ptrCursor);
	bool FindOperatingCoreSwitch(auto_ptr<DBClientCursor>& ptrCursor);
	bool FindOperatingRack(auto_ptr<DBClientCursor>& ptrCursor);
	bool FindOperatingPDU(auto_ptr<DBClientCursor>& ptrCursor);
	bool FindServerU(auto_ptr<DBClientCursor>& ptrCursor);
};
