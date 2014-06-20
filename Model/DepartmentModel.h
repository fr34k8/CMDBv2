#pragma once
#include "MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CDepartmentModel: public CMongodbModel
{
public:
	CDepartmentModel(void);
	~CDepartmentModel(void);

	inline string GetCode() { return m_strCode; }
	inline void SetCode(const string& strCode) { m_strCode = strCode;}

	inline string GetAlias() { return m_strAlias; }
	inline void SetAlias(const string& strAlias) { m_strAlias = strAlias; }

	inline string GetName() { return m_strName; }
	inline void SetName(const string& strName) { m_strName = strName; }

	inline BSONElement GetDivisionId() { return m_beDivisionId; }
	inline void SetDivisionId(BSONElement beDivisionId) { m_beDivisionId = beDivisionId; }

	inline string GetDivisionAlias() { return m_strDivisionAlias; }
	inline void SetDivisionAlias(const string& strDivisionAlias) { m_strDivisionAlias = strDivisionAlias; }

	inline string GetDivisionHRCode() { return m_strDivisionHRCode; }
	inline void SetDivisionHRCode(const string& strDivisionHRCode) { m_strDivisionHRCode = strDivisionHRCode; }


	inline string GetHRId() { return m_strHRId; }
	inline void SetHRId(const string& strHRId) { m_strHRId = strHRId; }

	inline string GetHRCode() { return m_strHRCode; }
	inline void SetHRCode(const string& strHRCode) { m_strHRCode = strHRCode; }

	inline int GetStatus() { return m_iStatus; }
	inline void SetStatus(int iStatus) { m_iStatus = iStatus; }

	inline int GetDelete() { return m_iDeleted; }
	inline void SetDelete(int iDeleted) { m_iDeleted= iDeleted; } 

	BSONObj GetDepartmentInfo();
protected:
	string m_strCode;
	string m_strAlias;
	string m_strName;
	BSONElement m_beDivisionId;
	string m_strDivisionAlias;
	string m_strDivisionHRCode;
	string m_strHRId;
	string m_strHRCode;
	
	int m_iStatus;
	int m_iDeleted;	
};