#include "DivisionInfoChangeProcessor.h"
#include "../Controller/DivisionController.h"
#include "../Controller/DivisionInfoChangeController.h"
#include "../Model/DivisionInfoChangeModel.h"

CDivisionInfoChangeProcessor::CDivisionInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{	
	m_pCIController = new CDivisionController();
	m_pCIInfoChangeController = new CDivisionInfoChangeController();
	m_pCIInfoChangeModel = new CDivisionInfoChangeModel();	
}

CDivisionInfoChangeProcessor::~CDivisionInfoChangeProcessor(void)
{	
}