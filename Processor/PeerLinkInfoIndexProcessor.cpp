#include "PeerLinkInfoIndexProcessor.h"
#include "PeerLinkIndexPooler.h"
#include "../Controller/PeerLinkInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CPeerLinkInfoIndexProcessor::CPeerLinkInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;
	m_pCIInfoChangeController = new CPeerLinkInfoChangeController();
}

CPeerLinkInfoIndexProcessor::~CPeerLinkInfoIndexProcessor(void)
{
}

void* CPeerLinkInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CPeerLinkIndexPooler *pPeerLinkIndexPooler = new CPeerLinkIndexPooler("Config.ini");
		pPeerLinkIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pPeerLinkIndexPooler;
	}
}

void CPeerLinkInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetPeerLinkIndexPooler();
	CCIInfoIndexProcessor::ProceedInfoIndex();
}