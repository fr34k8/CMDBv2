#include "CIRelationshipController.h"

#include "../Common/DBCommon.h"

CCIRelationshipController::CCIRelationshipController(void)
{
	m_strTableName = TBL_CI_RELATIONSHIP;
}

CCIRelationshipController::~CCIRelationshipController(void)
{

}

bool CCIRelationshipController::InsertTmpCI(string strTableName, vector<BSONObj> vboBulkData)
{
	return BulkInsert(strTableName, vboBulkData);
}
