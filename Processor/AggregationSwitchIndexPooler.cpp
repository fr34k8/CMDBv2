#include "AggregationSwitchIndexPooler.h"
#include "../Controller/AggregationSwitchInfoIndexController.h"

CAggregationSwitchIndexPooler::CAggregationSwitchIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CAggregationSwitchInfoIndexController();
}

CAggregationSwitchIndexPooler::~CAggregationSwitchIndexPooler(void)
{
}
