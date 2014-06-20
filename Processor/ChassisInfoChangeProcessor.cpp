#include "ChassisInfoChangeProcessor.h"
#include "../Controller/ChassisController.h"
#include "../Controller/ChassisInfoChangeController.h"
#include "../Model/ChassisInfoChangeModel.h"

CChassisInfoChangeProcessor::CChassisInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CChassisController();
	m_pCIInfoChangeModel = new CChassisInfoChangeModel();
	m_pCIInfoChangeController = new CChassisInfoChangeController();
}

CChassisInfoChangeProcessor::~CChassisInfoChangeProcessor(void)
{
}
