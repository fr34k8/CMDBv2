#include "CIInfoMappingProcessor.h"
#include "../Controller/CMDBController.h"
#include "../Model/DeviceModel.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"

CCIInfoMappingProcessor::CCIInfoMappingProcessor(const string& strFileName)
:CProcessor(strFileName)
{
}

CCIInfoMappingProcessor::~CCIInfoMappingProcessor(void)
{
	if (NULL != m_pCIController)
	{
		delete m_pCIController;
	}
	if (NULL != m_pCIModel)
	{
		delete m_pCIModel;
	}
}

auto_ptr<DBClientCursor> CCIInfoMappingProcessor::LoadDB()
{
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();
	ptrResultCursor = m_pCIController->Find(QUERY("deleted" << 0));
	return ptrResultCursor;
}

bool CCIInfoMappingProcessor::Proceed()
{
	if (Connect())
	{
		ProceedData();
	}
}

bool CCIInfoMappingProcessor::ProceedData()
{
	auto_ptr<DBClientCursor> ptrCursor;
	BSONObj boRecord, boMappingData;
	BSONObj boMappingRecord, boMappingCondition;
	ptrCursor = LoadDB();

	try
	{
		if (ptrCursor.get() == NULL)
		{
			return false;
		}
		while (ptrCursor->more())
		{
			boRecord = ptrCursor->nextSafe();
			boMappingData = CreateMapping(boRecord);
			boMappingRecord = boMappingData["record"].Obj();
			boMappingCondition = boMappingData["condition"].Obj();
			if (!m_pCIController->IsExisted(boMappingData.getStringField("table_name"), Query(boMappingCondition)))
			{
				m_pCIController->Insert(boMappingData.getStringField("table_name"), boMappingRecord);
			}
		}
		ptrCursor.reset();
	}
	catch (exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoMappingProcessor", "ProceedData()", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return true;
}

BSONObj CCIInfoMappingProcessor::CreateMapping(BSONObj boRecord)
{
	BSONObj boMapping, boMappingRecord, boMappingCondition;
	boMappingRecord = m_pCIModel->GetModelMappingRecord(boRecord);
	boMappingCondition = m_pCIModel->GetModelMappingCondition(boRecord);
	boMapping = BSON(
		"table_name" << TBL_CI_SPACE
			<< "record" << boMappingRecord
			<< "condition" << boMappingCondition
		);
	return boMapping;
}
