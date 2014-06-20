#include "AccessSwitchInfoIndexController.h"

CAccessSwitchInfoIndexController::CAccessSwitchInfoIndexController(void)
{
	m_strTableName = TBL_ACCESS_SWITCH_INVERTED_INDEX;
}

CAccessSwitchInfoIndexController::~CAccessSwitchInfoIndexController(void)
{
}

bool CAccessSwitchInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_ACCESS_SWITCH_INFO_CHANGE,queryRemoveCondition);
}