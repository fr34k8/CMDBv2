 #pragma once
#include "MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CHardwareCheckerModel: public CMongodbModel
{
public:
	CHardwareCheckerModel(void);
	~CHardwareCheckerModel(void);

	inline string GetSerialNumber() { return m_strSerialNumber; }
	inline void SetSerialNumber(const string& strSerialNumber) { m_strSerialNumber = strSerialNumber;}

	inline string GetSnSCpuInfo() { return m_strSnSCpuInfo; }
	inline void SetSnSCpuInfo(const string& strSnSCpuInfo) { m_strSnSCpuInfo = strSnSCpuInfo; }

	inline string GetSnSModelInfo() { return m_strSnSModelInfo; }
	inline void SetSnSModelInfo(const string& strSnSModelInfo) { m_strSnSModelInfo = strSnSModelInfo; }

	inline string GetCmdbCpuInfo() { return m_strCmdbCpuInfo; }
	inline void SetCmdbCpuInfo(const string& strCmdbCpuInfo) { m_strCmdbCpuInfo = strCmdbCpuInfo; }

	inline string GetCmdbModelInfo() { return m_strCmdbModelInfo; }
	inline void SetCmdbModelInfo(const string& strCmdbModelInfo) { m_strCmdbModelInfo = strCmdbModelInfo; }

	inline int GetIsMatch() { return m_nIsMatch; }
	inline void SetIsMatch(int nIsMatch) { m_nIsMatch = nIsMatch; }
	BSONObj GetHardwareCheckerInfo();

protected:
	string m_strSerialNumber;
	string m_strSnSCpuInfo;
	string m_strSnSModelInfo;
	string m_strCmdbCpuInfo;
	string m_strCmdbModelInfo;
	int m_nIsMatch;
};