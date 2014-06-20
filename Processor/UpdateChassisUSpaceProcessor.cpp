#include "UpdateChassisUSpaceProcessor.h"
#include "../Controller/ChassisController.h"

CUpdateChassisUSpaceProcessor::CUpdateChassisUSpaceProcessor(const string& strFileName)
:CUpdateCIUSpaceProcessor(strFileName)
{
	m_pCIController = new CChassisController();
}

CUpdateChassisUSpaceProcessor::~CUpdateChassisUSpaceProcessor(void)
{
}

bool CUpdateChassisUSpaceProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	return CProcessor::Connect();
}

auto_ptr<DBClientCursor> CUpdateChassisUSpaceProcessor::LoadMapDB()
{
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	string strTableName;
	strTableName = TBL_CI_SPACE;
	ptrResultCursor = m_pCIController->Find(strTableName, QUERY("type" << CI_TYPE_CHASSIS));
	return ptrResultCursor;
}