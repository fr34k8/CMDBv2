#include "RoleOwnerModel.h"

#define FIELD_USERNAME "username"
#define FIELD_ROLES "roles"

CRoleOwnerModel::CRoleOwnerModel(void)
{
}

CRoleOwnerModel::~CRoleOwnerModel(void)
{
}


void CRoleOwnerModel::AddRoleName(const std::string &strRoleName)
{
	if (!IsRoleExists(strRoleName))
	{
		m_vtRoleName.push_back(strRoleName);
	}
}

bool CRoleOwnerModel::IsRoleExists(const std::string &strRoleName)
{
	for(int i = 0; i < m_vtRoleName.size(); i++)
	{
		if (strRoleName == m_vtRoleName[i])
			return true;
	}
	return false;
}

void CRoleOwnerModel::RoleList2RoleInfo()
{
	BSONArrayBuilder arrBuilderRoleName;
	
	for(int i = 0; i < m_vtRoleName.size(); i++)
	{
		arrBuilderRoleName << m_vtRoleName[i];
	}
	m_barrRoleInfo = arrBuilderRoleName.arr();
}

void CRoleOwnerModel::Load(const BSONObj& boRecord)
{
	m_strUserName = CMongodbModel::GetStringFieldValue(boRecord, "username", "");
}


void CRoleOwnerModel::BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat)
{
	RoleList2RoleInfo();

	boBuilder.append(FIELD_USERNAME, m_strUserName);
	boBuilder.append(FIELD_ROLES, m_barrRoleInfo);
}