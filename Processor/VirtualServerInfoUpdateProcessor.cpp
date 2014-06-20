#include "VirtualServerInfoUpdateProcessor.h"
#include "../Controller/ServerController.h"
#include "../Controller/ServerInfoChangeController.h"
#include "../Controller/VirtualServerInfoUpdateController.h"
#include "../Controller/ServerHistoryLogController.h"
#include "../Model/ServerInfoChangeModel.h"
#include "../Model/ServerHistoryLogModel.h"
#include "ComputeServerDataProcessor.h"

CVirtualServerInfoUpdateProcessor::CVirtualServerInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController	= new CVirtualServerInfoUpdateController();
	m_pCIInfoChangeController	= new CServerInfoChangeController();
	m_pCMDBController			= new CServerController();
	m_pCIHistoryLogController	= new CServerHistoryLogController();	
	m_pCIHistoryLogModel		= new CServerHistoryLogModel();
	m_pCIInfoChangeModel		= new CServerInfoChangeModel();

	//DuyMN Add
	m_pComputeServerDataProcessor = new CComputeServerDataProcessor(strCfgFile);
}

CVirtualServerInfoUpdateProcessor::~CVirtualServerInfoUpdateProcessor(void)
{
	if (NULL != m_pComputeServerDataProcessor)
	{
		delete m_pComputeServerDataProcessor;
	}
}

bool CVirtualServerInfoUpdateProcessor::Connect()
{
	m_pComputeServerDataProcessor->Connect(); //Connect to Admin Database
	return CCIInfoUpdateProcessor::Connect();
}

void CVirtualServerInfoUpdateProcessor::UpdateSpecialDataInfo(BSONObj boOldCIInfo, BSONObj boNewCIInfo, BSONObj boChangedFields)
{
	if (boChangedFields.hasField("product_code"))
	{
		m_pComputeServerDataProcessor->ComputeTechnicalOwnerInfo(boNewCIInfo);
	}
}

void CVirtualServerInfoUpdateProcessor::InsertSpecialDataInfo(mongo::BSONObj boNewCIInfo)
{
	string strProductCode = "";
	strProductCode = CMongodbModel::GetStringFieldValue(boNewCIInfo, "product_code", "");
	
	if (strProductCode != "" && strProductCode != "NA")
		m_pComputeServerDataProcessor->ComputeTechnicalOwnerInfo(boNewCIInfo);
}