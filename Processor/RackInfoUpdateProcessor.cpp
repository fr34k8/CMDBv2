#include "RackInfoUpdateProcessor.h"
#include "../Controller/RackController.h"
#include "../Controller/RackInfoChangeController.h"
#include "../Controller/RackInfoUpdateController.h"
#include "../Controller/RackHistoryLogController.h"
#include "../Model/RackInfoChangeModel.h"
#include "../Model/RackHistoryLogModel.h"

CRackInfoUpdateProcessor::CRackInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController = new CRackInfoUpdateController();
	m_pCIInfoChangeController = new CRackInfoChangeController();
	m_pCMDBController = new CRackController();
	m_pCIHistoryLogController = new CRackHistoryLogController();
	m_pCIHistoryLogModel = new CRackHistoryLogModel();
	m_pCIInfoChangeModel = new CRackInfoChangeModel();
}

CRackInfoUpdateProcessor::~CRackInfoUpdateProcessor(void)
{
}