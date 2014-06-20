#include "DepartmentInfoChangeProcessor.h"
#include "../Controller/DepartmentController.h"
#include "../Controller/DepartmentInfoChangeController.h"
#include "../Model/DepartmentInfoChangeModel.h"

CDepartmentInfoChangeProcessor::CDepartmentInfoChangeProcessor(const string& strCfgFile)
:CCIInfoChangeProcessor(strCfgFile)
{
	m_pCIController = new CDepartmentController();
	m_pCIInfoChangeController = new CDepartmentInfoChangeController();
	m_pCIInfoChangeModel = new CDepartmentInfoChangeModel();	
}

CDepartmentInfoChangeProcessor::~CDepartmentInfoChangeProcessor(void)
{	
}
