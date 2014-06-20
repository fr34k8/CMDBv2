#pragma once
#include "CIIndexPooler.h"

class CDivisionIndexPooler :
	public CCIIndexPooler
{
public:
	CDivisionIndexPooler(const string& strCfgFile);
	~CDivisionIndexPooler(void);
};
