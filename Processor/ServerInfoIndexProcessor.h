#pragma once
#include "CIInfoIndexProcessor.h"

class CServerInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CServerInfoIndexProcessor(const string& strCfgFile);
	~CServerInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:	
	static void* StartPooler(void *threadarg);
};