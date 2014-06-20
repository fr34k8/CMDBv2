#pragma once
#include "ComputeDataProcessor.h"

class CAdminProductRolesController;
class CAdminProductOwnerController;
class CAdminUserGroupsProductsController;
class CAdminUserGroupsUsersController;
class CUserController;
class CRoleOwnerModel;
class CTechnicalOwnerModel;

typedef map<string, string> RoleID2RoleName;
typedef map<string, CRoleOwnerModel*> UserName2RoleOwnerModel;
typedef map<string, UserName2RoleOwnerModel*> ProductKey2ProductOwnerRole;
typedef map<string, CTechnicalOwnerModel*> RoleName2TechnicalOwner;

class CComputeServerDataProcessor :
	public CComputeDataProcessor
{
public:
	CComputeServerDataProcessor(const string& strCfgFile);
	~CComputeServerDataProcessor(void);
	bool Connect();
	//void ComputeSpecialDataInfo(const BSONObj& boServerInfo);
	void ComputeTechnicalOwnerInfo(const BSONObj& boServerInfo);
protected:
	bool LoadData();
	void ComputeData();

	bool LoadServerInfo();
	bool LoadRoles();
	bool LoadUsers();

	string GetRoleNameByRoleID(BSONElement beRoleID);
	bool LoadRoleProductOwnerByProductCode(const string& strProductCode);
	bool LoadRoleGroupProductByProductCode(const string& strProductCode);
	bool AddRoleOwnerModel(const BSONObj& boInfo, UserName2RoleOwnerModel *ptrMapUserName2RoleOwnerModel);
	bool IsProductLoaded(const string& strProductCode);
	bool IsUserExists(const string& strUserName);
	bool RemoveUserRoleInGroup(const BSONObj& boInfo, UserName2RoleOwnerModel *pMapUserName2RoleOwnerModel);

	void PrepareData(const BSONObj& boServerInfo);
	void BuildTechnicalOwnerFormatting(const vector<string>& vt_RoleName, const string& strUserName);
	void UpdateTechnicalOwnerServerByProduct(const string& strProductCode);
	void CalculateTechnicalOwner(const string& strProductCode, UserName2RoleOwnerModel *pMapUserName2RoleOwnerModel);
	void ClearTechnicalOwner();
	void ClearProductOwnerRole();
	void ClearProductRoles();
	void ClearUsers();
	
	void DestroyData();
	
private:
	ProductKey2ProductOwnerRole m_mapProductCode2ProductOwnerRole;
	RoleID2RoleName m_mapRoleID2RoleName;
	vector<string> m_vtUsers;
	RoleName2TechnicalOwner m_mapRoleName2TechnicalOwner;
	
	CUserController* m_pUserController;
	CAdminProductRolesController* m_pAdminProductRolesController;
	CAdminProductOwnerController* m_pAdminProductOwnerController;
	CAdminUserGroupsProductsController* m_pAdminUserGroupsProductsController;
	CAdminUserGroupsUsersController* m_pAdminUserGroupsUsersController;
};