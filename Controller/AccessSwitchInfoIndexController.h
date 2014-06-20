#pragma once
#include "CIInfoIndexController.h"

class CAccessSwitchInfoIndexController :
	public CCIInfoIndexController
{
public:
	CAccessSwitchInfoIndexController(void);
	~CAccessSwitchInfoIndexController(void);
	bool RemoveInfoChange(Query queryRemoveCondition);
};
