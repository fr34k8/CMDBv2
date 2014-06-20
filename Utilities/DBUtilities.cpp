#include "DBUtilities.h"
#include "../Common/DBCommon.h"
#include "../Config/ConfigFile.h"


/*
 * Constructor - Assign a file name
 */
CDBUtilities::CDBUtilities()
{

}

/*
 * Destructor -
 */
CDBUtilities::~CDBUtilities()
{

}

ConnectInfo CDBUtilities::GetConnectInfo()
{
	ConnectInfo CInfo;
	CInfo.strHost = CConfigFile::GetInstance()->GetHost();
	CInfo.strUser = CConfigFile::GetInstance()->GetUser();
	CInfo.strPass = CConfigFile::GetInstance()->GetPassword();
	CInfo.strSource = CConfigFile::GetInstance()->GetSource();
	CInfo.strDBType = CConfigFile::GetInstance()->GetDBType();

	CInfo.bIsReplicateSetUsed = CConfigFile::GetInstance()->IsReplicateSetUsed();
	CInfo.strReadReferenceOption = CConfigFile::GetInstance()->GetReadReference();
	
	if (CConfigFile::GetInstance()->GetPort().compare("") != 0)
	{
		CInfo.strHost = CInfo.strHost + ":" + CConfigFile::GetInstance()->GetPort();
	}

	return CInfo;
}
