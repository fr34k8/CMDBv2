#pragma once
#include "CIIndexPooler.h"

class CPeerLinkIndexPooler :
	public CCIIndexPooler
{
public:
	CPeerLinkIndexPooler(const string& strCfgFile);
	~CPeerLinkIndexPooler(void);
};
