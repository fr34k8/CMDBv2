#pragma once
#include "CMDBController.h"

class CCIRelationshipModel;
class CNotificationModel;
typedef map<string, BSONObj*> Field2CIRelationshipMap;
class CCIRelationshipController :
	public CCMDBController
{
public:
	CCIRelationshipController(void);
	~CCIRelationshipController(void);

	
protected:

public:
	bool InsertTmpCI(string strTableName, vector<BSONObj> vboBulkData);

};
