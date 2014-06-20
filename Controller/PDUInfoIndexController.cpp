#include "PDUInfoIndexController.h"

CPDUInfoIndexController::CPDUInfoIndexController(void)
{
	m_strTableName = TBL_PDU_INVERTED_INDEX;
}

CPDUInfoIndexController::~CPDUInfoIndexController(void)
{
}

bool CPDUInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_PDU_INFO_CHANGE,queryRemoveCondition);
}