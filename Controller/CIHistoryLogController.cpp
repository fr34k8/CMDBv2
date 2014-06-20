#include "CIHistoryLogController.h"

CCIHistoryLogController::CCIHistoryLogController(void)
{
}

CCIHistoryLogController::~CCIHistoryLogController(void)
{
}

bool CCIHistoryLogController::InsertHistoryLog(BSONObj boCIInfoChangeRecord, long long lClock)
{
	string strTableName;
	strTableName = m_strTableName + "_" + CUtilities::GetSuffixPartition(lClock);
	return Insert(strTableName,boCIInfoChangeRecord);
}