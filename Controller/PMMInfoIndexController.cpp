#include "PMMInfoIndexController.h"

CPMMInfoIndexController::CPMMInfoIndexController(void)
{
	m_strTableName = TBL_PMM_INVERTED_INDEX;
}

CPMMInfoIndexController::~CPMMInfoIndexController(void)
{
}

bool CPMMInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_PMM_INFO_CHANGE,queryRemoveCondition);
}