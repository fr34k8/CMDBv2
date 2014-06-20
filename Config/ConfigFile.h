#pragma once
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "ConfigReader.h"
#include "../Common/DBCommon.h"

class CConfigFile:public CConfigReader
{
	static CConfigFile* s_pInstance;
protected:
	string m_strDBGroup;

public:

	CConfigFile(const string& strCfgFile);
	~CConfigFile(void);
	static CConfigFile* GetInstance(const string& strCfgFile = "");
	static void DestroyInstance();

	string GetErrorLogFileName();
	string GetDBLogFileName();
	string GetInfoLogFileName();

	void SetActiveDBGroup(const string& strDBGroup);
	string GetHost();
	string GetUser();
	string GetPassword();
	string GetSource();
	string GetPort();
	string GetReadReference();
	string GetDBType();

	string GetTmpTableName(const char* strCIType);
	string GetSDKClientId();
	string GetSDKPasswd();
	bool IsReplicateSetUsed();
	int GetDivisionIndexPooler();
	int GetDepartmentIndexPooler();
	int GetServerIndexPooler();
	int GetProductIndexPooler();
	int GetChassisIndexPooler();
	int GetCoreSwitchIndexPooler();
	int GetAggregationSwitchIndexPooler();
	int GetAccessSwitchIndexPooler();
	int GetPeerLinkIndexPooler();
	int GetRackIndexPooler();
	int GetRowIndexPooler();
	int GetPDUIndexPooler();
	int GetPMMIndexPooler();
	int GetDebugLevel();
	int GetDBDebugLevel();
	string GetHostFixID();
};

