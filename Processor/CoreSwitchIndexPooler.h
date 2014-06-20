#pragma once
#include "CIIndexPooler.h"

class CCoreSwitchIndexPooler :
	public CCIIndexPooler
{
public:
	CCoreSwitchIndexPooler(const string& strCfgFile);
	~CCoreSwitchIndexPooler(void);
};
