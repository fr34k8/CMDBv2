#include "AggregationSwitchInfoIndexProcessor.h"
#include "AggregationSwitchIndexPooler.h"
#include "../Controller/AggregationSwitchInfoChangeController.h"
#include "../Config/ConfigFile.h"
#include "../Model/CIIndexPoolerModel.h"

CAggregationSwitchInfoIndexProcessor::CAggregationSwitchInfoIndexProcessor(const string& strCfgFile)
:CCIInfoIndexProcessor(strCfgFile)
{
	m_pFuncStartPoller = &StartPooler;
	m_pCIInfoChangeController = new CAggregationSwitchInfoChangeController();
}

CAggregationSwitchInfoIndexProcessor::~CAggregationSwitchInfoIndexProcessor(void)
{
}

void* CAggregationSwitchInfoIndexProcessor::StartPooler(void *pData)
{
	CCIIndexPoolerModel* pCIIndexPoolerModel = static_cast<CCIIndexPoolerModel*>(pData);
	cout << "Pooler was born! Be given a vector of: " << pCIIndexPoolerModel->GetLength() << " elements" << endl;
	if (pCIIndexPoolerModel->GetLength() > 0) {
		CAggregationSwitchIndexPooler *pAggregationSwitchIndexPooler = new CAggregationSwitchIndexPooler("Config.ini");
		pAggregationSwitchIndexPooler->ProceedInfo(pCIIndexPoolerModel);
		delete pAggregationSwitchIndexPooler;
	}
}

void CAggregationSwitchInfoIndexProcessor::ProceedInfoIndex()
{
	m_nInfoIndexPooler = CConfigFile::GetInstance()->GetAggregationSwitchIndexPooler();
	CCIInfoIndexProcessor::ProceedInfoIndex();
}