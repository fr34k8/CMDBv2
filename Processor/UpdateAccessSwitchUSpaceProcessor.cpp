#include "UpdateAccessSwitchUSpaceProcessor.h"
#include "../Controller/AccessSwitchController.h"

CUpdateAccessSwitchUSpaceProcessor::CUpdateAccessSwitchUSpaceProcessor(const string& strFileName)
:CUpdateCIUSpaceProcessor(strFileName)
{
	m_pCIController = new CAccessSwitchController();
}

CUpdateAccessSwitchUSpaceProcessor::~CUpdateAccessSwitchUSpaceProcessor(void)
{
}

bool CUpdateAccessSwitchUSpaceProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	return CProcessor::Connect();
}