#include "ServerCheckerProcessor.h"
#include "../Controller/CollectorController.h"
#include "../Controller/ServerStatisticCheckerController.h"
#include "../Model/CollectorModel.h"
#include "../DataChecker/ServerChecker.h"

CServerCheckerProcessor::CServerCheckerProcessor(const string& strCfgFile)
:CCheckerProcessor(strCfgFile)
{	
	m_pServerChecker = new CServerChecker();
	m_pServerStatisticCheckerController = new CServerStatisticCheckerController();
}

CServerCheckerProcessor::~CServerCheckerProcessor(void)
{	
	if (NULL != m_pServerChecker)
		delete m_pServerChecker;
	if (NULL != m_pServerStatisticCheckerController)
		delete m_pServerStatisticCheckerController;
}

bool CServerCheckerProcessor::Connect()
{		
	// Register controllers before connecting to database
	RegisterController(m_pCollectorInfoController);
	RegisterController(m_pServerStatisticCheckerController);
	return CProcessor::Connect();
}
void CServerCheckerProcessor::CheckServerStatistic(CCollectorModel* pCollectorInfo)
{
	char *pData;
	pData = NULL;
	
	pData = m_pServerChecker->CallSnSService(pCollectorInfo);
	if (NULL != pData)
	{
		cout << "Data:" << pData << endl;
		m_pServerStatisticCheckerController->CompareServerStatisticWithSnS(pCollectorInfo, pData);
		delete pData;
	}
}