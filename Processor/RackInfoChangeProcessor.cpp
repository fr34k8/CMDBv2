#include "RackInfoChangeProcessor.h"
#include "../Controller/RackController.h"
#include "../Controller/RackInfoChangeController.h"
#include "../Model/RackInfoChangeModel.h"

CRackInfoChangeProcessor::CRackInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CRackController();
	m_pCIInfoChangeController = new CRackInfoChangeController();
	m_pCIInfoChangeModel = new CRackInfoChangeModel();
}

CRackInfoChangeProcessor::~CRackInfoChangeProcessor(void)
{
}
