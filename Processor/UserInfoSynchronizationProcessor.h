#pragma once
#include "SynchronizationProcessor.h"

class CCollectorModel;
class CUserController;
class CMISUserSynchronization;

class CUserInfoSynchronizationProcessor :
	public CSynchronizationProcessor
{
public:
	CUserInfoSynchronizationProcessor(const string& strCfgFile);
	~CUserInfoSynchronizationProcessor(void);
	void CompareFullUserData(CCollectorModel* pCollectorInfo);
protected:
	bool Connect();	
protected:
	CMISUserSynchronization *m_pMISUserSync;
	CUserController *m_pUserController;
};
