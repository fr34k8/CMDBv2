#include "AggregationSwitchInfoChangeProcessor.h"
#include "../Controller/AggregationSwitchController.h"
#include "../Controller/AggregationSwitchInfoChangeController.h"
#include "../Model/AggregationSwitchInfoChangeModel.h"

CAggregationSwitchInfoChangeProcessor::CAggregationSwitchInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CAggregationSwitchController();
	m_pCIInfoChangeController = new CAggregationSwitchInfoChangeController();
	m_pCIInfoChangeModel = new CAggregationSwitchInfoChangeModel();
}

CAggregationSwitchInfoChangeProcessor::~CAggregationSwitchInfoChangeProcessor(void)
{
}
