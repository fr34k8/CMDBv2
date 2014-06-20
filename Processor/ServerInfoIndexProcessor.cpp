#include "ServerInfoIndexProcessor.h"
#include "ServerIndexPooler.h"
#include "../Controller/ServerInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CServerInfoIndexProcessor::CServerInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;	
	m_pCIInfoChangeController = new CServerInfoChangeController();	
}

CServerInfoIndexProcessor::~CServerInfoIndexProcessor(void)
{	
}

void* CServerInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if ( pCIIndexPoolerModel->GetLength() > 0 ) {
		CServerIndexPooler *pServerIndexPooler = new CServerIndexPooler("Config.ini");
		pServerIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pServerIndexPooler;
	}	
}

void CServerInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetServerIndexPooler();
	CCIInfoIndexProcessor::ProceedInfoIndex();
}
