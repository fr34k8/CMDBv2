#include "PMMInfoIndexProcessor.h"
#include "PMMIndexPooler.h"
#include "../Controller/PMMInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CPMMInfoIndexProcessor::CPMMInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;
	m_pCIInfoChangeController = new CPMMInfoChangeController();
}

CPMMInfoIndexProcessor::~CPMMInfoIndexProcessor(void)
{
}

void* CPMMInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CPMMIndexPooler *pPMMIndexPooler = new CPMMIndexPooler("Config.ini");
		pPMMIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pPMMIndexPooler;
	}
}

void CPMMInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetPMMIndexPooler();	
	CCIInfoIndexProcessor::ProceedInfoIndex();
}
