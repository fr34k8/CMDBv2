#include "RowInfoIndexController.h"

CRowInfoIndexController::CRowInfoIndexController(void)
{
	m_strTableName = TBL_ROW_INVERTED_INDEX;
}

CRowInfoIndexController::~CRowInfoIndexController(void)
{
}

bool CRowInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_ROW_INFO_CHANGE,queryRemoveCondition);
}