#pragma once
#include "CIIndexPooler.h"

class CPDUIndexPooler :
	public CCIIndexPooler
{
public:
	CPDUIndexPooler(const string& strCfgFile);
	~CPDUIndexPooler(void);
};
