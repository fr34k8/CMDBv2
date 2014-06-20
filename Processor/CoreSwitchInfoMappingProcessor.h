#pragma once
#include "CIInfoMappingProcessor.h"

class CCoreSwitchInfoMappingProcessor : public CCIInfoMappingProcessor
{
public:
	CCoreSwitchInfoMappingProcessor(const string& strFileName);
	virtual ~CCoreSwitchInfoMappingProcessor(void);
protected:
	bool Connect();
};