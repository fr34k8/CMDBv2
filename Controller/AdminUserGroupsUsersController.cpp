#include "AdminUserGroupsUsersController.h"
#include "../Common/DBCommon.h"

CAdminUserGroupsUsersController::CAdminUserGroupsUsersController(void)
{
	m_strTableName = TBL_USER_GROUPS_USERS;
}

CAdminUserGroupsUsersController::~CAdminUserGroupsUsersController(void)
{
}

bool CAdminUserGroupsUsersController::FindOperatingUserRoleByGroupProduct(std::auto_ptr<DBClientCursor>& ptrCursor, BSONArray baGroupProduct)
{
	bool bResult = Find(ptrCursor,
		QUERY(
			"user_group_id" << BSON("$in" << baGroupProduct) <<
			"deleted" << 0)
		);
	return bResult;
}