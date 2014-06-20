#include "ComputeDataProcessor.h"
#include "../Controller/CMDBController.h"

CComputeDataProcessor::CComputeDataProcessor(const string& strCfgFile)
:CProcessor(strCfgFile)
{
	m_pCIController = NULL;
}

CComputeDataProcessor::~CComputeDataProcessor(void)
{
	if (NULL != m_pCIController)
	{
		delete m_pCIController;
	}
	cout << "Destruction CComputeDataProcessor(void)" << endl;
}

bool CComputeDataProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterController(m_pCIController);

	return CProcessor::Connect();
}

void CComputeDataProcessor::ProceedComputeData()
{
	// Connect to database
	if (!Connect())
	{
		return;
	}

	if (!LoadData())
	{
		return;
	}

	ComputeData();
}

