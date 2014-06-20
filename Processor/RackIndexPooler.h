#pragma once
#include "CIIndexPooler.h"

class CRackIndexPooler :
	public CCIIndexPooler
{
public:
	CRackIndexPooler(const string& strCfgFile);
	~CRackIndexPooler(void);
};
