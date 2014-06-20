#include "PeerLinkInfoIndexController.h"

CPeerLinkInfoIndexController::CPeerLinkInfoIndexController(void)
{
	m_strTableName = TBL_PEER_LINK_INVERTED_INDEX;
}

CPeerLinkInfoIndexController::~CPeerLinkInfoIndexController(void)
{
}

bool CPeerLinkInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_PEER_LINK_INFO_CHANGE,queryRemoveCondition);
}