#pragma once
#include "DeviceModel.h"

#define FIELD_CODE			"code"
#define FIELD_SITE			"site"
#define FIELD_RACK			"rack"
#define FIELD_IP_CHASSIS	"chassis"
#define FIELD_BAY			"bay"
#define FIELD_STATUS		"status"

class CServerModel :
	public CDeviceModel
{
public:
	CServerModel(void);
	virtual ~CServerModel(void);

	BSONObj GetModelMappingRecord(BSONObj boRecord);
	BSONObj GetModelMappingCondition(BSONObj boRecord);

	operator int();
	operator string();
	CMongodbModel& operator=(int iValue);
	CMongodbModel& operator=(string strValue);

	bool IsEqualLocation(CServerModel* pServerModel);

	void Print();

	static string GetCode(BSONObj boCIInfo);
	static string GetServerName(BSONObj boCIInfo);
	static string GetProductAlias(BSONObj boCIInfo);
	static string GetProductCode(BSONObj boCIInfo);
	static int GetBay(BSONObj boCIInfo);

	static void CreateLocationMailInfo(const BSONObj& boServerInfo, BSONObj& boMailInfo);
	static void CreateNetworkMailInfo(const BSONObj& boServerInfo, BSONObj& boMailInfo);
protected:
	string m_strCode;
	string m_strSite;
	string m_strRack;
	string m_strIPChassis;
	int m_iBay;
	int m_iStatus;
};