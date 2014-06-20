#pragma once
#include "CIInfoUpdateProcessor.h"

class CRackInfoUpdateProcessor : public CCIInfoUpdateProcessor
{
public:
	CRackInfoUpdateProcessor(const string& strCfgFile);
	~CRackInfoUpdateProcessor(void);
};