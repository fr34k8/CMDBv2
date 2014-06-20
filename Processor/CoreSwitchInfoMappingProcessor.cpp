#include "CoreSwitchInfoMappingProcessor.h"
#include "../Controller/CoreSwitchController.h"
#include "../Model/CoreSwitchModel.h"

CCoreSwitchInfoMappingProcessor::CCoreSwitchInfoMappingProcessor(const string& strFileName)
:CCIInfoMappingProcessor(strFileName)
{
	m_pCIController = new CCoreSwitchController();
	m_pCIModel = new CCoreSwitchModel();
	m_pCIModel->SetCIType(CI_TYPE_CORE_SWITCH);
}

CCoreSwitchInfoMappingProcessor::~CCoreSwitchInfoMappingProcessor(void)
{
}

bool CCoreSwitchInfoMappingProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	return CProcessor::Connect();
}
