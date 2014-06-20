#pragma once
#include "CMDBController.h"

class CCollectorModel;
class CDepartmentModel;
class CDepartmentDefenseInfoModel;

typedef map<string, CDepartmentModel*> HRCode2DepartmentInfoMap;
typedef map<string, CDepartmentDefenseInfoModel*> HRCode2DepartmentDefenseInfoMap;

class CDepartmentController :
	public CCMDBController
{
public:
	CDepartmentController(void);
	~CDepartmentController(void);

	void CompareFullData(CCollectorModel* pCollectorInfo, char *pData);
	void CompareChangeData(CCollectorModel* pCollectorInfo, char *pData);
	bool IsMatchDepartmentInfo(const string& strOrgCode, const string& strOrgDivisionCode);

	void PushDirtyDepartmentOrgChart(const string& strDirtyTable, 
									 const string& strOrgCode, 
									 const string& strOrgId, 
									 const string& strOrgDivisionCode,
									 const string& strOrgDivisionId,
									 int iFlag);
	void SaveDepartmentInfo(CDepartmentModel *pDepartmentModel);
	void SaveDepartmentDefenseInfo(const string& strTableName, CDepartmentDefenseInfoModel *pDepartmentDefenseModel);
	BSONObj GetDivisionObjectByAlias(auto_ptr<DBClientCursor> &ptrDivisionResultCursor, const string& strAlias);

protected:
	CDepartmentModel* GetDepartmentInfoByHRCode(const string& strOrgCode);
	CDepartmentDefenseInfoModel* GetDepartmentDefenseInfoByHRCode(const string& strOrgCode);
	
	void ClearMapDepartmentInfo();
	void ClearMapDepartmentDefenseInfo();
	
protected:
	HRCode2DepartmentInfoMap m_mapHRCode2DepartmentInfoMap;
	HRCode2DepartmentDefenseInfoMap m_mapHRCode2DepartmentDefenseInfo;
};
