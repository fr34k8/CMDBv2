#include "PeerLinkInfoUpdateProcessor.h"
#include "../Controller/PeerLinkController.h"
#include "../Controller/PeerLinkInfoChangeController.h"
#include "../Controller/PeerLinkInfoUpdateController.h"
#include "../Controller/PeerLinkHistoryLogController.h"
#include "../Model/PeerLinkInfoChangeModel.h"
#include "../Model/PeerLinkHistoryLogModel.h"

CPeerLinkInfoUpdateProcessor::CPeerLinkInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController = new CPeerLinkInfoUpdateController();
	m_pCIInfoChangeController = new CPeerLinkInfoChangeController();
	m_pCMDBController = new CPeerLinkController();
	m_pCIHistoryLogController = new CPeerLinkHistoryLogController();
	m_pCIHistoryLogModel = new CPeerLinkHistoryLogModel();
	m_pCIInfoChangeModel = new CPeerLinkInfoChangeModel();
}

CPeerLinkInfoUpdateProcessor::~CPeerLinkInfoUpdateProcessor(void)
{
}