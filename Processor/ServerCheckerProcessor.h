#pragma once
#include "CheckerProcessor.h"

class CCollectorModel;
class CServerChecker;
class CServerStatisticCheckerController;

class CServerCheckerProcessor :
	public CCheckerProcessor
{
public:
	CServerCheckerProcessor(const string& strCfgFile);
	~CServerCheckerProcessor(void);
	void CheckServerStatistic(CCollectorModel* pCollectorInfo);
protected:
	bool Connect();	
protected:
	CServerChecker *m_pServerChecker;
	CServerStatisticCheckerController *m_pServerStatisticCheckerController;
};
