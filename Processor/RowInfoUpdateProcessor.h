#pragma once
#include "CIInfoUpdateProcessor.h"

class CRowInfoUpdateProcessor : public CCIInfoUpdateProcessor
{
public:
	CRowInfoUpdateProcessor(const string& strCfgFile);
	~CRowInfoUpdateProcessor(void);
};