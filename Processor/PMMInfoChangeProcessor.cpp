#include "PMMInfoChangeProcessor.h"
#include "../Controller/PMMController.h"
#include "../Controller/PMMInfoChangeController.h"
#include "../Model/PMMInfoChangeModel.h"

CPMMInfoChangeProcessor::CPMMInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CPMMController();
	m_pCIInfoChangeController = new CPMMInfoChangeController();
	m_pCIInfoChangeModel = new CPMMInfoChangeModel();
}

CPMMInfoChangeProcessor::~CPMMInfoChangeProcessor(void)
{
}
