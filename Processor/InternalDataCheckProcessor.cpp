#include "InternalDataCheckProcessor.h"
#include "../Controller/CMDBController.h"

CInternalDataCheckProcessor::CInternalDataCheckProcessor(const string& strFileName)
:CProcessor(strFileName)
{
}

CInternalDataCheckProcessor::~CInternalDataCheckProcessor(void)
{
	if (NULL != m_pCIController)
	{
		delete m_pCIController;
	}
}

bool CInternalDataCheckProcessor::Connect()
{
	RegisterController(m_pCIController);

	return CProcessor::Connect();
}

void CInternalDataCheckProcessor::ProceedCheckDataInfo()
{	
	if (!Connect())
	{
		return;
	}

	if (!LoadData())
	{
		return;
	}

	CheckData();
}