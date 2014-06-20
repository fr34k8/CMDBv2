#include "ProductInfoChangeProcessor.h"
#include "../Controller/ProductController.h"
#include "../Controller/ProductInfoChangeController.h"
#include "../Model/ProductInfoChangeModel.h"

CProductInfoChangeProcessor::CProductInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CProductController();
	m_pCIInfoChangeController = new CProductInfoChangeController();
	m_pCIInfoChangeModel = new CProductInfoChangeModel();	
}

CProductInfoChangeProcessor::~CProductInfoChangeProcessor(void)
{
}
