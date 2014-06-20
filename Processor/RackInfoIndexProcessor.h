#pragma once
#include "CIInfoIndexProcessor.h"

class CRackInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CRackInfoIndexProcessor(const string& strCfgFile);
	~CRackInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:	
	static void* StartPooler(void *threadarg);
};
