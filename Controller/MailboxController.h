#pragma once
#include "CMDBController.h"

class CMailboxController :
	public CCMDBController
{
public:
	CMailboxController(void);
	~CMailboxController(void);

	void NotifyServerLocation(const BSONObj& boServerInfo);	
	void NotifyServerNetwork(const BSONObj& boServerInfo);
	void NotifySwitchLocation(const BSONObj& boSwitchInfo);
	void NotifyMISServiceProblem(const BSONObj& boProblemInfo);
};
