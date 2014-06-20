#include "CoreSwitchInfoIndexController.h"

CCoreSwitchInfoIndexController::CCoreSwitchInfoIndexController(void)
{
	m_strTableName = TBL_CORE_SWITCH_INVERTED_INDEX;
}

CCoreSwitchInfoIndexController::~CCoreSwitchInfoIndexController(void)
{
}

bool CCoreSwitchInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_CORE_SWITCH_INFO_CHANGE,queryRemoveCondition);
}