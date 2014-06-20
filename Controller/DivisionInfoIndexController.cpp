#include "DivisionInfoIndexController.h"
#include "../Common/DBCommon.h"

CDivisionInfoIndexController::CDivisionInfoIndexController(void)
{
	m_strTableName = TBL_DIVISION_INVERTED_INDEX;
}

CDivisionInfoIndexController::~CDivisionInfoIndexController(void)
{
}

bool CDivisionInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_DIVISION_INFO_CHANGE,queryRemoveCondition);
}