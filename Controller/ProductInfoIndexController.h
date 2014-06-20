#pragma once
#include "CIInfoIndexController.h"

class CProductInfoIndexController :
	public CCIInfoIndexController
{
public:
	CProductInfoIndexController(void);
	~CProductInfoIndexController(void);
	bool InsertHistoryChange(BSONObj boCIInfoChangeRecord) { return true; }
	bool RemoveInfoChange(Query queryRemoveCondition);
};
