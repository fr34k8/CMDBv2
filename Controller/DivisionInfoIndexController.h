#pragma once
#include "CIInfoIndexController.h"

class CDivisionInfoIndexController :
	public CCIInfoIndexController
{
public:
	CDivisionInfoIndexController(void);
	~CDivisionInfoIndexController(void);
	bool InsertHistoryChange(BSONObj boCIInfoChangeRecord) { return true; }
	bool RemoveInfoChange(Query queryRemoveCondition);
};
