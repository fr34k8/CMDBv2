#include "ProductIndexPooler.h"
#include "../Controller/ProductInfoIndexController.h"

CProductIndexPooler::CProductIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CProductInfoIndexController();
}

CProductIndexPooler::~CProductIndexPooler(void)
{
}