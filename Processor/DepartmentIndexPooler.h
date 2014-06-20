#pragma once
#include "CIIndexPooler.h"

class CDepartmentIndexPooler :
	public CCIIndexPooler
{
public:
	CDepartmentIndexPooler(const string& strCfgFile);
	~CDepartmentIndexPooler(void);
};
