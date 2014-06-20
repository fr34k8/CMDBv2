#include "AggregationSwitchInfoMappingProcessor.h"
#include "../Controller/AggregationSwitchController.h"
#include "../Model/AggregationSwitchModel.h"

CAggregationSwitchInfoMappingProcessor::CAggregationSwitchInfoMappingProcessor(const string& strFileName)
:CCIInfoMappingProcessor(strFileName)
{
	m_pCIController = new CAggregationSwitchController();
	m_pCIModel = new CAggregationSwitchModel();
	m_pCIModel->SetCIType(CI_TYPE_AGGREGATION_SWITCH);
}

CAggregationSwitchInfoMappingProcessor::~CAggregationSwitchInfoMappingProcessor(void)
{
}

bool CAggregationSwitchInfoMappingProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	return CProcessor::Connect();
}
