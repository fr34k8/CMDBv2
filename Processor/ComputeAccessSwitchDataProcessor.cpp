#include "ComputeAccessSwitchDataProcessor.h"
#include "../Controller/AccessSwitchController.h"
#include "../Model/AccessSwitchModel.h"

CComputeAccessSwitchDataProcessor::CComputeAccessSwitchDataProcessor(const string& strCfgFile)
:CComputeDataProcessor(strCfgFile)
{
	m_pCIController = new CAccessSwitchController();	
}

CComputeAccessSwitchDataProcessor::~CComputeAccessSwitchDataProcessor(void)
{	
}

bool CComputeAccessSwitchDataProcessor::Connect()
{	
	return CComputeDataProcessor::Connect();
}

bool CComputeAccessSwitchDataProcessor::LoadData()
{
	BSONObj boAccessSwitchInfoRecord;
	CAccessSwitchModel oAccessSwitchModel;
	string strAllowVlan;
	BSONObj boVlanInfo;

	auto_ptr<DBClientCursor> ptrAccessSwitchCursor = auto_ptr<DBClientCursor>();
	ptrAccessSwitchCursor = m_pCIController->Find();		

	if (ptrAccessSwitchCursor.get() == NULL)
	{		
		return false;
	}	

	while(ptrAccessSwitchCursor->more())
	{		
		boAccessSwitchInfoRecord = ptrAccessSwitchCursor->nextSafe();		
		strAllowVlan = boAccessSwitchInfoRecord.getStringField("allow_vlan");

		// Convert allow vlan format
		oAccessSwitchModel.AllowVlan2VlanInfo(strAllowVlan);		
		oAccessSwitchModel.ToBSONObj(boVlanInfo);
		
		m_pCIController->Update(BSON("$set" << boVlanInfo), QUERY("_id" << boAccessSwitchInfoRecord["_id"]));				
	}

	ptrAccessSwitchCursor.reset();

	return true;
}