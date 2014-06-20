#pragma once
#include "MongodbModel.h"

class CCIInfoChangeModel:
	public CMongodbModel
{
public:
	CCIInfoChangeModel(void);
	virtual ~CCIInfoChangeModel(void);
	virtual vector<BSONObj> GetMiningCursor(BSONObj boCIInfoRecord);
	virtual bool GetCIInfoChangeCursor(vector<BSONObj> &vCIInfoChangeCursor, BSONElement beObjID, BSONObj boOldCIInfoRecord, BSONObj boNewCIInfoRecord);
	virtual void PushValueToCursor(vector<BSONObj> &vInfoCursor, string strOldVal, string strNewVal, string strFieldName, BSONElement beObjID);
	virtual void PushArrayValueToCursor(vector<BSONObj> &vInfoCursor, BSONElement beArrayInfo, string strFieldArrayName, BSONElement beObjID);
	virtual void PushArrayValueToCursor(vector<BSONObj> &vInfoCursor, BSONElement beArrayOldInfo, BSONElement beArrayNewInfo, string strFieldArrayName, BSONElement beObjID);

	bool IsInfoChanged(string strFieldName);
protected:
	void InitLookUpMap();
	virtual void InitLookUpByPass(){};
	virtual void InitLookUpFieldValue(){};
	string MapLookUpField(string strFieldName, string strVal);
	map< string, map<string, string> > m_mapLookUpFieldValue;
	map<string, bool> m_mapLookUpByPass;
	map<string, int> m_mapLookUpChangedField;
	bool m_bIsValueMapping;
};