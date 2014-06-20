#include "TechnicalOwnerModel.h"

#define FIELD_ROLE "role"
#define FIELD_USERS "users"

CTechnicalOwnerModel::CTechnicalOwnerModel(void)
{
}

CTechnicalOwnerModel::~CTechnicalOwnerModel(void)
{
}

void CTechnicalOwnerModel::ListUser2UserInfo()
{
	BSONArrayBuilder arrBuilderUserName;
	
	for(int i = 0; i < m_vtUserName.size(); i++)
	{
		arrBuilderUserName << m_vtUserName[i];
	}
	m_barrUserInfo = arrBuilderUserName.arr();
}

void CTechnicalOwnerModel::BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat)
{
	ListUser2UserInfo();

	boBuilder.append(FIELD_ROLE, m_strRoleName);
	boBuilder.append(FIELD_USERS, m_barrUserInfo);
}

void CTechnicalOwnerModel::AddUser(const std::string &strUserName)
{
	if (!IsUserExists(strUserName))
		m_vtUserName.push_back(strUserName);
}

bool CTechnicalOwnerModel::IsUserExists(const std::string &strUserName)
{
	for(int i = 0; i < m_vtUserName.size(); i++)
	{
		if (strUserName == m_vtUserName[i])
			return true;
	}
	return false;
}