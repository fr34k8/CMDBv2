#pragma once
#include "CIIndexPooler.h"

class CChassisIndexPooler :
	public CCIIndexPooler
{
public:
	CChassisIndexPooler(const string& strCfgFile);
	~CChassisIndexPooler(void);
};
