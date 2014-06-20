#pragma once
#include "CMDBController.h"

class CPartnerInfoModel;
class CNotificationModel;
typedef map<string, CPartnerInfoModel*> PartnerName2PartnerInfoMap;
class CPartnerInfoController :
	public CCMDBController
{
public:
	CPartnerInfoController(void);
	virtual ~CPartnerInfoController(void);

	bool LoadPartnerInfo();
	CNotificationModel* GetNotificationModel(const string& strPartnerName, const string& strTableName);
	bool IsPartnerName(const string& strPartnerName);
protected:
	CPartnerInfoModel* GetPartnerInfoByPartnerName(const string& strPartnerName);
protected:
	PartnerName2PartnerInfoMap m_mapPartnerName2PartnerInfo;
};
