#include "ChassisInfoIndexProcessor.h"
#include "ChassisIndexPooler.h"
#include "../Controller/ChassisInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CChassisInfoIndexProcessor::CChassisInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;
	m_pCIInfoChangeController = new CChassisInfoChangeController();
}

CChassisInfoIndexProcessor::~CChassisInfoIndexProcessor(void)
{
}

void* CChassisInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CChassisIndexPooler *pChassisIndexPooler = new CChassisIndexPooler("Config.ini");
		pChassisIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pChassisIndexPooler;
	}
}

void CChassisInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetChassisIndexPooler();
	CCIInfoIndexProcessor::ProceedInfoIndex();
}