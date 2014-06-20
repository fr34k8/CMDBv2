#pragma once
#include "UpdateCIUSpaceProcessor.h"

class CUpdateAggregationSwitchUSpaceProcessor : public CUpdateCIUSpaceProcessor
{
public:
	CUpdateAggregationSwitchUSpaceProcessor(const string& strFileName);
	virtual ~CUpdateAggregationSwitchUSpaceProcessor(void);
protected:
	bool Connect();
};