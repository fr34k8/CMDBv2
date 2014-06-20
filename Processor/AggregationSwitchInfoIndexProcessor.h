#pragma once
#include "CIInfoIndexProcessor.h"

class CAggregationSwitchInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CAggregationSwitchInfoIndexProcessor(const string& strCfgFile);
	~CAggregationSwitchInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:	
	static void* StartPooler(void *threadarg);
};
