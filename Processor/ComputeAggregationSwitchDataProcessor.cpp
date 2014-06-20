#include "ComputeAggregationSwitchDataProcessor.h"
#include "../Controller/AggregationSwitchController.h"
#include "../Model/AggregationSwitchModel.h"

CComputeAggregationSwitchDataProcessor::CComputeAggregationSwitchDataProcessor(const string& strCfgFile)
:CComputeDataProcessor(strCfgFile)
{
	m_pCIController = new CAggregationSwitchController();
}

CComputeAggregationSwitchDataProcessor::~CComputeAggregationSwitchDataProcessor(void)
{
}


bool CComputeAggregationSwitchDataProcessor::Connect()
{
	return CComputeDataProcessor::Connect();
}

bool CComputeAggregationSwitchDataProcessor::LoadData()
{
	BSONObj boAggregationSwitchInfoRecord;
	CAggregationSwitchModel oAggregationSwitchModel;
	string strAccessRack;
	BSONObj boRackInfo;

	auto_ptr<DBClientCursor> ptrAggregationSwitchCursor = auto_ptr<DBClientCursor>();
	ptrAggregationSwitchCursor = m_pCIController->Find();		

	if (ptrAggregationSwitchCursor.get() == NULL)
	{
		return false;
	}	

	while(ptrAggregationSwitchCursor->more())
	{		
		boAggregationSwitchInfoRecord = ptrAggregationSwitchCursor->nextSafe();		
		strAccessRack = boAggregationSwitchInfoRecord.getStringField(FIELD_ACC_RACK);

		// Convert allow vlan format
		oAggregationSwitchModel.AccessRack2RackInfo(strAccessRack);		
		oAggregationSwitchModel.ToBSONObj(boRackInfo);
		
		m_pCIController->Update(BSON("$set" << boRackInfo), QUERY("_id" << boAggregationSwitchInfoRecord["_id"]));				
	}

	ptrAggregationSwitchCursor.reset();

	return true;
}

void CComputeAggregationSwitchDataProcessor::ComputeData()
{
}