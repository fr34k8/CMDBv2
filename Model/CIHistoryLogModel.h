#pragma once
#include "MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CCIHistoryLogModel: public CMongodbModel
{
public:
	CCIHistoryLogModel(void);
	virtual ~CCIHistoryLogModel(void);

	inline string GetUsername() { return m_strUsername; }
	inline void SetUsername(const string& strUsername) { m_strUsername = strUsername; }

	inline BSONElement GetObjectId() { return m_beObjectId; }
	inline void SetObjectId(const BSONElement& beObjectId) { m_beObjectId = beObjectId; }

	inline string GetObjectCode() { return m_strObjectCode; }
	inline void SetObjectCode(const string& strObjectCode) { m_strObjectCode = strObjectCode; }

	inline int GetChangeType() { return m_iChangeType; }
	inline void SetChangeType(const int& iChangeType) { m_iChangeType = iChangeType; }

	inline long long GetChangeDate() { return m_lChangeDate; }
	inline void SetChangeDate(const long long& lChangeDate) { m_lChangeDate = lChangeDate; }

	void AppendOldValues(BSONObj boOldValue);
	void AppendNewValues(BSONObj boNewValue);
	void Unset();

	virtual BSONObj GetCIHistoryLog();

protected:
	string m_strUsername;
	BSONElement m_beObjectId;
	string m_strObjectCode;
	BSONObjBuilder* m_pBobOldValues;
	BSONObjBuilder* m_pBobNewValues;
	int m_iChangeType;
	long long m_lChangeDate;
};
