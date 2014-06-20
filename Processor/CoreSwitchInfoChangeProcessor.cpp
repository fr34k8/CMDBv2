#include "CoreSwitchInfoChangeProcessor.h"
#include "../Controller/CoreSwitchController.h"
#include "../Controller/CoreSwitchInfoChangeController.h"
#include "../Model/CoreSwitchInfoChangeModel.h"

CCoreSwitchInfoChangeProcessor::CCoreSwitchInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CCoreSwitchController();
	m_pCIInfoChangeController = new CCoreSwitchInfoChangeController();
	m_pCIInfoChangeModel = new CCoreSwitchInfoChangeModel();
}

CCoreSwitchInfoChangeProcessor::~CCoreSwitchInfoChangeProcessor(void)
{
}
