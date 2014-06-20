#include "InterfaceCheckerProcessor.h"
#include "../Config/ConfigFile.h"
#include "../Controller/CollectorController.h"
#include "../Controller/InterfaceCheckerController.h"
#include "../Model/CollectorModel.h"
#include "../External/SDKService.h"

CInterfaceCheckerProcessor::CInterfaceCheckerProcessor(const string& strCfgFile)
:CCheckerProcessor(strCfgFile)
{	
	m_pSDKService = new CSDKService();
	m_pInterfaceCheckerController = new CInterfaceCheckerController();
}

CInterfaceCheckerProcessor::~CInterfaceCheckerProcessor(void)
{	
	if (NULL != m_pSDKService)
		delete m_pSDKService;
	if (NULL != m_pInterfaceCheckerController)
		delete m_pInterfaceCheckerController;
}	

bool CInterfaceCheckerProcessor::Connect()
{		
	// Register controllers before connecting to database
	RegisterController(m_pCollectorInfoController);
	RegisterController(m_pInterfaceCheckerController);
	return CProcessor::Connect();
}

void CInterfaceCheckerProcessor::CheckInterfaceInfo(CCollectorModel* pCollectorInfo)
{
	char *pData;
	pData = NULL;
	string strClientId;
	char* pClientId;
	string strPasswd;
	
	strClientId = CConfigFile::GetInstance()->GetSDKClientId();
	//strClientId = CUtilities::ReplaceString(strClientId, "\"", "");
	pClientId = (char*)strClientId.c_str();
	
	strPasswd = CConfigFile::GetInstance()->GetSDKPasswd();
	//strPasswd = CUtilities::ReplaceString(strPasswd, "\"", "");
	

	m_pSDKService->SetClientId(pClientId);
	m_pSDKService->SetPassword(strPasswd);
	m_pSDKService->SetOperation((char*)"GetODAHostInfoList");
	m_pSDKService->SetRequestData((char*)"{}");
	
	pData = m_pSDKService->CallService();
	if (NULL != pData)
	{
		cout << "Data Okie" << endl;
		m_pInterfaceCheckerController->CompareInterfaceWithODA(pCollectorInfo, pData);
		delete pData;
	}
}