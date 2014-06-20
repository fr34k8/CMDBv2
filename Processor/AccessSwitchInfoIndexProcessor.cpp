#include "AccessSwitchInfoIndexProcessor.h"
#include "AccessSwitchIndexPooler.h"
#include "../Controller/AccessSwitchInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CAccessSwitchInfoIndexProcessor::CAccessSwitchInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;
	m_pCIInfoChangeController = new CAccessSwitchInfoChangeController();
}

CAccessSwitchInfoIndexProcessor::~CAccessSwitchInfoIndexProcessor(void)
{
}

void* CAccessSwitchInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CAccessSwitchIndexPooler *pAccessSwitchIndexPooler = new CAccessSwitchIndexPooler("Config.ini");
		pAccessSwitchIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pAccessSwitchIndexPooler;
	}
}

void CAccessSwitchInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetAccessSwitchIndexPooler();
	CCIInfoIndexProcessor::ProceedInfoIndex();
}
