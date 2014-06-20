#include "ConfigFile.h"

#define INVERTED_INDEX_GROUP "INVERTED_INDEX"
#define DIVISION_INDEX_POOLER "DivisionIndexPooler"
#define DEPARTMENT_INDEX_POOLER "DepartmentIndexPooler"
#define SERVER_INDEX_POOLER "ServerIndexPooler"
#define PRODUCT_INDEX_POOLER "ProductIndexPooler"

#define CHASSIS_INDEX_POOLER "ChassisIndexPooler"
#define CORE_SWITCH_INDEX_POOLER "CoreSwitchIndexPooler"
#define AGGREGATION_SWITCH_INDEX_POOLER "AggregationSwitchIndexPooler"
#define ACCESS_SWITCH_INDEX_POOLER "AccessSwitchIndexPooler"
#define PEER_LINK_INDEX_POOLER "PeerLinkIndexPooler"
#define RACK_INDEX_POOLER "RackIndexPooler"
#define ROW_INDEX_POOLER "RowIndexPooler"
#define PDU_INDEX_POOLER "PDUIndexPooler"
#define PMM_INDEX_POOLER "PMMIndexPooler"

#define CI_MAP_TMP_GROUP "CI_MAP_TMP"

#define DEBUG_GROUP "DEBUG"
#define DEBUG_LEVEL "Level"
#define DB_DEBUG_LEVEL "DBLevel"

#define LOG_GROUP "LOG"
#define ERROR_LOG "ErrorLog"
#define DB_LOG "DBLog"
#define INFO_LOG "InfoLog"

CConfigFile *CConfigFile::s_pInstance = NULL;

CConfigFile::CConfigFile(const string& strFileName)
:CConfigReader(strFileName)
{
	m_strDBGroup = DB_GROUP_MONGODB_DEFAULT;
}

CConfigFile::~CConfigFile(void)
{	
}


CConfigFile* CConfigFile::GetInstance(const string& strCfgFile)
{
	if (!s_pInstance && !strCfgFile.empty())
	{
		s_pInstance = new CConfigFile(strCfgFile);
	}
	return s_pInstance;
}

void CConfigFile::DestroyInstance()
{
	if (NULL != s_pInstance)
	{
		delete s_pInstance;
	}
}

string CConfigFile::GetErrorLogFileName()
{   
   return ReadStringValue(LOG_GROUP, ERROR_LOG);   
}

string CConfigFile::GetDBLogFileName()
{
	return ReadStringValue(LOG_GROUP, DB_LOG); 
}

string CConfigFile::GetInfoLogFileName()
{
	return ReadStringValue(LOG_GROUP, INFO_LOG);
}

void CConfigFile::SetActiveDBGroup(const string& strDBGroup)
{
	m_strDBGroup = strDBGroup;
}

string CConfigFile::GetHost()
{
	return ReadStringValue(m_strDBGroup, HOST);
}

string CConfigFile::GetUser()
{
	return ReadStringValue(m_strDBGroup, USER);
}

string CConfigFile::GetPassword()
{
	return ReadStringValue(m_strDBGroup, PASS);
}

string CConfigFile::GetSource()
{
	return ReadStringValue(m_strDBGroup, SRC);
}

string CConfigFile::GetPort()
{
	return ReadStringValue(m_strDBGroup, PORT);
}

bool CConfigFile::IsReplicateSetUsed()
{
	return ReadBoolValue(m_strDBGroup, REPLICA_SET);
}

string CConfigFile::GetReadReference()
{
	return ReadStringValue(m_strDBGroup, READ_REFERENCE);
}

string CConfigFile::GetDBType()
{
	return ReadStringValue(m_strDBGroup, DB_TYPE);
}

int CConfigFile::GetDivisionIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, DIVISION_INDEX_POOLER);
}

int CConfigFile::GetDepartmentIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, DEPARTMENT_INDEX_POOLER);
}

int CConfigFile::GetServerIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, SERVER_INDEX_POOLER);
}

int CConfigFile::GetProductIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, PRODUCT_INDEX_POOLER);
}

int CConfigFile::GetChassisIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, CHASSIS_INDEX_POOLER);
}

int CConfigFile::GetCoreSwitchIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, CORE_SWITCH_INDEX_POOLER);
}

int CConfigFile::GetAggregationSwitchIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, AGGREGATION_SWITCH_INDEX_POOLER);
}

int CConfigFile::GetAccessSwitchIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, ACCESS_SWITCH_INDEX_POOLER);
}

int CConfigFile::GetPeerLinkIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, PEER_LINK_INDEX_POOLER);
}

int CConfigFile::GetRackIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, RACK_INDEX_POOLER);
}

int CConfigFile::GetRowIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, ROW_INDEX_POOLER);
}

int CConfigFile::GetPDUIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, PDU_INDEX_POOLER);
}

int CConfigFile::GetPMMIndexPooler()
{
	return ReadIntValue(INVERTED_INDEX_GROUP, PMM_INDEX_POOLER);
}

int CConfigFile::GetDebugLevel()
{
	return ReadIntValue(DEBUG_GROUP, DEBUG_LEVEL);
}

int CConfigFile::GetDBDebugLevel()
{
	return ReadIntValue(DEBUG_GROUP, DB_DEBUG_LEVEL);
}

string CConfigFile::GetTmpTableName(const char* strCIType)
{
	return ReadStringValue(CI_MAP_TMP_GROUP, strCIType);
}

string CConfigFile::GetSDKClientId()
{
	return ReadStringValue(SDK_AUTH, CLIENT_ID);
}
string CConfigFile::GetSDKPasswd()
{
	return ReadStringValue(SDK_AUTH, CLIENT_PASSWD);
}
string CConfigFile::GetHostFixID()
{
	return ReadStringValue(HOTFIX, CI_ID);
}