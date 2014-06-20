#include "UpdateServerUSpaceProcessor.h"
#include "../Controller/ServerController.h"

CUpdateServerUSpaceProcessor::CUpdateServerUSpaceProcessor(const string& strFileName)
:CUpdateCIUSpaceProcessor(strFileName)
{
	m_pCIController = new CServerController();
}

CUpdateServerUSpaceProcessor::~CUpdateServerUSpaceProcessor(void)
{
}

bool CUpdateServerUSpaceProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	return CProcessor::Connect();
}

auto_ptr<DBClientCursor> CUpdateServerUSpaceProcessor::LoadDB()
{
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	CServerController* pServerController = dynamic_cast<CServerController*>(m_pCIController);
	if (NULL != pServerController)
	{
		pServerController->FindServerU(ptrResultCursor);
	}
	return ptrResultCursor;
}

int CUpdateServerUSpaceProcessor::CalculateUSpace(BSONObj boRecord)
{
	int iUSpace = 0;
	if (boRecord.hasField("server_model"))
	{
		iUSpace = m_mapModel2Space[boRecord.getStringField("server_model")];
	}
	return iUSpace;
}