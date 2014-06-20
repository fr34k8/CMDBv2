#include "CIInfoIndexProcessor.h"
#include "../Controller/CIInfoChangeController.h"
#include "../Model/CIInfoIndexModel.h"
#include "../Model/CIIndexPoolerModel.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"
#include "Thread.h"

CCIInfoIndexProcessor::CCIInfoIndexProcessor(const string& strFileName)
:CProcessor(strFileName)
{
	m_nInfoIndexPooler = INFO_INDEX_POOLER;	
	m_nRecordCount = 0;
}

CCIInfoIndexProcessor::~CCIInfoIndexProcessor(void)
{	
	if (NULL != m_pCIInfoChangeController)
	{
		delete m_pCIInfoChangeController;
		m_pCIInfoChangeController = NULL;
	}
}

bool CCIInfoIndexProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIInfoChangeController);

	return CProcessor::Connect();
}

int CCIInfoIndexProcessor::CalculatePoolerNumber()
{
	/*
		Number of pooler will calculate depend on minimun pooler's number
		Pooler will be plus 1 if it has redudant.
	*/
	int nPooler = (m_nRecordCount / MIN_INDEX_POOLER_RECORD);
	if ((m_nRecordCount % MIN_INDEX_POOLER_RECORD) > 0)
	{
		nPooler = nPooler + 1;
	}
	if (nPooler > m_nInfoIndexPooler)
	{
		nPooler = m_nInfoIndexPooler;
	}
	return nPooler;
}

vector<CCIIndexPoolerModel*> CCIInfoIndexProcessor::PrepareIndexing(auto_ptr<DBClientCursor> &ptrInfoChangeCursor)
{
	int nCIInfoChangePoolerIndex;
	int nCurrentPoolerIndex = 0;
	vector<CCIIndexPoolerModel*> vtCIInfoIndexModelArray;
	
	int nPooler = CalculatePoolerNumber();

	for (int i = 0; i < nPooler; i++)
	{
		vtCIInfoIndexModelArray.push_back(new CCIIndexPoolerModel()); // Create Pooler Slot in array
	}

	map<BSONElement, int> mapObjId2PoolerIndex;

	while (ptrInfoChangeCursor->more()) {
		BSONObj oCIChangeInfo = ptrInfoChangeCursor->nextSafe();
		// declare model and assign value
		try
		{
			CCIInfoIndexModel *ptrCIInfoIndexModel = new CCIInfoIndexModel();
			BSONElement oCIObjectId = oCIChangeInfo["id"];
			nCIInfoChangePoolerIndex = ComputePoolerIndex(&nCurrentPoolerIndex, &mapObjId2PoolerIndex, 
															oCIObjectId, nPooler);
			ptrCIInfoIndexModel->Load(oCIChangeInfo);

			vtCIInfoIndexModelArray[nCIInfoChangePoolerIndex]->Push(ptrCIInfoIndexModel);
		}
		catch(exception& ex)
		{
			stringstream strErrorMess;
			string strLog;
			strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoIndexProcessor", "PrepareIndexing()","Exception:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		}
	}
	return vtCIInfoIndexModelArray;
}

int CCIInfoIndexProcessor::ComputePoolerIndex(int *pCurrentPoolerIndex,
											map<BSONElement, int> *mapObjId2PoolerIndex,
											BSONElement oCIObjectId,
											int nPooler)
{
	/*
		If the Map has contained the object id
		This Function will return Current Index of Pooler
		Else this Function will create a new index for pooler
		Index of pooler will reset to 0 if it's max
	*/
	int nCIInfoChangePoolerIndex;

	// check weather Object Id existed
	map<BSONElement, int>::iterator p = (*mapObjId2PoolerIndex).find(oCIObjectId);
	if (p != (*mapObjId2PoolerIndex).end()) {
		nCIInfoChangePoolerIndex = p->second;
	}
	else {
		nCIInfoChangePoolerIndex = *pCurrentPoolerIndex;
		(*mapObjId2PoolerIndex).insert(pair<BSONElement, int> (oCIObjectId, nCIInfoChangePoolerIndex));	

		// rotate current pooler index
		*pCurrentPoolerIndex = *pCurrentPoolerIndex + 1;
		if (*pCurrentPoolerIndex == nPooler) {
			*pCurrentPoolerIndex = 0;
		}
	}

	return nCIInfoChangePoolerIndex;
}


bool CCIInfoIndexProcessor::LoadDB(auto_ptr<DBClientCursor> &ptrResultCursor)
{
	bool bResult;
	bResult = m_pCIInfoChangeController->Find(ptrResultCursor, Query().sort("clock"));
	m_nRecordCount = m_pCIInfoChangeController->Count();
	if (!ptrResultCursor->more())
	{
		bResult = false;
	}
	return bResult;
}

void CCIInfoIndexProcessor::DestroyData(vector<CCIIndexPoolerModel*>& arrCIInfoIndexModelArray)
{	
	cout << "Destroying...\n";
	try
	{
		for (int i = 0; i < arrCIInfoIndexModelArray.size(); i++)
		{
			delete arrCIInfoIndexModelArray[i];		
		}
	}
	catch(exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoIndexProcessor", "DestroyData()","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CCIInfoIndexProcessor::ProceedInfoIndex()
{
	if (!Connect()) // Connecting all controllers 
	{
		return;
	}

	while (true)
	{		
		auto_ptr<DBClientCursor> ptrInfoChangeCursor = auto_ptr<DBClientCursor>();// = LoadDB(); // Load current change info on ci change table

		if (LoadDB(ptrInfoChangeCursor))
		{
			vector<CCIIndexPoolerModel*> vtCIInfoIndexModelArray;
			vtCIInfoIndexModelArray = PrepareIndexing(ptrInfoChangeCursor); // Convert Cursor change data to vector of vector pointer of Index model
			LaunchMultiPoolers(vtCIInfoIndexModelArray);
			DestroyData(vtCIInfoIndexModelArray);
			sleep(LOAD_INFO_DELAY);
		}
		else
		{
			//Sleep for a while
			sleep(LOAD_INFO_CHANGE_CYCLE);
		}
		ptrInfoChangeCursor.reset();
	}
}

void CCIInfoIndexProcessor::LaunchMultiPoolers(vector<CCIIndexPoolerModel*> vtCIInfoIndexModelArray)
{
	if (NULL == m_pFuncStartPoller)
	{
		return;
	}
	
	vector<CThread*> arrThreadPool;
	for(int i=0; i < vtCIInfoIndexModelArray.size(); i++) {
		try{
			// Check if there is data to proceed index
			if (vtCIInfoIndexModelArray[i]->GetLength() > 0)
			{
				CThread* pThread = new CThread(m_pFuncStartPoller, vtCIInfoIndexModelArray[i]);
				arrThreadPool.push_back(pThread);
			}			
		}
		catch(exception& ex)
		{
			stringstream strErrorMess;
			string strLog;
			strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoIndexProcessor", "LaunchMultiPoolers(vector<CIInfoIndexModelArray>):pthread_create","exception:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		}
	}

	// Wait for all threads to be stopped
	for(int i=0; i < arrThreadPool.size(); i++)
	{
		arrThreadPool[i]->Wait();
	}
		
	cout << "Exiting... " << endl;
}
