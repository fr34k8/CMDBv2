#include "CIInfoChangeModel.h"
#include "../Common/DBCommon.h"

CCIInfoChangeModel::CCIInfoChangeModel(void)
{
}

CCIInfoChangeModel::~CCIInfoChangeModel(void)
{
	m_mapLookUpFieldValue.clear();
	m_mapLookUpChangedField.clear();
	m_mapLookUpByPass.clear();
}


void CCIInfoChangeModel::InitLookUpMap()
{
	m_bIsValueMapping = false;
	m_mapLookUpByPass["_id"] = true;
	m_mapLookUpByPass["deleted"] = true;
	m_mapLookUpByPass["created_date"] = true;
	cout << "InitLookUpMap\n\n";
	InitLookUpFieldValue();
	InitLookUpByPass();
}

string CCIInfoChangeModel::MapLookUpField(string strFieldName, string strVal)
{
	if (!m_bIsValueMapping)
	{
		return strVal;
	}

	string strMapValue;
	strMapValue = m_mapLookUpFieldValue[strFieldName][strVal];
	if(!strMapValue.empty())
	{
		strVal = strMapValue;
	}

	return strVal;
}

bool CCIInfoChangeModel::GetCIInfoChangeCursor(vector<BSONObj> &vCIInfoChangeCursor, BSONElement beObjID, BSONObj boOldCIInfoRecord, BSONObj boNewCIInfoRecord)
{
	bool bResult;
	StringSet setFieldNames;
	StringSet::iterator it;
	string strFieldName, strOldVal, strNewVal;
	int iFieldType;
	bool bIsOldRecordEmpty, bIsNewRecordEmpty;
	try
	{
		bResult = false;
		m_mapLookUpChangedField.clear();
		bIsOldRecordEmpty = boOldCIInfoRecord.isEmpty();
		bIsNewRecordEmpty = boNewCIInfoRecord.isEmpty();

		if(bIsNewRecordEmpty)
		{
			boOldCIInfoRecord.getFieldNames(setFieldNames);
		}
		else
		{
			boNewCIInfoRecord.getFieldNames(setFieldNames);
		}
		// foreach field of the both record for compare
		for(it=setFieldNames.begin(); it!=setFieldNames.end(); it++)
		{
			iFieldType = 0;
			strOldVal = strNewVal = "";
			strFieldName = *it;

			if (boOldCIInfoRecord[strFieldName] != boNewCIInfoRecord[strFieldName])
			{
				bResult = true;
				if (!m_mapLookUpByPass.empty())
				{
					if (m_mapLookUpByPass.find(strFieldName) != m_mapLookUpByPass.end())
					{
						continue;
					}
				}
				// Add changed field to map
				m_mapLookUpChangedField[strFieldName] = 1;

				if(!bIsOldRecordEmpty && boOldCIInfoRecord.hasField(strFieldName)){
					strOldVal = boOldCIInfoRecord[strFieldName].toString(false);
					iFieldType = boOldCIInfoRecord[strFieldName].type();
				}
				if(!bIsNewRecordEmpty && boNewCIInfoRecord.hasField(strFieldName)){
					strNewVal = boNewCIInfoRecord[strFieldName].toString(false);
					iFieldType = boNewCIInfoRecord[strFieldName].type();
				}
				switch(iFieldType)
				{
					case BSON_STRING_TYPE:
						strNewVal = CUtilities::RemoveBraces(strNewVal);
						strOldVal = CUtilities::RemoveBraces(strOldVal);
						PushValueToCursor(vCIInfoChangeCursor, strOldVal, strNewVal, strFieldName, beObjID);
						break;
					case BSON_ARRAY_TYPE:
						PushArrayValueToCursor(vCIInfoChangeCursor, boOldCIInfoRecord[strFieldName], boNewCIInfoRecord[strFieldName], strFieldName, beObjID);
						break;
					case BSON_OBJECTID_TYPE:
						break;
					default:
						PushValueToCursor(vCIInfoChangeCursor, strOldVal, strNewVal, strFieldName, beObjID);
				}
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeModel", "GetCIInfoChangeCursor(BSONObj,BSONObj)", "Exception:" + strErrorMess.str() + "|OID:" + beObjID.toString(false));
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bResult;
}

vector<BSONObj> CCIInfoChangeModel::GetMiningCursor(BSONObj boCIInfoRecord)
{
	vector<BSONObj> vMiningCursor;
	StringSet setFieldNames;
	StringSet::iterator it;
	string strObjId, strFieldName, strVal;
	int iFieldType;
	try
	{
		// Get object id of the record
		strObjId = boCIInfoRecord["_id"].toString(false);
		// Get all field names of the record
		boCIInfoRecord.getFieldNames(setFieldNames);
		// foreach field of the record
		for(it=setFieldNames.begin(); it!=setFieldNames.end(); it++)
		{
			strFieldName = *it;

			if (!m_mapLookUpByPass.empty())
			{
				if (m_mapLookUpByPass.find(strFieldName) != m_mapLookUpByPass.end())
				{
					continue;
				}
			}
			iFieldType = boCIInfoRecord[strFieldName].type();
			switch(iFieldType)
			{
			case BSON_STRING_TYPE:
				strVal = CUtilities::RemoveBraces(boCIInfoRecord[strFieldName].toString(false));
				PushValueToCursor(vMiningCursor, "", strVal, strFieldName, boCIInfoRecord["_id"]);
				break;
			case BSON_ARRAY_TYPE:
				PushArrayValueToCursor(vMiningCursor, boCIInfoRecord[strFieldName], strFieldName, boCIInfoRecord["_id"]);
				break;
			case BSON_OBJECTID_TYPE:
				break;
			default:
				strVal = boCIInfoRecord[strFieldName].toString(false);
				PushValueToCursor(vMiningCursor, "", strVal, strFieldName, boCIInfoRecord["_id"]);
			}
		}
		if(!vMiningCursor.empty())
		{
			CUtilities::WriteErrorLog(INFO_MSG, CUtilities::FormatLog(INFO_MSG, "CCIInfoChangeModel", "GetMiningCursor(BSONObj)", "SuccOID:" + strObjId));
		}
		else
		{
			CUtilities::WriteErrorLog(INFO_MSG, CUtilities::FormatLog(INFO_MSG, "CCIInfoChangeModel", "GetMiningCursor(BSONObj)", "FailOID:" + strObjId));
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeModel", "GetMiningCursor(BSONObj)","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return vMiningCursor;
}

void CCIInfoChangeModel::PushArrayValueToCursor(vector<BSONObj> &vInfoCursor, BSONElement beArrayInfo, string strFieldArrayName, BSONElement beObjID)
{
	vector<BSONElement> vbeInfo;
	StringSet::iterator it;
	StringSet setFieldNames;
	BSONObj boInfo;
	string strVal, strFieldName;
	int iElementType, iFieldType;

	try{
		vbeInfo = beArrayInfo.Array();
		for(int i=0; i<vbeInfo.size(); i++)
		{ 
			iElementType = vbeInfo[i].type();
			if(iElementType == BSON_OBJECT_TYPE)
			{
				boInfo = vbeInfo[i].Obj();
				// Get all field names of the Obj
				boInfo.getFieldNames(setFieldNames);
				
				// foreach field of the Obj
				for(it=setFieldNames.begin(); it!=setFieldNames.end(); it++)
				{
					strFieldName = *it;
					iFieldType = boInfo[strFieldName].type();
					if(iFieldType == BSON_STRING_TYPE)
					{
						strVal = CUtilities::RemoveBraces(boInfo[strFieldName].toString(false));
					}
					else if(iFieldType == BSON_OBJECTID_TYPE)
					{
						continue;
					}
					else if (iFieldType == BSON_ARRAY_TYPE)
					{
						PushArrayValueToCursor(vInfoCursor, boInfo[strFieldName], strFieldArrayName + "." + strFieldName, beObjID);
						continue;
					}
					else
					{
						strVal = boInfo[strFieldName].toString(false);
					}
					PushValueToCursor(vInfoCursor, "", strVal, strFieldArrayName + "." + strFieldName, beObjID);
				}
			}
			else
			{
				if(iElementType == BSON_STRING_TYPE)
				{
					strVal = CUtilities::RemoveBraces(vbeInfo[i].toString(false));
				}
				else if(iElementType == BSON_OBJECTID_TYPE)
				{
					continue;
				}
				else
				{
					strVal = vbeInfo[i].toString(false);
				}
				PushValueToCursor(vInfoCursor, "", strVal, strFieldArrayName, beObjID);
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeModel", "PushArrayValueToCursor(vector<BSONObj>, BSONElement, string)","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CCIInfoChangeModel::PushArrayValueToCursor(vector<BSONObj> &vInfoCursor, BSONElement beArrayOldInfo, BSONElement beArrayNewInfo, string strFieldArrayName, BSONElement beObjID)
{
	vector<BSONElement> vbeInfo, vbeOldInfo, vbeNewInfo;
	StringSet::iterator it;
	StringSet setFieldNames;
	BSONObj boOldInfo, boNewInfo;
	string strNewVal, strOldVal, strFieldName;
	int iElementType, iFieldType, iInfoArrSize, iOldInfoArrSize, iNewInfoArrSize;

	try{
		if(!beArrayOldInfo.eoo())
			vbeOldInfo = beArrayOldInfo.Array();
		if(!beArrayNewInfo.eoo())
			vbeNewInfo = beArrayNewInfo.Array();
		
		iOldInfoArrSize = vbeOldInfo.size();
		iNewInfoArrSize = vbeNewInfo.size();
		for(int i=0; i<iOldInfoArrSize; i++)
		{
			iElementType = vbeOldInfo[i].type();
			if (iElementType == BSON_OBJECT_TYPE)
			{
				boOldInfo = vbeOldInfo[i].Obj();
				// Get all field names of the Obj
				setFieldNames.clear();
				boOldInfo.getFieldNames(setFieldNames);
				it = setFieldNames.begin();
				for (it = setFieldNames.begin(); it != setFieldNames.end(); it++)
				{
					strFieldName = *it;
					strOldVal = boOldInfo[strFieldName].toString(false);
					iFieldType = boOldInfo[strFieldName].type();
					if (iFieldType == BSON_STRING_TYPE)
					{
						strOldVal = CUtilities::RemoveBraces(strOldVal);
					}
					else if (iFieldType == BSON_OBJECTID_TYPE)
					{
						continue;
					}
					else if (iFieldType == BSON_ARRAY_TYPE)
					{
						PushArrayValueToCursor(vInfoCursor, boOldInfo[strFieldName], BSONElement(), strFieldArrayName + "." + strFieldName, beObjID);
						continue;
					}
					PushValueToCursor(vInfoCursor, strOldVal, "", strFieldArrayName + "." + strFieldName, beObjID);
				}
			}
			else
			{
				if (iElementType == BSON_STRING_TYPE)
				{
					strOldVal = CUtilities::RemoveBraces(vbeOldInfo[i].toString(false));
				}
				else if (iElementType == BSON_OBJECTID_TYPE)
				{
					continue;
				}
				else
				{
					strOldVal = vbeOldInfo[i].toString(false);
				}
				PushValueToCursor(vInfoCursor, strOldVal, "", strFieldArrayName, beObjID);
			}
		}
		for(int i=0; i<iNewInfoArrSize; i++)
		{
			iElementType = vbeNewInfo[i].type();
			if (iElementType == BSON_OBJECT_TYPE)
			{
				boNewInfo = vbeNewInfo[i].Obj();
				// Get all field names of the Obj
				setFieldNames.clear();
				boNewInfo.getFieldNames(setFieldNames);
				it = setFieldNames.begin();
				for (it = setFieldNames.begin(); it != setFieldNames.end(); it++)
				{
					strFieldName = *it;
					strNewVal = boNewInfo[strFieldName].toString(false);
					iFieldType = boNewInfo[strFieldName].type();
					if (iFieldType == BSON_STRING_TYPE)
					{
						strNewVal = CUtilities::RemoveBraces(strNewVal);
					}
					else if (iFieldType == BSON_OBJECTID_TYPE)
					{
						continue;
					}
					else if (iFieldType == BSON_ARRAY_TYPE)
					{
						PushArrayValueToCursor(vInfoCursor, BSONElement(), boNewInfo[strFieldName], strFieldArrayName + "." + strFieldName, beObjID);
						continue;
					}
					PushValueToCursor(vInfoCursor, "", strNewVal, strFieldArrayName + "." + strFieldName, beObjID);
				}
			}
			else
			{
				if (iElementType == BSON_STRING_TYPE)
				{
					strNewVal = CUtilities::RemoveBraces(vbeNewInfo[i].toString(false));
				}
				else if (iElementType == BSON_OBJECTID_TYPE)
				{
					continue;
				}
				else
				{
					strNewVal = vbeNewInfo[i].toString(false);
				}
				PushValueToCursor(vInfoCursor, "", strNewVal, strFieldArrayName, beObjID);
			}
		}
	}
	catch(exception& ex)
	{	
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__ ;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCIInfoChangeModel", "PushArrayValueToCursor(vector<BSONObj>, BSONElement, string)","exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CCIInfoChangeModel::PushValueToCursor(vector<BSONObj> &vInfoCursor, string strOldVal, string strNewVal, string strFieldName, BSONElement beObjID)
{
	BSONObj boMiningRecord;
	string strMapValue;
	long long lClock = atol(CUtilities::GetCurrTimeStamp().c_str());
	if(!strOldVal.empty() || !strNewVal.empty())
	{
		strNewVal = MapLookUpField(strFieldName,strNewVal);
		strOldVal = MapLookUpField(strFieldName,strOldVal);
		boMiningRecord = BSON("id"<<beObjID<<"old"<<strOldVal<<"new"<<strNewVal<<"field"<<strFieldName<<"clock"<<lClock);
		vInfoCursor.push_back(boMiningRecord);
	}
}

bool CCIInfoChangeModel::IsInfoChanged(string strFieldName)
{
	map<string, int>::iterator it = m_mapLookUpChangedField.find(strFieldName);
	if (it != m_mapLookUpChangedField.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}