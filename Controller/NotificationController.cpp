#include "NotificationController.h"

CNotificationController::CNotificationController(void)
{
}

CNotificationController::~CNotificationController(void)
{
}

bool CNotificationController::SetStatus()
{
	return true;
}

bool CNotificationController::InsertHistory(BSONObj boHistoricalRecord)
{
	bool bResult;
	string strPartitionTable;
	long long lCreatedData;
	try{
		lCreatedData = atol(CUtilities::GetCurrTimeStamp().c_str());
		strPartitionTable = m_strTableName + "_" + CUtilities::GetSuffixPartition(lCreatedData);
		bResult = Insert(strPartitionTable, boHistoricalRecord);
	}
	catch (exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CNotificationController", "InsertHistory", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bResult;
}
