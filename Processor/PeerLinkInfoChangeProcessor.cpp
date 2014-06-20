#include "PeerLinkInfoChangeProcessor.h"
#include "../Controller/PeerLinkController.h"
#include "../Controller/PeerLinkInfoChangeController.h"
#include "../Model/PeerLinkInfoChangeModel.h"

CPeerLinkInfoChangeProcessor::CPeerLinkInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CPeerLinkController();
	m_pCIInfoChangeController = new CPeerLinkInfoChangeController();
	m_pCIInfoChangeModel = new CPeerLinkInfoChangeModel();
}

CPeerLinkInfoChangeProcessor::~CPeerLinkInfoChangeProcessor(void)
{
}
