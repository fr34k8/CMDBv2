#include "RowInfoIndexProcessor.h"
#include "RowIndexPooler.h"
#include "../Controller/RowInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CRowInfoIndexProcessor::CRowInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;
	m_pCIInfoChangeController = new CRowInfoChangeController();
}

CRowInfoIndexProcessor::~CRowInfoIndexProcessor(void)
{
}

void* CRowInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CRowIndexPooler *pRowIndexPooler = new CRowIndexPooler("Config.ini");
		pRowIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pRowIndexPooler;
	}
}

void CRowInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetRowIndexPooler();
	CCIInfoIndexProcessor::ProceedInfoIndex();
}