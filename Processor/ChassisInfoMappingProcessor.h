#pragma once
#include "CIInfoMappingProcessor.h"

class CChassisInfoMappingProcessor : public CCIInfoMappingProcessor
{
public:
	CChassisInfoMappingProcessor(const string& strFileName);
	virtual ~CChassisInfoMappingProcessor(void);
protected:
	bool Connect();
};