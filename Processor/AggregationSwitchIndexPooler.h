#pragma once
#include "CIIndexPooler.h"

class CAggregationSwitchIndexPooler :
	public CCIIndexPooler
{
public:
	CAggregationSwitchIndexPooler(const string& strCfgFile);
	~CAggregationSwitchIndexPooler(void);
};
