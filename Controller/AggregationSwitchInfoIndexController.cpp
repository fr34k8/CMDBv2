#include "AggregationSwitchInfoIndexController.h"

CAggregationSwitchInfoIndexController::CAggregationSwitchInfoIndexController(void)
{
	m_strTableName = TBL_AGGREGATION_SWITCH_INVERTED_INDEX;
}

CAggregationSwitchInfoIndexController::~CAggregationSwitchInfoIndexController(void)
{
}

bool CAggregationSwitchInfoIndexController::RemoveInfoChange(Query queryRemoveCondition)
{
	return Remove(TBL_AGGREGATION_SWITCH_INFO_CHANGE,queryRemoveCondition);
}