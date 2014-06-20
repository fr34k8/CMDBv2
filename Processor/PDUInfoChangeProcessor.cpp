#include "PDUInfoChangeProcessor.h"
#include "../Controller/PDUController.h"
#include "../Controller/PDUInfoChangeController.h"
#include "../Model/PDUInfoChangeModel.h"

CPDUInfoChangeProcessor::CPDUInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CPDUController();
	m_pCIInfoChangeController = new CPDUInfoChangeController();
	m_pCIInfoChangeModel = new CPDUInfoChangeModel();
}

CPDUInfoChangeProcessor::~CPDUInfoChangeProcessor(void)
{
}
