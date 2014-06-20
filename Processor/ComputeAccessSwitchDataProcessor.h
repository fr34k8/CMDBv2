#pragma once
#include "ComputeDataProcessor.h"

class CAccessSwitchModel;
class CComputeAccessSwitchDataProcessor :
	public CComputeDataProcessor
{
public:
	CComputeAccessSwitchDataProcessor(const string& strCfgFile);
	~CComputeAccessSwitchDataProcessor(void);
protected:
	bool Connect();
	bool LoadData();	
};
