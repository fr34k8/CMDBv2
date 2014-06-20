#pragma once
#include "CIInfoIndexProcessor.h"

class CCoreSwitchInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CCoreSwitchInfoIndexProcessor(const string& strCfgFile);
	~CCoreSwitchInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:	
	static void* StartPooler(void *threadarg);
};
