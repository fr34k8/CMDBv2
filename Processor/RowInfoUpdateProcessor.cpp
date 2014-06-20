#include "RowInfoUpdateProcessor.h"
#include "../Controller/RowController.h"
#include "../Controller/RowInfoChangeController.h"
#include "../Controller/RowInfoUpdateController.h"
#include "../Controller/RowHistoryLogController.h"
#include "../Model/RowInfoChangeModel.h"
#include "../Model/RowHistoryLogModel.h"

CRowInfoUpdateProcessor::CRowInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController = new CRowInfoUpdateController();
	m_pCIInfoChangeController = new CRowInfoChangeController();
	m_pCMDBController = new CRowController();
	m_pCIHistoryLogController = new CRowHistoryLogController();
	m_pCIHistoryLogModel = new CRowHistoryLogModel();
	m_pCIInfoChangeModel = new CRowInfoChangeModel();
}

CRowInfoUpdateProcessor::~CRowInfoUpdateProcessor(void)
{
}