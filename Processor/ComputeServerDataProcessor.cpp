#include "ComputeServerDataProcessor.h"
#include "../Common/Common.h"
#include "../Common/DBCommon.h"
#include "../Controller/ServerController.h"
#include "../Controller/UserController.h"
#include "../Controller/AdminProductRolesController.h"
#include "../Controller/AdminProductOwnerController.h"
#include "../Controller/AdminUserGroupsProductsController.h"
#include "../Controller/AdminUserGroupsUsersController.h"
#include "../Model/RoleOwnerModel.h"
#include "../Model/TechnicalOwnerModel.h"

CComputeServerDataProcessor::CComputeServerDataProcessor(const std::string &strCfgFile)
:CComputeDataProcessor(strCfgFile)
{
	m_pCIController						 = new CServerController();
	m_pUserController					 = new CUserController();
	m_pAdminProductRolesController		 = new CAdminProductRolesController();
	m_pAdminProductOwnerController		 = new CAdminProductOwnerController();
	m_pAdminUserGroupsProductsController = new CAdminUserGroupsProductsController();
	m_pAdminUserGroupsUsersController	 = new CAdminUserGroupsUsersController(); 

}

CComputeServerDataProcessor::~CComputeServerDataProcessor()
{
	if (NULL != m_pAdminProductRolesController)
		delete m_pAdminProductRolesController;

	if (NULL != m_pAdminProductOwnerController)
		delete m_pAdminProductOwnerController;

	if (NULL != m_pAdminUserGroupsProductsController)
		delete m_pAdminUserGroupsProductsController;

	if (NULL != m_pAdminUserGroupsUsersController)
		delete m_pAdminUserGroupsUsersController;

	if (NULL != m_pUserController)
		delete m_pUserController;

	DestroyData();
	//cout << "Finished Destruction CComputeServerDataProcessor()" << endl;
}

bool CComputeServerDataProcessor::Connect()
{
	//Register Admin CMDBv2
	RegisterController(m_pUserController);
	RegisterController(m_pAdminProductRolesController, MONGODB_CMDB_ADMIN_GROUP);	
	RegisterController(m_pAdminProductOwnerController, MONGODB_CMDB_ADMIN_GROUP);
	RegisterController(m_pAdminUserGroupsProductsController, MONGODB_CMDB_ADMIN_GROUP);
	RegisterController(m_pAdminUserGroupsUsersController, MONGODB_CMDB_ADMIN_GROUP);
	
	return CComputeDataProcessor::Connect();
}

void CComputeServerDataProcessor::DestroyData()
{
	//cout << "Starting Destroy Data..." << endl;
	ClearProductRoles();
	ClearProductOwnerRole();
	ClearUsers();
	cout << "Finished Destroy CComputeServerDataProcessor" << endl;
}

void CComputeServerDataProcessor::ClearProductOwnerRole()
{
	//cout << "Starting clear product owner role..." << endl;
	ProductKey2ProductOwnerRole::iterator it = m_mapProductCode2ProductOwnerRole.begin();
	while(it != m_mapProductCode2ProductOwnerRole.end())
	{
		UserName2RoleOwnerModel* pMapUserName2RoleOwnerModel = (*it).second;
		
		if (NULL != pMapUserName2RoleOwnerModel)
		{
			UserName2RoleOwnerModel::iterator itRoleOwnerModel = pMapUserName2RoleOwnerModel->begin();
			
			//iTotalUserName = 0;
			while(itRoleOwnerModel != pMapUserName2RoleOwnerModel->end())
			{
				if (NULL != (*itRoleOwnerModel).second)
				{
					delete (*itRoleOwnerModel).second;
				}
				itRoleOwnerModel++;
			}
			pMapUserName2RoleOwnerModel->clear();
			delete pMapUserName2RoleOwnerModel;

			/*if (NULL != pMapUserName2RoleOwnerModel)
			{
				pMapUserName2RoleOwnerModel->clear();
				delete pMapUserName2RoleOwnerModel;
			}*/
		}
		it++;
	}
	m_mapProductCode2ProductOwnerRole.clear();
	//cout << "Finish clear product owner role" << endl;
}

void CComputeServerDataProcessor::ClearProductRoles()
{
	m_mapRoleID2RoleName.clear();
}

