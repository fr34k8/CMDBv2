#include "ProductInfoIndexController.h"
#include "../Common/DBCommon.h"

CProductInfoIndexController::CProductInfoIndexController(void)
{
	m_strTableName = TBL_PRODUCT_INVERTED_INDEX;
}

CProductInfoIndexController::~CProductInfoIndexController(void)
{
}

bool CProductInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_PRODUCT_INFO_CHANGE,queryRemoveCondition);
}
