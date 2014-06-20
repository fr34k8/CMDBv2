#include "AccessSwitchInfoChangeProcessor.h"
#include "../Controller/AccessSwitchController.h"
#include "../Controller/AccessSwitchInfoChangeController.h"
#include "../Model/AccessSwitchInfoChangeModel.h"

CAccessSwitchInfoChangeProcessor::CAccessSwitchInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CAccessSwitchController();
	m_pCIInfoChangeController = new CAccessSwitchInfoChangeController();
	m_pCIInfoChangeModel = new CAccessSwitchInfoChangeModel();
}

CAccessSwitchInfoChangeProcessor::~CAccessSwitchInfoChangeProcessor(void)
{
}
