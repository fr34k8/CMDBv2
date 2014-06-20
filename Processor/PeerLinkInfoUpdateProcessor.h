#pragma once
#include "CIInfoUpdateProcessor.h"

class CPeerLinkInfoUpdateProcessor : public CCIInfoUpdateProcessor
{
public:
	CPeerLinkInfoUpdateProcessor(const string& strCfgFile);
	~CPeerLinkInfoUpdateProcessor(void);
};