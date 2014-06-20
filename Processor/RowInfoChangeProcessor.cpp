#include "RowInfoChangeProcessor.h"
#include "../Controller/RowController.h"
#include "../Controller/RowInfoChangeController.h"
#include "../Model/RowInfoChangeModel.h"

CRowInfoChangeProcessor::CRowInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CRowController();
	m_pCIInfoChangeController = new CRowInfoChangeController();
	m_pCIInfoChangeModel = new CRowInfoChangeModel();
}

CRowInfoChangeProcessor::~CRowInfoChangeProcessor(void)
{
}
