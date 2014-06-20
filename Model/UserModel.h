 #pragma once
#include "MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CUserModel: public CMongodbModel
{
public:
	CUserModel(void);
	~CUserModel(void);

	inline string GetUserName() { return m_strUserName; }
	inline void SetUserName(const string& strUserName) { m_strUserName = strUserName;}

	inline string GetFullName() { return m_strFullName; }
	inline void SetFullName(const string& strFullName) { m_strFullName = strFullName; }

	inline string GetDepartmentHRCode() { return m_strDepartmentHRCode; }
	inline void SetDepartmentHRCode(const string& strDepartmentHRCode) { m_strDepartmentHRCode = strDepartmentHRCode; }

	BSONObj GetUserInfo();
protected:
	string m_strUserName;
	string m_strFullName;
	string m_strDepartmentHRCode;
};