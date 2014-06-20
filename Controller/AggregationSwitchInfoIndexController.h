#pragma once
#include "CIInfoIndexController.h"

class CAggregationSwitchInfoIndexController :
	public CCIInfoIndexController
{
public:
	CAggregationSwitchInfoIndexController(void);
	~CAggregationSwitchInfoIndexController(void);
	bool RemoveInfoChange(Query queryRemoveCondition);
};
