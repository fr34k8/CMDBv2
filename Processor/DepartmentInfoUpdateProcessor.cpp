#include "DepartmentInfoUpdateProcessor.h"
#include "../Controller/DepartmentController.h"
#include "../Controller/DepartmentInfoChangeController.h"
#include "../Controller/DepartmentInfoUpdateController.h"
#include "../Controller/DepartmentHistoryLogController.h"
#include "../Model/DepartmentInfoChangeModel.h"
#include "../Model/CIHistoryLogModel.h"
#include "../Model/DepartmentHistoryLogModel.h"

CDepartmentInfoUpdateProcessor::CDepartmentInfoUpdateProcessor(const string& strCfgFile)
:CCIInfoUpdateProcessor(strCfgFile)
{
	m_pCIInfoUpdateController	= new CDepartmentInfoUpdateController();
	m_pCIInfoChangeController	= new CDepartmentInfoChangeController();
	m_pCMDBController			= new CDepartmentController();
	m_pCIHistoryLogController	= new CDepartmentHistoryLogController();
	m_pCIHistoryLogModel		= new CDepartmentHistoryLogModel();
	m_pCIInfoChangeModel		= new CDepartmentInfoChangeModel();
}

CDepartmentInfoUpdateProcessor::~CDepartmentInfoUpdateProcessor(void)
{	
}