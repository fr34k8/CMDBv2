#pragma once
#include "CIInfoIndexController.h"

class CRowInfoIndexController :
	public CCIInfoIndexController
{
public:
	CRowInfoIndexController(void);
	~CRowInfoIndexController(void);
	bool RemoveInfoChange(Query queryRemoveCondition);
};
