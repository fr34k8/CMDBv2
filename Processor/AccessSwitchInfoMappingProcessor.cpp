#include "AccessSwitchInfoMappingProcessor.h"
#include "../Controller/AccessSwitchController.h"
#include "../Model/AccessSwitchModel.h"

CAccessSwitchInfoMappingProcessor::CAccessSwitchInfoMappingProcessor(const string& strFileName)
:CCIInfoMappingProcessor(strFileName)
{
	m_pCIController = new CAccessSwitchController();
	m_pCIModel = new CAccessSwitchModel();
	m_pCIModel->SetCIType(CI_TYPE_ACCESS_SWITCH);
}

CAccessSwitchInfoMappingProcessor::~CAccessSwitchInfoMappingProcessor(void)
{
}

bool CAccessSwitchInfoMappingProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	return CProcessor::Connect();
}
