#include "ServerInfoIndexController.h"
#include "../Common/DBCommon.h"

CServerInfoIndexController::CServerInfoIndexController(void)
{
	m_strTableName = TBL_SERVER_INVERTED_INDEX;
}

CServerInfoIndexController::~CServerInfoIndexController(void)
{
}

bool CServerInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_SERVER_INFO_CHANGE,queryRemoveCondition);
}