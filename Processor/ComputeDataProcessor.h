#pragma once
#include "Processor.h"

class CCMDBController;
class CComputeDataProcessor :
	public CProcessor
{
public:
	CComputeDataProcessor(const string& strCfgFile);
	virtual ~CComputeDataProcessor(void);
	void ProceedComputeData();
protected:
	virtual bool Connect();
	virtual bool LoadData() { return false; }
	virtual void ComputeData() {}
protected:
	CCMDBController* m_pCIController;
};
