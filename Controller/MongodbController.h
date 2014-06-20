#pragma once
#include "../Common/Common.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

#define MAX_STRING_VALUE_LEN	1024
typedef struct _tMongodbField
{
	string strName;
	int iDataType;
	union
	{
		int iValue;
		float fValue;
		wchar_t strValue[MAX_STRING_VALUE_LEN];
	};
} tMongodbField;

typedef std::vector<tMongodbField> MongodbFieldArray;

class CMongodbController
{
public:
	CMongodbController(void);
	virtual ~CMongodbController(void);
	
	bool Connect(ConnectInfo CInfo);
	auto_ptr<DBClientCursor> Find(Query queryCondition = Query(), int iLimit = 0, int iSkip = 0);
	auto_ptr<DBClientCursor> Find(string strTable, Query queryCondition = Query());
	bool Find(auto_ptr<DBClientCursor>& ptrCursor, Query queryCondition = Query());
	bool Find(string strTable, auto_ptr<DBClientCursor>& ptrCursor, Query queryCondition = Query());
	bool Insert(string strTable, BSONObj bsonRecord, BSONObj bsonCondition = BSONObj());
	bool Insert(BSONObj bsonRecord, BSONObj bsonCondition = BSONObj());
	bool InsertPartition(BSONObj bsonRecord, BSONObj bsonKeysIndex, string strSuffix, BSONObj bsonCondition = BSONObj());
	bool BulkInsert(vector<BSONObj> vboRecord);
	bool BulkInsert(string strTable, vector<BSONObj> vboRecord);
	bool Update(BSONObj bsonRecord, Query queryCondition);
	bool Update(string strTable, BSONObj bsonRecord, Query queryCondition);
	bool Upsert(BSONObj bsonRecord, Query queryCondition);
	bool Upsert(string strTable, BSONObj bsonRecord, Query queryCondition);
	bool Remove(Query queryCondition);
	bool Remove(string strTable,Query queryCondition);
	long long Count(BSONObj bsonCondition = BSONObj());
	long long Count(string strTable, BSONObj bsonCondition = BSONObj());
	bool IsExisted(Query queryCondition = Query());
	bool IsExisted(string strTable, Query queryCondition = Query());
	inline string GetTableName() { return m_strTableName; }
	inline string GetNameSpace() { return m_strNameSpace; }
	
protected:
	DBClientConnection m_connDB;
	DBClientReplicaSet* m_pRSConnDB;
	bool m_bIsConnected;
	int m_nReadReference; // 0: primary, QueryOption_SlaveOk: secondary
	bool m_bIsReplicaSetUsed;
	string m_strNameSpace;
	string m_strTableName;
	string m_strSource;
	BSONObjBuilder *m_pModel;
};
