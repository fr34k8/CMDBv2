#pragma once
#include "CIInfoMappingProcessor.h"

class CAccessSwitchInfoMappingProcessor : public CCIInfoMappingProcessor
{
public:
	CAccessSwitchInfoMappingProcessor(const string& strFileName);
	virtual ~CAccessSwitchInfoMappingProcessor(void);
protected:
	bool Connect();
};