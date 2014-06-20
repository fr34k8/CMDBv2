#include "DepartmentIndexPooler.h"
#include "../Controller/DepartmentInfoIndexController.h"

CDepartmentIndexPooler::CDepartmentIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CDepartmentInfoIndexController();
}

CDepartmentIndexPooler::~CDepartmentIndexPooler(void)
{
}
