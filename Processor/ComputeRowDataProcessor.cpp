#include "ComputeRowDataProcessor.h"
#include "../Controller/RowController.h"
#include "../Controller/RackController.h"
#include "../Model/RackModel.h"
#include "../Model/RowModel.h"

CComputeRowDataProcessor::CComputeRowDataProcessor(const string& strCfgFile)
:CComputeDataProcessor(strCfgFile)
{
	m_ptrCursor = auto_ptr<DBClientCursor>();
	m_pCIController = new CRowController();
	m_pRackController = new CRackController();
}

CComputeRowDataProcessor::~CComputeRowDataProcessor(void)
{
}

bool CComputeRowDataProcessor::LoadData()
{
	bool bResult = false;
	bResult = m_pCIController->Find(m_ptrCursor);
	return bResult;
}

void CComputeRowDataProcessor::ComputeData()
{
	bool bResult = false;
	BSONObj boRowRecord, boVLanInfo;
	Query queryRackInRow;
	CRackModel *pRackModel;
	CRowModel *pRowModel;
	auto_ptr<DBClientCursor> ptrRackCursor = auto_ptr<DBClientCursor>();
	while (m_ptrCursor->more())
	{
		boRowRecord = m_ptrCursor->nextSafe();
		if (pRowModel->GetRackQuery(queryRackInRow, boRowRecord))
		{
			if (m_pRackController->Find(ptrRackCursor, queryRackInRow))
			{
				boVLanInfo = pRackModel->GetVLanInfo(ptrRackCursor);
				m_pCIController->Update(boVLanInfo, QUERY("_id" << boRowRecord["_id"]));
			}
		}
		ptrRackCursor.reset();
	}
}

bool CComputeRowDataProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pRackController);
	return CComputeDataProcessor::Connect();
}
