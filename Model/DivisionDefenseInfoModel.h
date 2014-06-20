#pragma once
#include "MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CDivisionDefenseInfoModel: public CMongodbModel
{
public:
	CDivisionDefenseInfoModel(void);
	~CDivisionDefenseInfoModel(void);
	
	inline BSONElement GetCIId() { return m_beCIId; }
	inline void SetCIId(const BSONElement& beObjectId) { m_beCIId = beObjectId; }

	inline string GetHRId() { return m_strHRId; }
	inline void SetHRId(const string& strHRId) { m_strHRId = strHRId; }

	inline string GetHRCode() { return m_strHRCode; }
	inline void SetHRCode(const string& strHRCode) { m_strHRCode = strHRCode; }

	inline string GetAlias() { return m_strAlias; }
	inline void SetAlias(const string& strAlias) { m_strAlias = strAlias; }

	inline string GetCode() { return m_strCode; }
	inline void SetCode(const string& strCode) { m_strCode = strCode; }

	inline string GetChangeBy() { return m_strChangeBy; }
	inline void SetChangeBy(const string& strChangeBy) { m_strChangeBy = strChangeBy; }

	inline int GetStatus() { return m_iStatus; }
	inline void SetStatus(int iStatus) { m_iStatus = iStatus; }

	inline int GetDelete() { return m_iDeleted; }
	inline void SetDelete(int iDeleted) { m_iDeleted= iDeleted; } 

	inline int GetActionType() { return m_iActionType; }
	inline void SetActionType(int iActionType) { m_iActionType = iActionType; }

	inline int GetClock() { return m_iClock; }
	inline void SetClock(int iClock) { m_iClock = iClock; }

	BSONObj GetDivisionDefenseInfo();
protected:
	BSONElement m_beCIId;
	string m_strHRId;
	string m_strHRCode;
	string m_strAlias;
	string m_strCode;
	string m_strChangeBy;
	int m_iStatus;
	int m_iDeleted;
	int m_iActionType;
	int m_iClock;
};