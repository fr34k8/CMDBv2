#include "Thread.h"
#include "../Utilities/Utilities.h"
#include "../Common/Common.h"

CThread::CThread(ThreadFunc pFun, void* pData)
{
	int iResult = pthread_create(&m_hThread, NULL, pFun, pData);
	if (iResult != 0)
	{
		m_bIsCreated = false;
		CUtilities::WriteErrorLog(ERROR_MSG, CUtilities::FormatLog(ERROR_MSG, "CThread", "CThread()", "FAIL CREATE THREAD"));
	}
	else
	{
		m_bIsCreated = true;
	}
}

CThread::~CThread(void)
{
}

int CThread::Wait()
{
	if (!m_bIsCreated)
	{
		return -1;
	}
	else
	{
		try
		{
			return pthread_join(m_hThread, NULL);
		}
		catch(exception& ex)
		{
			stringstream strErrorMess;
			string strLog;
			strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CThread", "Wait():pthread_join","exception:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		}
	}
}
