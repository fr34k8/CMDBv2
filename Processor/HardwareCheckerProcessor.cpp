#include "HardwareCheckerProcessor.h"
#include "../Controller/CollectorController.h"
#include "../Controller/HardwareCheckerController.h"
#include "../Model/CollectorModel.h"
#include "../DataChecker/HardwareChecker.h"

CHardwareCheckerProcessor::CHardwareCheckerProcessor(const string& strCfgFile)
:CCheckerProcessor(strCfgFile)
{	
	m_pHardwareChecker = new CHardwareChecker();
	m_pHardwareCheckerController = new CHardwareCheckerController();
}

CHardwareCheckerProcessor::~CHardwareCheckerProcessor(void)
{	
	if (NULL != m_pHardwareChecker)
		delete m_pHardwareChecker;
	if (NULL != m_pHardwareCheckerController)
		delete m_pHardwareCheckerController;
}

bool CHardwareCheckerProcessor::Connect()
{		
	// Register controllers before connecting to database
	RegisterController(m_pCollectorInfoController);
	RegisterController(m_pHardwareCheckerController);
	return CProcessor::Connect();
}

void CHardwareCheckerProcessor::CheckHardwareInfo(CCollectorModel* pCollectorInfo)
{
	m_pHardwareCheckerController->CompareHardwareWithSnS(pCollectorInfo, m_pHardwareChecker);
}