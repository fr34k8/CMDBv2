#include "RackInfoIndexController.h"

CRackInfoIndexController::CRackInfoIndexController(void)
{
	m_strTableName = TBL_RACK_INVERTED_INDEX;
}

CRackInfoIndexController::~CRackInfoIndexController(void)
{
}

bool CRackInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_RACK_INFO_CHANGE,queryRemoveCondition);
}