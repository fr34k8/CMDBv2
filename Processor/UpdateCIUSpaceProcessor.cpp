#include "UpdateCIUSpaceProcessor.h"
#include "../Controller/CMDBController.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"

CUpdateCIUSpaceProcessor::CUpdateCIUSpaceProcessor(const string& strFileName)
:CProcessor(strFileName)
{
}

CUpdateCIUSpaceProcessor::~CUpdateCIUSpaceProcessor(void)
{
	if (NULL != m_pCIController)
	{
		delete m_pCIController;
	}
}

auto_ptr<DBClientCursor> CUpdateCIUSpaceProcessor::LoadDB()
{
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	ptrResultCursor = m_pCIController->Find(QUERY("deleted" << 0));
	return ptrResultCursor;
}

auto_ptr<DBClientCursor> CUpdateCIUSpaceProcessor::LoadMapDB()
{
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	string strTableName;
	strTableName = TBL_CI_SPACE;
	ptrResultCursor = m_pCIController->Find(strTableName);
	return ptrResultCursor;
}

bool CUpdateCIUSpaceProcessor::Proceed()
{
	if (Connect())
	{
		ProceedData();
	}
}

bool CUpdateCIUSpaceProcessor::PrepareCISpace()
{
	auto_ptr<DBClientCursor> ptrMapCursor;
	BSONObj boMapRecord;
	ptrMapCursor = LoadMapDB();
	try
	{
		if (ptrMapCursor.get() == NULL)
		{
			return false;
		}
		m_mapModel2Space.clear();
		while (ptrMapCursor->more())
		{
			boMapRecord = ptrMapCursor->nextSafe();
			if (boMapRecord.hasField("model") && boMapRecord.hasField("u_space"))
			{
				m_mapModel2Space[boMapRecord.getStringField("model")] = boMapRecord.getIntField("u_space");
			}
		}
		ptrMapCursor.reset();
	}
	catch (exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CUpdateCIUSpaceProcessor", "PrepareCISpace()", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return true;
}

bool CUpdateCIUSpaceProcessor::ProceedData()
{
	string strTableName;
	auto_ptr<DBClientCursor> ptrCursor;
	BSONObj boRecord, boMappingData;
	int iUSpace;
	ptrCursor = LoadDB();

	try
	{
		if (!PrepareCISpace())
		{
			return false;
		}
		if (ptrCursor.get() == NULL)
		{
			return false;
		}
		while (ptrCursor->more())
		{
			boRecord = ptrCursor->nextSafe();
			iUSpace = CalculateUSpace(boRecord);
			m_pCIController->Update(BSON("$set" << BSON("u_space" << iUSpace)), QUERY("_id" << boRecord["_id"]));
			//Change u_space to floor_layer to compute floor_layer for chassis.
			/*-- Compute Switch_type --*/
			/*strTableName = m_pCIController->GetTableName();
			if (strTableName.compare(TBL_ACCESS_SWITCH) == 0
				|| strTableName.compare(TBL_AGGREGATION_SWITCH) == 0
				|| strTableName.compare(TBL_CORE_SWITCH) == 0)
			{

				if (iUSpace == 0)
				{
					m_pCIController->Update(BSON("$set" << BSON("switch_type" << SWITCH_MODULE)), QUERY("_id" << boRecord["_id"]));
				}
				else
				{
					m_pCIController->Update(BSON("$set" << BSON("switch_type" << SWITCH_U)), QUERY("_id" << boRecord["_id"]));
				}
			}*/
			/*-------------------------*/
		}
		ptrCursor.reset();
	}
	catch (exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CUpdateCIUSpaceProcessor", "ProceedData()", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return true;
}

int CUpdateCIUSpaceProcessor::CalculateUSpace(BSONObj boRecord)
{
	int iUSpace = 0;
	if (boRecord.hasField("model"))
	{
		iUSpace = m_mapModel2Space[boRecord.getStringField("model")];
	}
	return iUSpace;
}