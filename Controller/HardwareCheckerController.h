#pragma once
#include "CheckerController.h"

class CCollectorModel;
class CHardwareCheckerModel;
class CHardwareChecker;

typedef map<string, CHardwareCheckerModel*> SerialNumber2HardwareInfoMap;

class CHardwareCheckerController :
	public CCheckerController
{
public:
	CHardwareCheckerController(void);
	~CHardwareCheckerController(void);

	//----------- Compare Hardware Info ------------//
	void CompareHardwareWithSnS(CCollectorModel *pCollectorInfo, CHardwareChecker *pHardwareChecker);
	void LoadCMDBHardwareInfo(auto_ptr<DBClientCursor> &ptrServerResultCursor);
	void ClearMapHardwareInfo();
	CHardwareCheckerModel* GetHardwareCheckerInfoBySerialNumber(const string& strSerialNumber);
	string GetSnSCpuInfo(char* pData);
	string GetSnSServerModelInfo(char* pData);
	void SaveHardwareCheckerInfo(const string& strTableName, CHardwareCheckerModel *pHardwareCheckerModel);
	//----------------------------------------------//

protected:
	CHardwareCheckerModel* GetHardwareCheckerInfoBySerialNumber(char* pSerialNumber);
protected:
	SerialNumber2HardwareInfoMap m_mapSerialNumber2DHardwareInfoMap;
};
