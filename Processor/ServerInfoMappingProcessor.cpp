#include "ServerInfoMappingProcessor.h"
#include "../Controller/ServerController.h"
#include "../Model/ServerModel.h"

CServerInfoMappingProcessor::CServerInfoMappingProcessor(const string& strFileName)
:CCIInfoMappingProcessor(strFileName)
{
	m_pCIController = new CServerController();
	m_pCIModel = new CServerModel();
	m_pCIModel->SetCIType(CI_TYPE_SERVER);
}

CServerInfoMappingProcessor::~CServerInfoMappingProcessor(void)
{
}

bool CServerInfoMappingProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	return CProcessor::Connect();
}

auto_ptr<DBClientCursor> CServerInfoMappingProcessor::LoadDB()
{
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	ptrResultCursor = m_pCIController->Find(QUERY("server_type" << BSON("$in" << BSON_ARRAY(SERVER_U << SERVER_UNKNOWN)) << "deleted" << 0));
	return ptrResultCursor;
}
