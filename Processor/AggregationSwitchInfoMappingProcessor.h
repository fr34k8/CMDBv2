#pragma once
#include "CIInfoMappingProcessor.h"

class CAggregationSwitchInfoMappingProcessor : public CCIInfoMappingProcessor
{
public:
	CAggregationSwitchInfoMappingProcessor(const string& strFileName);
	virtual ~CAggregationSwitchInfoMappingProcessor(void);
protected:
	bool Connect();
};