#pragma once
#include "CIInfoIndexProcessor.h"

class CDivisionInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CDivisionInfoIndexProcessor(const string& strCfgFile);
	~CDivisionInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:	
	static void* StartPooler(void *threadarg);
};
