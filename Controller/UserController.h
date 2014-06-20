#pragma once
#include "CMDBController.h"

class CCollectorModel;
class CUserModel;

typedef map<string, CUserModel*> HRAccountDomain2UserInfoMap;

class CUserController :
	public CCMDBController
{
public:
	CUserController(void);
	~CUserController(void);

	void CompareFullData(CCollectorModel* pCollectorInfo, char *pData);
	bool IsMatchUser(const string& strAccountDomain);
	void PushDirtyUserOrgChart(const string& strDirtyTable, 
							   const string& strAccountDomain, 
							   const string& strOrgDepartment, 
							   int iFlag);
	bool FindOperatingUser(auto_ptr<DBClientCursor>& ptrCursor);
protected:
	CUserModel* GetUserInfoByAccountDomain(const string& strAccountDomain);
	void ClearMapUserInfo();
protected:
	HRAccountDomain2UserInfoMap m_mapAccountDomain2UserInfoMap;
};