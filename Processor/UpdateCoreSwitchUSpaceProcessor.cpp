#include "UpdateCoreSwitchUSpaceProcessor.h"
#include "../Controller/CoreSwitchController.h"

CUpdateCoreSwitchUSpaceProcessor::CUpdateCoreSwitchUSpaceProcessor(const string& strFileName)
:CUpdateCIUSpaceProcessor(strFileName)
{
	m_pCIController = new CCoreSwitchController();
}

CUpdateCoreSwitchUSpaceProcessor::~CUpdateCoreSwitchUSpaceProcessor(void)
{
}

bool CUpdateCoreSwitchUSpaceProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	return CProcessor::Connect();
}