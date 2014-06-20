#pragma once
#include "CIInfoIndexProcessor.h"

class CPDUInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CPDUInfoIndexProcessor(const string& strCfgFile);
	~CPDUInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:
	static void* StartPooler(void *threadarg);
};
