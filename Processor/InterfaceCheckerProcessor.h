#pragma once
#include "CheckerProcessor.h"

class CCollectorModel;
class CSDKService;
class CInterfaceCheckerController;

class CInterfaceCheckerProcessor :
	public CCheckerProcessor
{
public:
	CInterfaceCheckerProcessor(const string& strCfgFile);
	~CInterfaceCheckerProcessor(void);
	void CheckInterfaceInfo(CCollectorModel* pCollectorInfo);
protected:
	bool Connect();
protected:
	CSDKService *m_pSDKService;
	CInterfaceCheckerController *m_pInterfaceCheckerController;
};
