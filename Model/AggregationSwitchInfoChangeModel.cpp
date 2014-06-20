#include "AggregationSwitchInfoChangeModel.h"

CAggregationSwitchInfoChangeModel::CAggregationSwitchInfoChangeModel(void)
{
	InitLookUpMap();
}

CAggregationSwitchInfoChangeModel::~CAggregationSwitchInfoChangeModel(void)
{
}

void CAggregationSwitchInfoChangeModel::InitLookUpByPass()
{
	m_mapLookUpByPass["aggregation_switch_id"] = true;
}