#pragma once
#include "CMDBController.h"

class CServerController :
	public CCMDBController
{
public:
	CServerController(void);
	~CServerController(void);

	bool FindServerU(auto_ptr<DBClientCursor>& ptrCursor);
	bool FindOperatingPhysicalServer(auto_ptr<DBClientCursor>& ptrCursor);
};
