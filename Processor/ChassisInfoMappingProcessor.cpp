#include "ChassisInfoMappingProcessor.h"
#include "../Controller/ChassisController.h"
#include "../Model/ChassisModel.h"

CChassisInfoMappingProcessor::CChassisInfoMappingProcessor(const string& strFileName)
:CCIInfoMappingProcessor(strFileName)
{
	m_pCIController = new CChassisController();
	m_pCIModel = new CChassisModel();
	m_pCIModel->SetCIType(CI_TYPE_CHASSIS);
}

CChassisInfoMappingProcessor::~CChassisInfoMappingProcessor(void)
{
}

bool CChassisInfoMappingProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	return CProcessor::Connect();
}