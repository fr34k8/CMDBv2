#include "RackInfoIndexProcessor.h"
#include "RackIndexPooler.h"
#include "../Controller/RackInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CRackInfoIndexProcessor::CRackInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;	
	m_pCIInfoChangeController = new CRackInfoChangeController();
}

CRackInfoIndexProcessor::~CRackInfoIndexProcessor(void)
{
}

void* CRackInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CRackIndexPooler *pRackIndexPooler = new CRackIndexPooler("Config.ini");
		pRackIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pRackIndexPooler;
	}
}

void CRackInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetRackIndexPooler();
	CCIInfoIndexProcessor::ProceedInfoIndex();
}