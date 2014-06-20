#pragma once
#include "CIIndexPooler.h"

class CAccessSwitchIndexPooler :
	public CCIIndexPooler
{
public:
	CAccessSwitchIndexPooler(const string& strCfgFile);
	~CAccessSwitchIndexPooler(void);
};
