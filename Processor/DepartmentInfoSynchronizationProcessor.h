#pragma once
#include "SynchronizationProcessor.h"

class CCollectorModel;
class CMISDepartmentSynchronization;

class CDepartmentInfoSynchronizationProcessor :
	public CSynchronizationProcessor
{
public:
	CDepartmentInfoSynchronizationProcessor(const string& strCfgFile);
	~CDepartmentInfoSynchronizationProcessor(void);
	void CompareFullDepartmentData(CCollectorModel* pCollectorInfo);
	void CompareChangeDepartmentData(CCollectorModel* pCollectorInfo);
protected:
	CMISDepartmentSynchronization *m_pMISDepartmentSync;
};
