#pragma once
#include "MongodbModel.h"

class CRoleOwnerModel:
	public CMongodbModel
{
public:
	CRoleOwnerModel(void);
	~CRoleOwnerModel(void);

	void Load(const BSONObj& boRecord);
	void RoleList2RoleInfo();
	void AddRoleName(const string& strRoleName);
	bool IsRoleExists(const string& strRoleName);
	vector<string> GetRoleName(){ return m_vtRoleName; }
	string GetUserName(){ return m_strUserName; }
protected:
	void BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat = 0);
private:
	string m_strUserName;
	vector<string> m_vtRoleName;
	BSONArray m_barrRoleInfo;
};