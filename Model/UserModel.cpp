#include "UserModel.h"

CUserModel::CUserModel(void)
{
	m_strUserName = "";
	m_strFullName = "";
	m_strDepartmentHRCode = "";
}

CUserModel::~CUserModel(void)
{
}

BSONObj CUserModel::GetUserInfo()
{
	BSONObj boDataInfo = BSON("username" << m_strUserName << "full_name" << m_strFullName << 
							  "department_hr_code" << m_strDepartmentHRCode);
	return boDataInfo;
}