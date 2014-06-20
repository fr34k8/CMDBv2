#include "PDUInfoIndexProcessor.h"
#include "PDUIndexPooler.h"
#include "../Controller/PDUInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CPDUInfoIndexProcessor::CPDUInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;
	m_pCIInfoChangeController = new CPDUInfoChangeController();
}

CPDUInfoIndexProcessor::~CPDUInfoIndexProcessor(void)
{
}

void* CPDUInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CPDUIndexPooler *pPDUIndexPooler = new CPDUIndexPooler("Config.ini");
		pPDUIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pPDUIndexPooler;
	}
}

void CPDUInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetPDUIndexPooler();
	CCIInfoIndexProcessor::ProceedInfoIndex();
}