#pragma once
#include "CIInfoIndexProcessor.h"

class CPMMInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CPMMInfoIndexProcessor(const string& strCfgFile);
	~CPMMInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:	
	static void* StartPooler(void *threadarg);
};
