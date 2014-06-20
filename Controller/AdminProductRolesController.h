#pragma once
#include "AdminController.h"

class CAdminProductRolesController:
	public CAdminController
{
public:
	CAdminProductRolesController(void);
	~CAdminProductRolesController(void);

	bool FindOperatingProductRoles(auto_ptr<DBClientCursor>& ptrCursor);
};