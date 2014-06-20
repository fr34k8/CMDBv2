#pragma once
#include "InternalDataCheckProcessor.h"

class CServerModel;
typedef vector<CServerModel*> ServerModelArray;
typedef map<string, ServerModelArray*> RackName2ServerModelArrayMap;
class CInternalServerDataCheckProcessor :
	public CInternalDataCheckProcessor
{
public:
	CInternalServerDataCheckProcessor(const string& strFileName);
	~CInternalServerDataCheckProcessor(void);
protected:
	bool LoadData();
	void CheckData();
	void CheckLocation(ServerModelArray* pServerModelArray);
private:
	void LoadServer(BSONObj& boServerRecord);
	void DestroyData();
	void InsertDuplicatedLocationServer(CServerModel* pServerModel);
protected:
	RackName2ServerModelArrayMap m_mapRackName2ServerModelArray;
};