bool CComputeServerDataProcessor::LoadData()
{
	//TO DO
	if(!LoadRoles())
		return false;
	
	if(!LoadUsers())
		return false;

	if(!LoadServerInfo())
		return false;

	return true;
}

bool CComputeServerDataProcessor::LoadServerInfo()
{
	//cout << "Starting Load Server Info ..." << endl;
	BSONObj boRecord;
	auto_ptr<DBClientCursor> ptrCursor = auto_ptr<DBClientCursor>();
	
	if (!m_pCIController->FindOperatingAllServer(ptrCursor))
	{
		return false;
	}
	
	while(ptrCursor->more())
	{
		boRecord = ptrCursor->nextSafe();
		PrepareData(boRecord);
	}
	ptrCursor.reset();
	return true;
}

bool CComputeServerDataProcessor::LoadRoles()
{
	bool bResult = true;

	BSONObj boRecord;
	string strRoleName;
	string strRoleID;

	auto_ptr<DBClientCursor> ptrCursor = auto_ptr<DBClientCursor>();
	
	if (!m_pAdminProductRolesController->FindOperatingProductRoles(ptrCursor))
	{
		return false;
	}
	//cout << "Found Record" << endl;
	try
	{
		while(ptrCursor->more())
		{
			boRecord    = ptrCursor->nextSafe();
			//cout << "Record:" << boRecord.toString() << endl;
			strRoleName = CMongodbModel::GetStringFieldValue(boRecord, "role_name", "");
			strRoleID	= (!boRecord.hasField("_id")) ? "" : CUtilities::GetMongoObjId(boRecord.getField("_id").toString(false));
			
			if (strRoleID == "" || strRoleName == "")
				continue;

			RoleID2RoleName::iterator it = m_mapRoleID2RoleName.find(strRoleID);
			if (it == m_mapRoleID2RoleName.end())
			{
				m_mapRoleID2RoleName[strRoleID] = strRoleName;
			}
		}
		ptrCursor.reset();
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CComputeServerDataProcessor", "LoadRoles","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		bResult = false;
	}
	//cout << "Finished Load Roles" << endl;
	return bResult;
}

bool CComputeServerDataProcessor::LoadUsers()
{
	bool bResult = true;
	BSONObj boRecord;
	string strUserName;

	auto_ptr<DBClientCursor> ptrCursor = auto_ptr<DBClientCursor>();

	if (!m_pUserController->FindOperatingUser(ptrCursor))
	{
		return false;
	}
	try
	{
		while(ptrCursor->more())
		{
			boRecord = ptrCursor->nextSafe();
			strUserName = CMongodbModel::GetStringFieldValue(boRecord, "username");

			if(strUserName == "")
				continue;

			m_vtUsers.push_back(strUserName);
		}
		ptrCursor.reset();
	}
	catch(exception& ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CComputeServerDataProcessor", "LoadUsers","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		bResult = false;
	}
	//cout << "Finished Load Users" << endl;
	return bResult;
}

void CComputeServerDataProcessor::ClearUsers()
{
	m_vtUsers.clear();
}

string CComputeServerDataProcessor::GetRoleNameByRoleID(BSONElement beRoleID)
{
	string strRoleID, strRoleName;
	
	strRoleName = "";
	strRoleID   = CUtilities::GetMongoObjId(beRoleID.toString(false));

	RoleID2RoleName::iterator it = m_mapRoleID2RoleName.find(strRoleID);

	if (it != m_mapRoleID2RoleName.end())
		strRoleName = (*it).second;

	return strRoleName;
}

void CComputeServerDataProcessor::PrepareData(const BSONObj& boServerInfo)
{
	//TO DO
	string strProductCode;

	strProductCode = CMongodbModel::GetStringFieldValue(boServerInfo, "product_code", "");
	//cout << "Product Code:" << strProductCode << endl;

	if (strProductCode != "" && strProductCode != "NA")
	{
		if (!IsProductLoaded(strProductCode))
		{
			//cout << "Product was not loaded!!!" << endl;
			LoadRoleGroupProductByProductCode(strProductCode);
			LoadRoleProductOwnerByProductCode(strProductCode);
		}
		else
		{
			//cout << "Product loaded!!!" << endl;
		}
	}
}

