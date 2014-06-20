#pragma once
#include "MongodbModel.h"

class CMailboxModel: public CMongodbModel
{
public:
	CMailboxModel(void);
	~CMailboxModel(void);

	inline string GetApplication() { return m_strApplication; }
	inline void SetApplication(const string& strApplication) { m_strApplication = strApplication; }

	inline long long GetClock() { return m_lClock; }
	inline void SetClock(const long long& lClock) { m_lClock = lClock; }

	inline string GetFunction() { return m_strFunction; }
	inline void SetFunction(const string& strFunction) { m_strFunction = strFunction; }

	inline string GetSourceFrom() { return m_strSourceFrom; }
	inline void SetSourceFrom(const string& strSourceFrom) { m_strSourceFrom = strSourceFrom; }

	inline string GetTechOwner() { return m_strTechOwner; }
	inline void SetTechOwner(const string& strTechOwner) { m_strTechOwner = strTechOwner; }

	inline BSONObj GetData() { return m_boData; }
	inline void SetData(BSONObj boData) { m_boData = boData.copy(); }

	BSONObj GetBSONModel();

	static void CreateServerLocationMailInfo(const BSONObj& boServerInfo, BSONObj& boMailInfo);
	static void CreateSwitchChassisLocationMailInfo(const BSONObj& boSwitchChassisInfo, BSONObj& boMailInfo);
	static void CreateServerNetworkMailInfo(const BSONObj& boServerInfo, BSONObj& boMailInfo);
	static void CreateTechnicalOwnerUserName(const BSONObj& boServerInfo, BSONObj& boTechnicalOwner);
	static void CreateNotifyMISServiceMailInfo(const BSONObj& boDataNotiInfo, BSONObj& boMailInfo);

protected:
	string m_strApplication;
	long long m_lClock;
	string m_strFunction;
	string m_strSourceFrom;
	string m_strTechOwner;
	BSONObj m_boData;

};