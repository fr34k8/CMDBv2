#pragma once
#include "../Common/Common.h"
#include "mongo/client/dbclient.h"
#include "mongo/bson/bsonobjbuilder.h"
using namespace mongo;

//====Field Type====
#define BSON_STRING_TYPE 2
#define BSON_OBJECT_TYPE 3
#define BSON_ARRAY_TYPE 4
#define BSON_OBJECTID_TYPE 7
#define BSON_INT_TYPE 16
#define BSON_TIMESTAMP_TYPE 17
#define BSON_LONG_LONG_TYPE 18

#define FIELD_ID "_id"

typedef vector<BSONObj> BSONObjArray;
typedef map<string, int> FieldIndexMap;
typedef map<string, int> FieldTypeMap;
typedef map<string, bool> FieldSetMap;
class CMongodbModel
{
public:
	CMongodbModel(void);
	CMongodbModel(BSONObj objBSON);
	virtual ~CMongodbModel(void);

	virtual operator int() { return -1; }
	virtual operator string() { return ""; }
	virtual operator BSONArray() { BSONArray boArray; return boArray; }
	virtual operator BSONElement() { BSONElement be; return be; }

	virtual CMongodbModel& operator=(int iValue) { m_mapFieldSet[m_strCurrentField] = true; return *this; }
	virtual CMongodbModel& operator=(string strValue) { m_mapFieldSet[m_strCurrentField] = true; return *this; }
	virtual CMongodbModel& operator=(BSONArray boValue) { m_mapFieldSet[m_strCurrentField] = true; return *this; }
	virtual CMongodbModel& operator=(BSONElement beValue) { m_mapFieldSet[m_strCurrentField] = true; return *this; }

	virtual void Load(const BSONObj& boRecord) {}
	virtual void Save(BSONObj& boRecord, int iFormat = 0);
	virtual bool ToBSONObj(BSONObj& boRecord);
	CMongodbModel& operator[](const char* strFieldName);	

	operator BSONObj() { return m_objBSON; }
	operator BSONObj*() { return &m_objBSON; }

	inline CMongodbModel operator=(const BSONObj& objBSON) { m_objBSON = objBSON; return *this;}
	inline void UpdateBSONObj(const BSONObj& objBSON) { m_objBSON = objBSON; }
	inline BSONElement GetOID() { return m_objBSON["_id"]; }

	static BSONObj RemoveFields(BSONObj *pRecord, StringArray &arrFieldName);
	static BSONObj MergeBSONObj(BSONObj *pOldRecord, BSONObj *pNewRecord);
	static BSONObj MergeBSONObj(BSONObj *pOldRecord, BSONObj *pNewRecord, BSONObj &pboChangedFields);
	static BSONElement GetField(BSONObj *pboObj, string strField);
	static BSONObj ConvertBSONObj(BSONObj boRecord, map<string, string> mapField);
	static int GetIntFieldValue(BSONObj boRecord, string strFieldName, int iExceptionValue = 0);
	static string GetStringFieldValue(BSONObj boRecord, string strFieldName, string strExceptionValue = "");
	static void TrackChangeArray(vector<BSONElement> &vbeOldArray, vector<BSONElement> &vbeNewArray, vector<BSONElement> &vbeDeletedArray);

protected:
	virtual void BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat = 0) {}
	static bool GetArrayFieldValue(const BSONObj& boInfo, string strFieldName, 
									std::vector<BSONElement>& vtValue);
protected:
	BSONObjBuilder *m_pBSONBuilder;
	BSONObj m_objBSON;
	string m_F;
	FieldIndexMap m_mapFieldIndex;
	FieldSetMap m_mapFieldSet;
	int m_iFieldIndex;
	string m_strCurrentField;
	BSONElement m_beOID;
	FieldTypeMap m_mapFieldType;
};
