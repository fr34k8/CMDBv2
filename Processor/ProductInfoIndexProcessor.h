#pragma once
#include "CIInfoIndexProcessor.h"

class CProductInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CProductInfoIndexProcessor(const string& strCfgFile);
	~CProductInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:	
	static void* StartPooler(void *threadarg);
};
