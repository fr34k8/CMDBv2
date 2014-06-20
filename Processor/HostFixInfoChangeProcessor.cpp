#include "HostFixInfoChangeProcessor.h"
#include "../Controller/CMDBController.h"
#include "../Controller/CIInfoChangeController.h"
#include "../Model/HostFixInfoChangeModel.h"

CHostFixInfoChangeProcessor::CHostFixInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CCMDBController();
	m_pCIInfoChangeController = new CCIInfoChangeController();
	m_pCIInfoChangeModel = new CHostFixInfoChangeModel();
}

CHostFixInfoChangeProcessor::~CHostFixInfoChangeProcessor(void)
{
}