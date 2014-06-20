#include "AdminUserGroupsProductsController.h"
#include "../Common/DBCommon.h"

CAdminUserGroupsProductsController::CAdminUserGroupsProductsController(void)
{
	m_strTableName = TBL_USER_GROUPS_PRODUCTS;
}

CAdminUserGroupsProductsController::~CAdminUserGroupsProductsController(void)
{
}

bool CAdminUserGroupsProductsController::FindOperatingUserGroupByProduct(auto_ptr<DBClientCursor>& ptrCursor, const string &strProductCode)
{
	bool bResult = Find(ptrCursor,
		QUERY(
			"product_key" << strProductCode <<
			"deleted" << 0)
		);
	return bResult;
}

BSONArray CAdminUserGroupsProductsController::GetListUserGroupsProducts(auto_ptr<DBClientCursor>& ptrCursor, const string &strProductCode)
{
	BSONArrayBuilder baGroupProduct;
	BSONObj boRecord;
	
	if (FindOperatingUserGroupByProduct(ptrCursor, strProductCode))
	{
		try
		{
			while(ptrCursor->more())
			{
				boRecord = ptrCursor->nextSafe();
				baGroupProduct << boRecord["user_group_id"];
			}
		}
		catch(exception& ex)
		{	
			stringstream strErrorMess;
			string strLog;
			strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CAdminUserGroupsProductsController", "GetListUserGroupsProducts","Exception:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		}
	}
	return baGroupProduct.arr();
}
