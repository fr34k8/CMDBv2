#pragma once
#include "CIInfoIndexProcessor.h"

class CRowInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CRowInfoIndexProcessor(const string& strCfgFile);
	~CRowInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:
	static void* StartPooler(void *threadarg);
};
