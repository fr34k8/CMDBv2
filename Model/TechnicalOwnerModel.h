#pragma once
#include "MongodbModel.h"

class CTechnicalOwnerModel:
	public CMongodbModel
{
public:
	CTechnicalOwnerModel(void);
	~CTechnicalOwnerModel(void);
	
	void SetRoleName(const string& strRoleName) { m_strRoleName = strRoleName; }
	string GetRoleName() { return m_strRoleName; }
	void SetUserName(const vector<string>& vt_UserName) { m_vtUserName = vt_UserName; }
	vector<string> GetUserName() { return m_vtUserName; }
	void AddUser(const string& strUserName);
	bool IsUserExists(const string& strUserName);
	void ListUser2UserInfo();
protected:
	void BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat = 0);
private:
	string m_strRoleName;
	vector<string> m_vtUserName;
	BSONArray m_barrUserInfo;
};