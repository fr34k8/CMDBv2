#pragma once
#include "Processor.h"

class CCMDBController;
class CInternalDataCheckProcessor :
	public CProcessor
{
public:
	CInternalDataCheckProcessor(const string& strFileName);
	virtual ~CInternalDataCheckProcessor(void);

	void ProceedCheckDataInfo();
protected:
	virtual bool Connect();
	virtual bool LoadData() { return false; }
	virtual void CheckData() {}

protected:
	CCMDBController* m_pCIController;
};
