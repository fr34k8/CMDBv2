#pragma once
#include "CIInfoIndexProcessor.h"

class CAccessSwitchInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CAccessSwitchInfoIndexProcessor(const string& strCfgFile);
	~CAccessSwitchInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:	
	static void* StartPooler(void *threadarg);
};
