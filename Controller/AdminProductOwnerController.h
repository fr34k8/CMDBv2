#pragma once
#include "AdminController.h"

class CAdminProductOwnerController:
	public CAdminController
{
public:
	CAdminProductOwnerController(void);
	~CAdminProductOwnerController(void);

	bool FindOperatingRoleOwnerByProductCode(auto_ptr<DBClientCursor>& ptrCursor, const string& strProductCode);
};