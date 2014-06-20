#include "DivisionIndexPooler.h"
#include "../Controller/DivisionInfoIndexController.h"

CDivisionIndexPooler::CDivisionIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CDivisionInfoIndexController();
}

CDivisionIndexPooler::~CDivisionIndexPooler(void)
{
}
