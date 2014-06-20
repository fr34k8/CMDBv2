#include "InternalServerDataCheckProcessor.h"
#include "../Controller/ServerController.h"
#include "../Model/ServerModel.h"

CInternalServerDataCheckProcessor::CInternalServerDataCheckProcessor(const string& strFileName)
:CInternalDataCheckProcessor(strFileName)
{
	m_pCIController = new CServerController();
}

CInternalServerDataCheckProcessor::~CInternalServerDataCheckProcessor(void)
{
	DestroyData();
}

bool CInternalServerDataCheckProcessor::CInternalServerDataCheckProcessor::LoadData()
{
	auto_ptr<DBClientCursor> ptrServerCursor = auto_ptr<DBClientCursor>();
	BSONObj boServerRecord;
	
	if (!((CServerController*)m_pCIController)->FindOperatingPhysicalServer(ptrServerCursor))
	{
		return false;
	}

	while (ptrServerCursor->more()) 
	{
		boServerRecord = ptrServerCursor->nextSafe();			
		LoadServer(boServerRecord);
	}

	return true;
}

void CInternalServerDataCheckProcessor::CheckLocation(ServerModelArray* pServerModelArray)
{
	CServerModel* pServerModelLeft;
	CServerModel* pServerModelRight;
	int nLength = (*pServerModelArray).size();
	bool arrErrorModel[nLength];

	// Init for checking duplicated servers location
	for (int i = 0; i < nLength; i++)
	{
		arrErrorModel[i] = false;
	}
	
	for (int i = 0; i < nLength - 1; i++)
	{
		for (int j = i + 1; j < nLength; j++)
		{
			pServerModelLeft = (*pServerModelArray)[i];
			pServerModelRight = (*pServerModelArray)[j];

			if (pServerModelLeft->IsEqualLocation(pServerModelRight))
			{
				arrErrorModel[i] = true;
				arrErrorModel[j] = true;				
			}
		}
	}

	// Proceed duplicated servers location
	for (int i = 0; i < nLength; i++)
	{
		if (arrErrorModel[i])
		{			
			InsertDuplicatedLocationServer((*pServerModelArray)[i]);			
		}
	}
}

void CInternalServerDataCheckProcessor::InsertDuplicatedLocationServer(CServerModel* pServerModel)
{
	BSONObj boServerErrorInfo;

	pServerModel->ToBSONObj(boServerErrorInfo);

	//cout << boServerErrorInfo.toString() << endl;
	m_pCIController->Insert(TBL_SERVER_DATA_ERROR, boServerErrorInfo);
}

void CInternalServerDataCheckProcessor::CheckData()
{		
	ServerModelArray* pServerModelArray = NULL;
	
	RackName2ServerModelArrayMap::iterator it = m_mapRackName2ServerModelArray.begin();
	while (it != m_mapRackName2ServerModelArray.end())
	{
		pServerModelArray = (*it).second;
		CheckLocation(pServerModelArray);			

		it++;
	}
}

void CInternalServerDataCheckProcessor::LoadServer(BSONObj& boServerRecord)
{
	string strRack = "";
	RackName2ServerModelArrayMap::iterator it;
	CServerModel* pServerModel = NULL;
	ServerModelArray* pServerModelArray = NULL;

	strRack = boServerRecord.getStringField(FIELD_RACK);
	pServerModel = new CServerModel();
	(*pServerModel)[FIELD_RACK] = strRack;	
	(*pServerModel)[FIELD_CODE] = boServerRecord.getStringField(FIELD_CODE);
	(*pServerModel)[FIELD_SITE] = boServerRecord.getStringField(FIELD_SITE);
	(*pServerModel)[FIELD_IP_CHASSIS] = boServerRecord.getStringField(FIELD_IP_CHASSIS);
	(*pServerModel)[FIELD_BAY] = boServerRecord.getIntField(FIELD_BAY);
	(*pServerModel)[FIELD_STATUS] = boServerRecord.getIntField(FIELD_STATUS);
	(*pServerModel)[FIELD_U] = boServerRecord.getIntField(FIELD_U);

	it = m_mapRackName2ServerModelArray.find(strRack);

	if (it != m_mapRackName2ServerModelArray.end())
	{
		pServerModelArray = (*it).second;
	}
	else
	{				
		pServerModelArray = new ServerModelArray();
		m_mapRackName2ServerModelArray[strRack] = pServerModelArray;
	}

	pServerModelArray->push_back(pServerModel);
}

void CInternalServerDataCheckProcessor::DestroyData()
{
	ServerModelArray::iterator itServerModel;
	ServerModelArray* pServerModelArray = NULL;
	RackName2ServerModelArrayMap::iterator it = m_mapRackName2ServerModelArray.begin();
	while (it != m_mapRackName2ServerModelArray.end())
	{
		pServerModelArray = (*it).second;
		itServerModel = pServerModelArray->begin();
		while (itServerModel != pServerModelArray->end())
		{
			delete (*itServerModel);
			itServerModel++;
		}
		delete pServerModelArray;

		it++;
	}

	m_mapRackName2ServerModelArray.clear();
}