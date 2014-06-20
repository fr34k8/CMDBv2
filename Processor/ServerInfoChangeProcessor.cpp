#include "ServerInfoChangeProcessor.h"
#include "../Controller/ServerController.h"
#include "../Controller/ServerInfoChangeController.h"
#include "../Model/ServerInfoChangeModel.h"

CServerInfoChangeProcessor::CServerInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CServerController();
	m_pCIInfoChangeController = new CServerInfoChangeController();
	m_pCIInfoChangeModel = new CServerInfoChangeModel();	
}

CServerInfoChangeProcessor::~CServerInfoChangeProcessor(void)
{	
}

//auto_ptr<DBClientCursor> CServerInfoChangeProcessor::LoadDB()
//{
//	auto_ptr<DBClientCursor> ptrResultCursor;
//	ptrResultCursor = m_pCIController->Find(BSON("department_alias"<<"IS"));
//	try
//	{
//		if(!ptrResultCursor->more())
//		{
//			//CUtilities::WriteErrorLog(CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeProcessor", "LoadDB()", "FAIL"));
//		}
//		return ptrResultCursor;
//	}
//	catch(exception& ex)
//	{	
//		stringstream strErrorMess;
//		string strLog;
//		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
//		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeProcessor", "LoadDB()","exception:" + strErrorMess.str());
//		CUtilities::WriteErrorLog(strLog);
//	}
//}