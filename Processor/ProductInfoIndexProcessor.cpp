#include "ProductInfoIndexProcessor.h"
#include "ProductIndexPooler.h"
#include "../Controller/ProductInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CProductInfoIndexProcessor::CProductInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;
	m_pCIInfoChangeController = new CProductInfoChangeController();
}

CProductInfoIndexProcessor::~CProductInfoIndexProcessor(void)
{
}

void* CProductInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;	
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CProductIndexPooler *pProductIndexPooler = new CProductIndexPooler("Config.ini");
		pProductIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pProductIndexPooler;
	}	
}

void CProductInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetProductIndexPooler();
	cout << "Pooler number is:" << m_nInfoIndexPooler << endl;
	
	CCIInfoIndexProcessor::ProceedInfoIndex();
}