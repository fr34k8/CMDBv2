#include "DepartmentInfoIndexProcessor.h"
#include "DepartmentIndexPooler.h"
#include "../Controller/DepartmentInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CDepartmentInfoIndexProcessor::CDepartmentInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;
	m_pCIInfoChangeController = new CDepartmentInfoChangeController();
}

CDepartmentInfoIndexProcessor::~CDepartmentInfoIndexProcessor(void)
{
}

void* CDepartmentInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CDepartmentIndexPooler *pDepartmentIndexPooler = new CDepartmentIndexPooler("Config.ini");
		pDepartmentIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pDepartmentIndexPooler;
	}
}

void CDepartmentInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetDepartmentIndexPooler();
	CCIInfoIndexProcessor::ProceedInfoIndex();
}