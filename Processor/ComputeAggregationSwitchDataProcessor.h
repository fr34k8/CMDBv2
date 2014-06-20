#pragma once
#include "ComputeDataProcessor.h"

class CComputeAggregationSwitchDataProcessor :
	public CComputeDataProcessor
{
public:
	CComputeAggregationSwitchDataProcessor(const string& strCfgFile);
	~CComputeAggregationSwitchDataProcessor(void);
protected:
	bool Connect();
	bool LoadData();
	void ComputeData();
};
