#include "PMMInfoUpdateProcessor.h"
#include "../Controller/PMMController.h"
#include "../Controller/PMMInfoChangeController.h"
#include "../Controller/PMMInfoUpdateController.h"
#include "../Controller/PMMHistoryLogController.h"
#include "../Model/PMMInfoChangeModel.h"
#include "../Model/CIHistoryLogModel.h"
#include "../Model/PMMHistoryLogModel.h"

CPMMInfoUpdateProcessor::CPMMInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController	= new CPMMInfoUpdateController();
	m_pCIInfoChangeController	= new CPMMInfoChangeController();
	m_pCMDBController			= new CPMMController();
	m_pCIHistoryLogController	= new CPMMHistoryLogController();
	m_pCIHistoryLogModel		= new CPMMHistoryLogModel();
	m_pCIInfoChangeModel		= new CPMMInfoChangeModel();
}

CPMMInfoUpdateProcessor::~CPMMInfoUpdateProcessor(void)
{	
}