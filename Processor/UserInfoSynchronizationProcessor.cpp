#include "UserInfoSynchronizationProcessor.h"
#include "../Controller/CollectorController.h"
#include "../Controller/UserController.h"
#include "../Model/CollectorModel.h"
#include "../Synchronization/MISUserSynchronization.h"

CUserInfoSynchronizationProcessor::CUserInfoSynchronizationProcessor(const string& strCfgFile)
:CSynchronizationProcessor(strCfgFile)
{	
	m_pMISUserSync = new CMISUserSynchronization();
	m_pUserController = new CUserController();
}

CUserInfoSynchronizationProcessor::~CUserInfoSynchronizationProcessor(void)
{	
	if (NULL != m_pMISUserSync)
		delete m_pMISUserSync;

	if (NULL != m_pUserController)
		delete m_pUserController;
}

bool CUserInfoSynchronizationProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCollectorInfoController);
	RegisterController(m_pUserController);
	return CProcessor::Connect();
}

void CUserInfoSynchronizationProcessor::CompareFullUserData(CCollectorModel* pCollectorInfo)
{
	char *pData;
	char *pTmpDataInfo;
	char *pUrlParameter;
	
	pUrlParameter = NULL;
	if (m_pMISUserSync->Synchronize(pUrlParameter, pCollectorInfo, &pTmpDataInfo))
	{
		pData = pTmpDataInfo;
		if (NULL != pData)
		{
			cout << "Data:" << pData << endl;
			m_pUserController->CompareFullData(pCollectorInfo, pData);
			delete pData;
		}
	}
}