bool CComputeServerDataProcessor::IsProductLoaded(const string &strProductCode)
{
	bool bResult = false;
	ProductKey2ProductOwnerRole::iterator it = m_mapProductCode2ProductOwnerRole.find(strProductCode);

	if (it != m_mapProductCode2ProductOwnerRole.end())
	{
		bResult = true;
	}
	return bResult;
}
bool CComputeServerDataProcessor::LoadRoleProductOwnerByProductCode(const string &strProductCode)
{
	//cout << "Starting Load Role Product Owner..." << endl;
	bool bResult = true;

	BSONObj boRecord;
	auto_ptr<DBClientCursor> ptrCursor = auto_ptr<DBClientCursor>();
	UserName2RoleOwnerModel* ptrMapUserName2RoleOwnerModel;

	CRoleOwnerModel* pRoleOwnerModel;

	
	if (!m_pAdminProductOwnerController->FindOperatingRoleOwnerByProductCode(ptrCursor, strProductCode))
		return false;
	
	try
	{
		ProductKey2ProductOwnerRole::iterator it = m_mapProductCode2ProductOwnerRole.find(strProductCode);
		if(it != m_mapProductCode2ProductOwnerRole.end())
		{
			ptrMapUserName2RoleOwnerModel = (*it).second;
		}
		else
		{
			ptrMapUserName2RoleOwnerModel = new UserName2RoleOwnerModel;
			m_mapProductCode2ProductOwnerRole[strProductCode] = ptrMapUserName2RoleOwnerModel;
		}

		while(ptrCursor->more())
		{
			boRecord = ptrCursor->nextSafe();
			RemoveUserRoleInGroup(boRecord, ptrMapUserName2RoleOwnerModel); //Remove user role if exists in group product
			//cout << "Remove User Role Okie" << endl;
			AddRoleOwnerModel(boRecord, ptrMapUserName2RoleOwnerModel);
			//cout << "Add Role Owner Okie" << endl;
		}
		ptrCursor.reset();
	}
	
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CComputeServerDataProcessor", "LoadRoleProductOwnerByProductCode","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		bResult = false;
	}
	return bResult;
}

bool CComputeServerDataProcessor::LoadRoleGroupProductByProductCode(const string& strProductCode)
{
	//cout << "Staring Load Role Group Product..." << endl;
	bool bResult = true;

	BSONObj boRecord;
	BSONArray baGroupProduct;

	auto_ptr<DBClientCursor> ptrCursorGroupProduct = auto_ptr<DBClientCursor>();
	auto_ptr<DBClientCursor> ptrCursorGroupUser = auto_ptr<DBClientCursor>();
	
	UserName2RoleOwnerModel* ptrMapUserName2RoleOwnerModel;
	CRoleOwnerModel* pRoleOwnerModel;
	
	try
	{
		baGroupProduct = m_pAdminUserGroupsProductsController->GetListUserGroupsProducts(ptrCursorGroupProduct,strProductCode);
		//cout << "List Group Product:" << baGroupProduct.toString() << endl;

		if (!m_pAdminUserGroupsUsersController->FindOperatingUserRoleByGroupProduct(ptrCursorGroupUser, baGroupProduct))
			return false;

		ProductKey2ProductOwnerRole::iterator it = m_mapProductCode2ProductOwnerRole.find(strProductCode);
		if(it != m_mapProductCode2ProductOwnerRole.end())
		{
			ptrMapUserName2RoleOwnerModel = (*it).second;
		}
		else
		{
			ptrMapUserName2RoleOwnerModel = new UserName2RoleOwnerModel;
			m_mapProductCode2ProductOwnerRole[strProductCode] = ptrMapUserName2RoleOwnerModel;
		}

		while(ptrCursorGroupUser->more())
		{
			boRecord = ptrCursorGroupUser->nextSafe();
			AddRoleOwnerModel(boRecord, ptrMapUserName2RoleOwnerModel);
		}
		ptrCursorGroupProduct.reset();
		ptrCursorGroupUser.reset();
	}
	
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CComputeServerDataProcessor", "LoadRoleGroupProductByProductCode","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		bResult = false;
	}
	return bResult;
}

