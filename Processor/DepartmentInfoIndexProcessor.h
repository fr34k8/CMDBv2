#pragma once
#include "CIInfoIndexProcessor.h"

class CDepartmentInfoIndexProcessor :
	public CCIInfoIndexProcessor
{
public:
	CDepartmentInfoIndexProcessor(const string& strCfgFile);
	~CDepartmentInfoIndexProcessor(void);
	void ProceedInfoIndex();
protected:	
	static void* StartPooler(void *threadarg);
};
