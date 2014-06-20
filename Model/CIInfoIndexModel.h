#pragma once
#include "MongodbModel.h"

class CCIInfoIndexModel:
	public CMongodbModel
{
public:
	CCIInfoIndexModel(void);
	virtual ~CCIInfoIndexModel(void);
	
	inline string GetCIID() { return m_strCIID; }
	inline void SetCIID(const string& strCIID) { m_strCIID = strCIID; }

	inline string GetObjectID() { return m_strObjectID; }
	inline void SetObjectID(const string& strObjectID) { m_strObjectID = strObjectID; }

	inline string GetOldValue() { return m_strOldValue; }
	inline void SetOldValue(const string& strOldValue) { m_strOldValue = strOldValue; }

	inline string GetNewValue() { return m_strNewValue; }
	inline void SetNewValue(const string& strNewValue) { m_strNewValue = strNewValue; }

	inline string GetFieldName() { return m_strFieldName; }
	inline void SetFieldName(const string& strFieldName) { m_strFieldName = strFieldName; }

	inline long long GetClock() { return m_lClock; }
	inline void SetClock(const long long& lClock) { m_lClock = lClock; }

	CCIInfoIndexModel* Clone();
	void Load(const BSONObj& boRecord);

	Query IsExistedIndexQuery(string strValue);
	Query GetAddIndexQuery();
	Query GetDeleteIndexQuery();
	BSONObj GetCIInfoChange();
	BSONObj GetAddIndexRecord();
	BSONObj GetDeleteIndexRecord();
protected:
	string m_strCIID;
	string m_strObjectID;
	string m_strOldValue;
	string m_strNewValue;
	string m_strFieldName;
	long long m_lClock;
};
