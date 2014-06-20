#pragma once
#include "CIIndexPooler.h"

class CRowIndexPooler :
	public CCIIndexPooler
{
public:
	CRowIndexPooler(const string& strCfgFile);
	~CRowIndexPooler(void);
};
