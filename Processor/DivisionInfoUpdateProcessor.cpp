#include "DivisionInfoUpdateProcessor.h"
#include "../Controller/DivisionController.h"
#include "../Controller/DivisionInfoChangeController.h"
#include "../Controller/DivisionInfoUpdateController.h"
#include "../Controller/DivisionHistoryLogController.h"
#include "../Model/DivisionInfoChangeModel.h"
#include "../Model/CIHistoryLogModel.h"
#include "../Model/DivisionHistoryLogModel.h"

CDivisionInfoUpdateProcessor::CDivisionInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController	= new CDivisionInfoUpdateController();
	m_pCIInfoChangeController	= new CDivisionInfoChangeController();
	m_pCMDBController			= new CDivisionController();
	m_pCIHistoryLogController	= new CDivisionHistoryLogController();	
	m_pCIHistoryLogModel		= new CDivisionHistoryLogModel();
	m_pCIInfoChangeModel		= new CDivisionInfoChangeModel();
}

CDivisionInfoUpdateProcessor::~CDivisionInfoUpdateProcessor(void)
{	
}