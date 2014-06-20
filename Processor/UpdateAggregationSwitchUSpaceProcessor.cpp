#include "UpdateAggregationSwitchUSpaceProcessor.h"
#include "../Controller/AggregationSwitchController.h"

CUpdateAggregationSwitchUSpaceProcessor::CUpdateAggregationSwitchUSpaceProcessor(const string& strFileName)
:CUpdateCIUSpaceProcessor(strFileName)
{
	m_pCIController = new CAggregationSwitchController();
}

CUpdateAggregationSwitchUSpaceProcessor::~CUpdateAggregationSwitchUSpaceProcessor(void)
{
}

bool CUpdateAggregationSwitchUSpaceProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	return CProcessor::Connect();
}