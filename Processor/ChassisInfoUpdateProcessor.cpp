#include "ChassisInfoUpdateProcessor.h"
#include "../Controller/ChassisController.h"
#include "../Controller/ChassisInfoChangeController.h"
#include "../Controller/ChassisInfoUpdateController.h"
#include "../Controller/ChassisHistoryLogController.h"
#include "../Model/ChassisInfoChangeModel.h"
#include "../Model/ChassisHistoryLogModel.h"

CChassisInfoUpdateProcessor::CChassisInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController = new CChassisInfoUpdateController();
	m_pCIInfoChangeController = new CChassisInfoChangeController();
	m_pCMDBController = new CChassisController();
	m_pCIHistoryLogController = new CChassisHistoryLogController();
	m_pCIHistoryLogModel = new CChassisHistoryLogModel();
	m_pCIInfoChangeModel = new CChassisInfoChangeModel();
}

CChassisInfoUpdateProcessor::~CChassisInfoUpdateProcessor(void)
{
}

void CChassisInfoUpdateProcessor::InsertData(BSONObj boNewCIInfo)
{
}

void CChassisInfoUpdateProcessor::DeleteData(BSONObj boNewCIInfo)
{
}

void CChassisInfoUpdateProcessor::UpdateData(BSONObj boOldCIInfo, 
											 BSONObj boChangedData, 
											 BSONObj boChangedFields)
{
}