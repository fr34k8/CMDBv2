#include "ServerController.h"
#include "../Common/DBCommon.h"

CServerController::CServerController(void)
{
	m_strTableName = TBL_SERVER;
}


CServerController::~CServerController(void)
{
}

bool CServerController::FindServerU(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult;
	bResult = Find(ptrCursor, 
		QUERY(
		"status" << BSON("$in" << BSON_ARRAY(SERVER_IN_USED << SERVER_BORROW << SERVER_TRANSFER)) << 
		"server_type" << BSON("$in" << BSON_ARRAY(SERVER_U << SERVER_CHASSIS)) <<
		"deleted" << 0)
		);
	return bResult;
}

bool CServerController::FindOperatingPhysicalServer(auto_ptr<DBClientCursor>& ptrCursor)
{
	bool bResult;
	bResult = Find(ptrCursor, 
		QUERY(
		"status" << BSON("$in" << BSON_ARRAY(SERVER_IN_USED << SERVER_BORROW << SERVER_TRANSFER)) << 
		"server_type" << BSON("$in" << BSON_ARRAY(SERVER_U << SERVER_UNKNOWN << SERVER_CHASSIS)) << 
		"deleted" << 0)
		);

	return bResult;
}