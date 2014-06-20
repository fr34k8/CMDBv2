#include "PDUIndexPooler.h"
#include "../Controller/PDUInfoIndexController.h"

CPDUIndexPooler::CPDUIndexPooler(const string& strCfgFile)
:CCIIndexPooler(strCfgFile)
{
	m_pCIInfoIndexController = new CPDUInfoIndexController();
}

CPDUIndexPooler::~CPDUIndexPooler(void)
{
}
