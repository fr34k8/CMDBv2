#include "AdminProductOwnerController.h"
#include "../Common/DBCommon.h"

CAdminProductOwnerController::CAdminProductOwnerController(void)
{
	m_strTableName = TBL_PRODUCT_OWNER;
}

CAdminProductOwnerController::~CAdminProductOwnerController(void)
{
}

bool CAdminProductOwnerController::FindOperatingRoleOwnerByProductCode(auto_ptr<DBClientCursor>& ptrCursor, const string& strProductCode)
{
	bool bResult = Find(ptrCursor,
		QUERY(
			"product_key" << strProductCode <<
			"deleted" << 0)
		);
	return bResult;
}