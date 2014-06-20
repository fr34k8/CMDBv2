#pragma once
#include "CIIndexPooler.h"

class CPMMIndexPooler :
	public CCIIndexPooler
{
public:
	CPMMIndexPooler(const string& strCfgFile);
	~CPMMIndexPooler(void);
};
