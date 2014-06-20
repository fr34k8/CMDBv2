#include "ChassisInfoIndexController.h"

CChassisInfoIndexController::CChassisInfoIndexController(void)
{
	m_strTableName = TBL_CHASSIS_INVERTED_INDEX;
}

CChassisInfoIndexController::~CChassisInfoIndexController(void)
{
}

bool CChassisInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_CHASSIS_INFO_CHANGE,queryRemoveCondition);
}