#include "CIInfoChangeProcessor.h"
#include "../Controller/CMDBController.h"
#include "../Controller/CIInfoChangeController.h"
#include "../Model/CIInfoChangeModel.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"

CCIInfoChangeProcessor::CCIInfoChangeProcessor(const string& strFileName)
:CProcessor(strFileName)
{	
}

CCIInfoChangeProcessor::~CCIInfoChangeProcessor(void)
{	
	if (NULL != m_pCIController)
	{
		delete m_pCIController;
	}

	if (NULL != m_pCIInfoChangeController)
	{
		delete m_pCIInfoChangeController;
	}

	if (NULL != m_pCIInfoChangeModel)
	{
		delete m_pCIInfoChangeModel;
	}
}

auto_ptr<DBClientCursor> CCIInfoChangeProcessor::LoadDB()
{
	int i;
	string strOID;
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	//===================HOTFIX CODE===========================
	/*BSONArrayBuilder babOIDArray;
	StringArray vOID;
	strOID = m_pConfigFile->GetHostFixID();
	cout << strOID << endl;
	vOID = CUtilities::SplitString(strOID, ",");
	for (i = 0; i < vOID.size(); i++)
	{
		babOIDArray << OID(vOID[i]);
	}
	ptrResultCursor = m_pCIController->Find(QUERY("_id" << BSON("$in" << babOIDArray.arr())));*/
	//==========================================================
	ptrResultCursor = m_pCIController->Find();
	try
	{
		if(!ptrResultCursor->more())
		{
			//CUtilities::WriteErrorLog(CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeProcessor", "LoadDB()", "FAIL"));
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeProcessor", "LoadDB()","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return ptrResultCursor;
}


bool CCIInfoChangeProcessor::ProceedMiningRecord(BSONObj &boCIInfoRecord)
{
	vector<BSONObj> vMiningCursor;
	try
	{
		/*
			Mining changed info
		*/
		vMiningCursor = m_pCIInfoChangeModel->GetMiningCursor(boCIInfoRecord);
		for(int i=0; i<vMiningCursor.size(); i++)
		{
			if(!m_pCIInfoChangeController->Insert(vMiningCursor[i]))
			{
				CUtilities::WriteErrorLog(ERROR_MSG, CUtilities::FormatLog(ERROR_MSG, "CServerInfoChangeProcessor", "ProceedMiningRecord(BSONObj)", "FAIL:Insert"));
				return false;
			}
		}
		return true;
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CServerInfoChangeProcessor", "ProceedMiningRecord(BSONObj)","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return false;
}

bool CCIInfoChangeProcessor::Connect()
{	
	// Register controllers before connecting to database
	RegisterController(m_pCIController);
	RegisterController(m_pCIInfoChangeController);

	return CProcessor::Connect();
}

bool CCIInfoChangeProcessor::ProceedMining()
{
	cout<<"In ProceedMining."<<endl;
	// Connect to database
	if(!Connect())
	{
		return false;
	}

	cout<<"Database connected."<<endl;
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	BSONObj boCIInfoRecord;
	int iNextLoad = 0;
	try
	{
		while (true)
		{
			ptrResultCursor = m_pCIController->Find(Query(), LIMIT_MINING_RECORD, LIMIT_MINING_RECORD * iNextLoad);
			if (ptrResultCursor.get() == NULL || ptrResultCursor->more() == false)
			{
				return false;
			}

			int iCount = 1;
			while (ptrResultCursor->more())
			{
				boCIInfoRecord = ptrResultCursor->nextSafe();
				if (!ProceedMiningRecord(boCIInfoRecord))
				{
					CUtilities::WriteErrorLog(ERROR_MSG, CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeProcessor", "ProceedMining()", "ProceedMiningRecord:FAIL"));
				}
			}
			ptrResultCursor.reset();
			sleep(LOAD_INFO_DELAY);
			iNextLoad++;
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeProcessor", "ProceedMining()","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}