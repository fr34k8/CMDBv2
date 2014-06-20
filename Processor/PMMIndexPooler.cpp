#include "PMMIndexPooler.h"
#include "../Controller/PMMInfoIndexController.h"

CPMMIndexPooler::CPMMIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CPMMInfoIndexController();
}

CPMMIndexPooler::~CPMMIndexPooler(void)
{
}
