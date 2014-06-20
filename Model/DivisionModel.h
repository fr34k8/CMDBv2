 #pragma once
#include "MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CDivisionModel: public CMongodbModel
{
public:
	CDivisionModel(void);
	~CDivisionModel(void);

	inline string GetCode() { return m_strCode; }
	inline void SetCode(const string& strCode) { m_strCode = strCode;}

	inline string GetAlias() { return m_strAlias; }
	inline void SetAlias(const string& strAlias) { m_strAlias = strAlias; }

	inline string GetMISAlias() { return m_strMisAlias; }
	inline void SetMISAlias(const string& strMisAlias) { m_strMisAlias = strMisAlias; }

	inline string GetHRId() { return m_strHRId; }
	inline void SetHRId(const string& strHRId) { m_strHRId = strHRId; }

	inline string GetHRCode() { return m_strHRCode; }
	inline void SetHRCode(const string& strHRCode) { m_strHRCode = strHRCode; }

	inline string GetName() { return m_strName; }
	inline void SetName(const string& strName) { m_strName = strName; }

	inline string GetHRParentCode() { return m_strHRParentCode; }
	inline void SetHRParentCode(const string& strHRParentCode) { m_strHRParentCode = strHRParentCode; }

	inline int GetStatus() { return m_iStatus; }
	inline void SetStatus(int iStatus) { m_iStatus = iStatus; }

	inline int GetDelete() { return m_iDeleted; }
	inline void SetDelete(int iDeleted) { m_iDeleted= iDeleted; } 
	
	inline string GetHRCreatedAt() { return m_strHRCreatedAt; }
	inline void SetHRCreatedAt(const string& strHRCreatedAt) { m_strHRCreatedAt = strHRCreatedAt; }

	inline string GetHRLastUpdated() { return m_strHRLastUpdated; }
	inline void SetHRLastUpdated(const string& strHRLastUpdated) { m_strHRLastUpdated = strHRLastUpdated; }

	inline int GetIsVirtual() { return m_nIsVirtual; }
	inline void SetIsVirtual(int nIsVirtual) { m_nIsVirtual = nIsVirtual; }

	BSONObj GetDivisionInfo();
protected:
	string m_strName;
	string m_strCode;
	string m_strAlias;
	string m_strMisAlias;
	string m_strHRId;
	string m_strHRCode;
	string m_strHRParentCode;
	string m_strHRCreatedAt;
	string m_strHRLastUpdated;

	int m_iStatus;
	int m_iDeleted;	
	int m_nIsVirtual;
};