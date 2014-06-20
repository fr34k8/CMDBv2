#include "CoreSwitchInfoIndexProcessor.h"
#include "CoreSwitchIndexPooler.h"
#include "../Controller/CoreSwitchInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CCoreSwitchInfoIndexProcessor::CCoreSwitchInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;
	m_pCIInfoChangeController = new CCoreSwitchInfoChangeController();
}

CCoreSwitchInfoIndexProcessor::~CCoreSwitchInfoIndexProcessor(void)
{
}

void* CCoreSwitchInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CCoreSwitchIndexPooler *pCoreSwitchIndexPooler = new CCoreSwitchIndexPooler("Config.ini");
		pCoreSwitchIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pCoreSwitchIndexPooler;
	}
}

void CCoreSwitchInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetCoreSwitchIndexPooler();
	CCIInfoIndexProcessor::ProceedInfoIndex();
}