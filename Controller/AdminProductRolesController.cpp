#include "AdminProductRolesController.h"
#include "../Common/DBCommon.h"

CAdminProductRolesController::CAdminProductRolesController(void)
{
	m_strTableName = TBL_PRODUCT_ROLES;
}

CAdminProductRolesController::~CAdminProductRolesController(void)
{
}

bool CAdminProductRolesController::FindOperatingProductRoles(auto_ptr<DBClientCursor> &ptrCursor)
{
	bool bResult = Find(ptrCursor,
		QUERY(
			"deleted" << 0 << "ignore" << 0)
		);
	return bResult;
}