bool CComputeServerDataProcessor::AddRoleOwnerModel(const BSONObj& boInfo, UserName2RoleOwnerModel *ptrMapUserName2RoleOwnerModel)
{
	bool bResult = true;
	CRoleOwnerModel *pRoleOwnerModel = NULL;
	string strUserName;
	string strRoleName;
	
	strUserName = strRoleName = "";
	try
	{
		strUserName = CMongodbModel::GetStringFieldValue(boInfo, "username", "");
		//cout << "Role Owner:" << boInfo.toString() << endl;

		if (boInfo.hasField("role_id"))
		{
			strRoleName = GetRoleNameByRoleID(boInfo["role_id"]);
		}
		else if (boInfo.hasField("role"))
		{
			strRoleName = GetRoleNameByRoleID(boInfo["role"]);
		}
		
		if (strUserName != "" && strRoleName != "" && IsUserExists(strUserName))
		{
			//cout << "User:" << strUserName << " - role:" << strRoleName << endl;

			UserName2RoleOwnerModel::iterator it = ptrMapUserName2RoleOwnerModel->find(strUserName);
			if (it != ptrMapUserName2RoleOwnerModel->end())
			{
				pRoleOwnerModel = (*it).second;
			}
			else
			{
				pRoleOwnerModel = new CRoleOwnerModel();
				pRoleOwnerModel->Load(boInfo);
				(*ptrMapUserName2RoleOwnerModel)[strUserName] = pRoleOwnerModel;
			}
			//cout << "Add Role Name" << endl;
			pRoleOwnerModel->AddRoleName(strRoleName);
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CComputeServerDataProcessor", "CreateRoleOwnerModel","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		bResult = false;
	}
	return bResult;
}

bool CComputeServerDataProcessor::RemoveUserRoleInGroup(const BSONObj& boInfo, UserName2RoleOwnerModel *pMapUserName2RoleOwnerModel)
{
	//cout << "Starting remove user role in group..." << endl;
	bool bResult = true;
	string strUserName;
	
	try
	{
		strUserName = CMongodbModel::GetStringFieldValue(boInfo, "username", "");
		//cout << "user is removed:" << strUserName << endl;
		UserName2RoleOwnerModel::iterator it = pMapUserName2RoleOwnerModel->find(strUserName);

		if (it != pMapUserName2RoleOwnerModel->end())
		{
			delete (*it).second;
			(*it).second = NULL;
			pMapUserName2RoleOwnerModel->erase(it);
		}
		
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CComputeServerDataProcessor", "RemoveUserRoleInGroup","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		bResult = false;
	}
	return bResult;
}

void CComputeServerDataProcessor::CalculateTechnicalOwner(const string& strProductCode, UserName2RoleOwnerModel *pMapUserName2RoleOwnerModel)
{
	CRoleOwnerModel *pRoleOwnerModel = NULL;
	//BSONArrayBuilder arr_baTechnicalInfo;
	string strUserName;
	vector<string> vt_RoleName;

	UserName2RoleOwnerModel::iterator itRoleOwnerModel = pMapUserName2RoleOwnerModel->begin();
	while(itRoleOwnerModel != pMapUserName2RoleOwnerModel->end())
	{
		//BSONObj boRoleOwnerInfo;
		pRoleOwnerModel = (*itRoleOwnerModel).second;
		strUserName = pRoleOwnerModel->GetUserName();
		vt_RoleName = pRoleOwnerModel->GetRoleName();
		
		BuildTechnicalOwnerFormatting(vt_RoleName, strUserName);

		//pRoleOwnerModel->Save(boRoleOwnerInfo);
		//arr_baTechnicalInfo << boRoleOwnerInfo;

		itRoleOwnerModel++;
	}
	UpdateTechnicalOwnerServerByProduct(strProductCode);
}

void CComputeServerDataProcessor::BuildTechnicalOwnerFormatting(const std::vector<string>& vt_RoleName, const std::string& strUserName)
{
	string strRoleName;
	CTechnicalOwnerModel *pTechnicalOwnerModel = NULL;

	for(int i=0; i < vt_RoleName.size(); i++)
	{
		strRoleName = vt_RoleName[i];
		RoleName2TechnicalOwner::iterator it = m_mapRoleName2TechnicalOwner.find(strRoleName);

		if (it != m_mapRoleName2TechnicalOwner.end())
		{
			pTechnicalOwnerModel = (*it).second;
		}
		else
		{
			pTechnicalOwnerModel = new CTechnicalOwnerModel();
			pTechnicalOwnerModel->SetRoleName(strRoleName);
			m_mapRoleName2TechnicalOwner[strRoleName] = pTechnicalOwnerModel;
		}
		pTechnicalOwnerModel->AddUser(strUserName);
	}
}

void CComputeServerDataProcessor::UpdateTechnicalOwnerServerByProduct(const string& strProductCode)
{
	CTechnicalOwnerModel *pTechnicalOwnerModel = NULL;
	BSONArrayBuilder arr_baTechnicalOwnerInfo;

	RoleName2TechnicalOwner::iterator it = m_mapRoleName2TechnicalOwner.begin();
	while(it != m_mapRoleName2TechnicalOwner.end())
	{
		BSONObj boTechnicalOwnerInfo;

		pTechnicalOwnerModel = (*it).second;
		pTechnicalOwnerModel->Save(boTechnicalOwnerInfo);

		arr_baTechnicalOwnerInfo << boTechnicalOwnerInfo;
		it++;
	}
	Query qProductCond = QUERY("product_code" << strProductCode);
	m_pCIController->Update(BSON("$set" << BSON("technical_owner" << arr_baTechnicalOwnerInfo.arr())), qProductCond);
}

void CComputeServerDataProcessor::ClearTechnicalOwner()
{
	RoleName2TechnicalOwner::iterator it = m_mapRoleName2TechnicalOwner.begin();
	while (it != m_mapRoleName2TechnicalOwner.end())
	{
		if (NULL != (*it).second)
			delete (*it).second;
		it++;
	}
	m_mapRoleName2TechnicalOwner.clear();
}
void CComputeServerDataProcessor::ComputeData()
{
	//TO DO
	//cout << "Starting Compute Data..." << endl;
	string strProductCode;
	try
	{
		ProductKey2ProductOwnerRole::iterator it = m_mapProductCode2ProductOwnerRole.begin();
		while(it != m_mapProductCode2ProductOwnerRole.end())
		{
			strProductCode = (*it).first;
			UserName2RoleOwnerModel* pMapUserName2RoleOwnerModel = (*it).second;
			CalculateTechnicalOwner(strProductCode, pMapUserName2RoleOwnerModel);
			ClearTechnicalOwner();
			it++;
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CComputeServerDataProcessor", "ComputeData","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	//cout << "Finished Compute Data..." << endl;
}

//void CComputeServerDataProcessor::ComputeSpecialDataInfo(const mongo::BSONObj &boServerInfo, const mongo::BSONObj &boChangedFields)
//{
//	string strProductCode = "";
//	strProductCode = CMongodbModel::GetStringFieldValue(boChangedFields, "product_code", "");
//	
//	if (strProductCode != "" && strProductCode != "NA")
//		ComputeTechnicalOwnerInfo(boServerInfo);
//}

void CComputeServerDataProcessor::ComputeTechnicalOwnerInfo(const mongo::BSONObj &boServerInfo)
{
	string strProductCode = "";
	
	strProductCode = CMongodbModel::GetStringFieldValue(boServerInfo, "product_code", "");

	if (strProductCode == "" || strProductCode == "NA")
		return;

	if (!LoadRoles())	
	{	
		//cout << "Can not load roles" << endl;
		return;
	}
	
	if (!LoadUsers())
	{
		return;
	}
	//cout << "Load Roles Okie" << endl;
	try
	{
		PrepareData(boServerInfo);
		//cout << "Prepare data successful" << endl;
		//strProductCode = CMongodbModel::GetStringFieldValue(boServerInfo, "product_code", "");

		ProductKey2ProductOwnerRole::iterator it = m_mapProductCode2ProductOwnerRole.find(strProductCode);
		//cout << "Found product:" << strProductCode << endl;
		if (it != m_mapProductCode2ProductOwnerRole.end())
		{
			UserName2RoleOwnerModel* pMapUserName2RoleOwnerModel = (*it).second;
			CalculateTechnicalOwner(strProductCode, pMapUserName2RoleOwnerModel);
			
			ClearTechnicalOwner();
			ClearProductOwnerRole();
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CComputeServerDataProcessor", "ComputeTechnicalOwnerInfo","Exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}

	ClearProductRoles();
	ClearUsers();

	//cout << "Finished compute technical owner ..." << endl;
}
bool CComputeServerDataProcessor::IsUserExists(const string& strUserName)
{
	std::vector<string>::iterator it = std::find(m_vtUsers.begin(), m_vtUsers.end(), strUserName);
	if (it != m_vtUsers.end())
		return true;
	return false;
}