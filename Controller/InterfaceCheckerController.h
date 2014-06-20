#pragma once
#include "CheckerController.h"
#include "../Model/JsonModel.h"

class CCollectorModel;
class CInterfaceCheckerModel;

typedef map<string, CInterfaceCheckerModel*> Code2InterfaceInfoMap;

class CInterfaceCheckerController :
	public CCheckerController
{
public:
	CInterfaceCheckerController(void);
	~CInterfaceCheckerController(void);
	
	//----------- Compare Interface Info -----------//
	void CompareInterfaceWithODA(CCollectorModel *pCollectorInfo, char* pData);
	void ClearMapInterfaceInfo();
	void LoadCMDBInterfaceInfo(auto_ptr<DBClientCursor> &ptrServerResultCursor);
	void SaveAllServerInterfaceInfo(const string& strTableName);
	void SaveInterfaceCheckerInfo(const string& strTableName, CInterfaceCheckerModel *pInterfaceCheckerModel);
	bool IsMatchInterface(BSONArray baSourceInterface, Json::Value joDescInterface);
	bool IsInterfaceExists(BSONObj boInterface, Json::Value jarrInterfaceInfo);
	vector<BSONObj> GetFilterInterface(vector<BSONObj> vtInterface);
	BSONArray GetInterfaceList(BSONElement beInterface);
	BSONArray ConvertJson2BsonArray(Json::Value joValue);
	//----------------------------------------------//
protected:
	CInterfaceCheckerModel* GetInterfaceCheckerInfoByCode(const string& strCode);
protected:
	Code2InterfaceInfoMap m_mapCode2InterfaceInfoMap;
};
