#pragma once
#include "CIInfoIndexController.h"

class CChassisInfoIndexController :
	public CCIInfoIndexController
{
public:
	CChassisInfoIndexController(void);
	~CChassisInfoIndexController(void);
	bool RemoveInfoChange(Query queryRemoveCondition);
};
