#pragma once
#include "CheckerProcessor.h"

class CCollectorModel;
class CHardwareChecker;
class CHardwareCheckerController;

class CHardwareCheckerProcessor :
	public CCheckerProcessor
{
public:
	CHardwareCheckerProcessor(const string& strCfgFile);
	~CHardwareCheckerProcessor(void);
	void CheckHardwareInfo(CCollectorModel* pCollectorInfo);
protected:
	bool Connect();	
protected:
	CHardwareChecker *m_pHardwareChecker;
	CHardwareCheckerController *m_pHardwareCheckerController;
};
