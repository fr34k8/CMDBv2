#pragma once
#include "AdminController.h"

class CAdminUserGroupsProductsController:
	public CAdminController
{
public:
	CAdminUserGroupsProductsController(void);
	~CAdminUserGroupsProductsController(void);

	bool FindOperatingUserGroupByProduct(auto_ptr<DBClientCursor>& ptrCursor, const string& strProductCode);
	BSONArray GetListUserGroupsProducts(auto_ptr<DBClientCursor>& ptrCursor, const string& strProductCode);
};