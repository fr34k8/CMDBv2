#pragma once
#include "CIInfoIndexProcessor.h"

class CChassisInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CChassisInfoIndexProcessor(const string& strCfgFile);
	~CChassisInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:
	static void* StartPooler(void *threadarg);
};
