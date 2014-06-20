#pragma once
#include "CIInfoChangeModel.h"

class CAggregationSwitchInfoChangeModel :
	public CCIInfoChangeModel
{
public:
	CAggregationSwitchInfoChangeModel(void);
	~CAggregationSwitchInfoChangeModel(void);
	void InitLookUpByPass();
};
