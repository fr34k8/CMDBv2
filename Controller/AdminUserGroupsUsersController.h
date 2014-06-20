#pragma once
#include "AdminController.h"

class CAdminUserGroupsUsersController:
	public CAdminController
{
public:
	CAdminUserGroupsUsersController(void);
	~CAdminUserGroupsUsersController(void);

	bool FindOperatingUserRoleByGroupProduct(auto_ptr<DBClientCursor>& ptrCursor, BSONArray baGroupProduct);
};