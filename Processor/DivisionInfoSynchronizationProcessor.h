#pragma once
#include "SynchronizationProcessor.h"

class CCollectorModel;
class CMISDivisionSynchronization;

class CDivisionInfoSynchronizationProcessor :
	public CSynchronizationProcessor
{
public:
	CDivisionInfoSynchronizationProcessor(const string& strCfgFile);
	~CDivisionInfoSynchronizationProcessor(void);
	void CompareFullDivisionData(CCollectorModel* pCollectorInfo);
	void CompareChangeDivisionData(CCollectorModel* pCollectorInfo);
protected:
	CMISDivisionSynchronization *m_pMISDivisionSync;
};
