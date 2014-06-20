#pragma once
#include "CMDBController.h"

class CCollectorModel;
typedef map<string, CCollectorModel*> CollectorName2CollectorInfoMap;

class CCollectorController :
	public CCMDBController
{
public:
	CCollectorController(void);
	virtual ~CCollectorController(void);

	bool LoadCollectorInfo(const string& strCollectorName);
	bool IsCollectorNameExists(const string& strCollectorName);
	string GetCollectorType(const string& strCollectorName);
	CCollectorModel* GetCollectorInfoByCollectorName(const string& strCollectorName);
protected:
	CollectorName2CollectorInfoMap m_mapCollectorName2CollectorInfo;
};
