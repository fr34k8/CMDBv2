#include "RowIndexPooler.h"
#include "../Controller/RowInfoIndexController.h"

CRowIndexPooler::CRowIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CRowInfoIndexController();
}

CRowIndexPooler::~CRowIndexPooler(void)
{
}
