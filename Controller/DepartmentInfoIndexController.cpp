#include "DepartmentInfoIndexController.h"
#include "../Common/DBCommon.h"

CDepartmentInfoIndexController::CDepartmentInfoIndexController(void)
{
	m_strTableName = TBL_DEPARTMENT_INVERTED_INDEX;
}

CDepartmentInfoIndexController::~CDepartmentInfoIndexController(void)
{
}

bool CDepartmentInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_DEPARTMENT_INFO_CHANGE,queryRemoveCondition);
}
