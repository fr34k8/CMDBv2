#pragma once
#include "CIInfoIndexProcessor.h"

class CPeerLinkInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CPeerLinkInfoIndexProcessor(const string& strCfgFile);
	~CPeerLinkInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:
	static void* StartPooler(void *threadarg);
};
