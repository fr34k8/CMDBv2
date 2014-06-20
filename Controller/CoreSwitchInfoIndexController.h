#pragma once
#include "CIInfoIndexController.h"

class CCoreSwitchInfoIndexController :
	public CCIInfoIndexController
{
public:
	CCoreSwitchInfoIndexController(void);
	~CCoreSwitchInfoIndexController(void);
	bool RemoveInfoChange(Query queryRemoveCondition);
};
