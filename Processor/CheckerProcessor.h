#pragma once
#include "Processor.h"

class CCollectorController;
class CCollectorModel;

class CCheckerProcessor :
	public CProcessor
{
public:
	CCheckerProcessor(const string& strFileName);
	virtual ~CCheckerProcessor(void);

	void ProceedCheckDataInfo(const string& strCollectorName);
	virtual void CheckServerStatistic(CCollectorModel* pCollectorInfo){};
	virtual void CheckHardwareInfo(CCollectorModel* pCollectorInfo){};
	virtual void CheckInterfaceInfo(CCollectorModel* pCollectorInfo){};
protected:
	CCollectorController* m_pCollectorInfoController;
};
