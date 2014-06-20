#pragma once
#include "CIInfoIndexController.h"

class CDepartmentInfoIndexController :
	public CCIInfoIndexController
{
public:
	CDepartmentInfoIndexController(void);
	~CDepartmentInfoIndexController(void);
	bool InsertHistoryChange(BSONObj boCIInfoChangeRecord) { return true; }
	bool RemoveInfoChange(Query queryRemoveCondition);
};
