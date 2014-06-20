#pragma once
#include "CheckerController.h"

class CCollectorModel;
class CServerStatisticCheckerModel;

class CServerStatisticCheckerController :
	public CCheckerController
{
public:
	CServerStatisticCheckerController(void);
	~CServerStatisticCheckerController(void);
	
	//----------- Compare Server Statistic ---------//
	void CompareServerStatisticWithSnS(CCollectorModel *pCollectorInfo, char* pData);
	void SaveServerStatisticChecker(const string& strTableName, CServerStatisticCheckerModel objServStatistic);
	//----------------------------------------------//
};
