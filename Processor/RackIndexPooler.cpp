#include "RackIndexPooler.h"
#include "../Controller/RackInfoIndexController.h"

CRackIndexPooler::CRackIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CRackInfoIndexController();
}

CRackIndexPooler::~CRackIndexPooler(void)
{
}
