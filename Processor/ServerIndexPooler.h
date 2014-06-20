#pragma once
#include "CIIndexPooler.h"

class CServerIndexPooler :
	public CCIIndexPooler
{
public:
	CServerIndexPooler(const string& strCfgFile);
	~CServerIndexPooler(void);
};