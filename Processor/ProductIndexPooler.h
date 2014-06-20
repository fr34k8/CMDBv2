#pragma once
#include "CIIndexPooler.h"

class CProductIndexPooler :
	public CCIIndexPooler
{
public:
	CProductIndexPooler(const string& strCfgFile);
	~CProductIndexPooler(void);
};
