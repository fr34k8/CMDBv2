#include "SwitchInfoChangeProcessor.h"
#include "../Controller/SwitchController.h"
#include "../Controller/SwitchInfoChangeController.h"
#include "../Model/SwitchInfoChangeModel.h"

CSwitchInfoChangeProcessor::CSwitchInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CSwitchController();
	m_pCIInfoChangeController = new CSwitchInfoChangeController();
	m_pCIInfoChangeModel = new CSwitchInfoChangeModel();
}

CSwitchInfoChangeProcessor::~CSwitchInfoChangeProcessor(void)
{
}
