#include "MongodbModel.h"
#include "../Common/DBCommon.h"
CMongodbModel::CMongodbModel(void)
{	
	m_iFieldIndex = -1;
	m_strCurrentField = "";
}

CMongodbModel::CMongodbModel(BSONObj objBSON)
{
	m_objBSON = objBSON.copy();
}

CMongodbModel::~CMongodbModel(void)
{
	m_mapFieldIndex.clear();
	m_mapFieldSet.clear();
	m_mapFieldType.clear();
}

CMongodbModel& CMongodbModel::operator[](const char* strFieldName)
{
	FieldIndexMap::iterator it = m_mapFieldIndex.find(strFieldName);

	// Calculate field index
	if (it != m_mapFieldIndex.end())
	{
		m_strCurrentField = strFieldName;
		m_iFieldIndex = (*it).second;
	}
	else
	{
		m_strCurrentField = "";
		m_iFieldIndex = -1;
	}

	return *this;
}

void CMongodbModel::Save(BSONObj& boRecord, int iFormat)
{
	BSONObjBuilder boBuilder;
	BuildBSONObj(boBuilder, iFormat);
	boRecord = boBuilder.obj();
}

bool CMongodbModel::ToBSONObj(BSONObj& boRecord)
{
	int iValueType;
	BSONObjBuilder boBuilder;
	string strFieldName;
	FieldSetMap::iterator it = m_mapFieldSet.begin();

	if (it == m_mapFieldSet.end())
	{
		return false;
	}		

	while (it != m_mapFieldSet.end())
	{
		strFieldName = (*it).first;
		try 
		{
			iValueType = m_mapFieldType[strFieldName];
		}
		catch (exception& ex)
		{
			it++;
			continue;
		}

		switch (iValueType)
		{
		case BSON_STRING_TYPE:
			boBuilder.append(strFieldName, (string)(*this)[strFieldName.c_str()]);
			break;
		case BSON_INT_TYPE:
			boBuilder.append(strFieldName, (int)(*this)[strFieldName.c_str()]);
			break;
		case BSON_ARRAY_TYPE:
			{
				BSONArray boarrValue = (*this)[strFieldName.c_str()];
				boBuilder.append(strFieldName, boarrValue);
				break;
			}
		case BSON_OBJECT_TYPE:
			boBuilder.append(strFieldName, (BSONObj)(*this)[strFieldName.c_str()]);
			break;
		case BSON_LONG_LONG_TYPE:
			boBuilder.append(strFieldName, (long long int)(*this)[strFieldName.c_str()]);
			break;
		}
		
		it++;
	}

	boRecord = boBuilder.obj();
	m_mapFieldSet.clear();

	return true;
}

BSONElement CMongodbModel::GetField(BSONObj *pboObj, string strField)
{
	/*if (pboObj->hasField(strField))
	{
		return pboObj->getField(strField);
	}*/
	BSONObj boEmpty = BSON(strField << "EOO");
	return boEmpty.getField(strField);
}

void CMongodbModel::TrackChangeArray(vector<BSONElement> &vbeOldArray, vector<BSONElement> &vbeNewArray, vector<BSONElement> &vbeDeletedArray)
{ 
	vector<BSONElement> vbeTmpArray;
	BSONElement beOld, beNew;
	vector<BSONElement>::iterator itOld, itNew;
	string strOld, strNew;
	bool bIsContinue;

	itNew = vbeNewArray.begin();
	while (itNew != vbeNewArray.end())
	{
		bIsContinue = false;
		strOld = strNew = "";
		beNew = *itNew;
		itOld = vbeOldArray.begin();
		while (itOld != vbeOldArray.end())
		{
			beOld = *itOld;
			strOld = beOld.toString(false);
			strNew = beNew.toString(false);
			if (strOld.compare(strNew) == 0)
			{
				vbeOldArray.erase(itOld);
				vbeNewArray.erase(itNew);
				vbeDeletedArray.push_back(beNew);
				itNew = vbeNewArray.begin();
				bIsContinue = true;
				break;
			}
			itOld++;
		}
		if (bIsContinue)//(strOld.compare(strNew) == 0 && !strOld.empty() && !strNew.empty())
		{
			continue;
		}
		itNew++;
	}
	vbeTmpArray = vbeOldArray;
	vbeOldArray.clear();
	vbeOldArray = vbeDeletedArray;
	vbeDeletedArray.clear();
	vbeDeletedArray = vbeTmpArray;
}

BSONObj CMongodbModel::MergeBSONObj(BSONObj *pOldRecord, BSONObj *pNewRecord)
{
	BSONObjBuilder bobMergedRecord;
	StringSet setFieldNames;
	StringSet::iterator it;
	string strFieldName;
	pOldRecord->getFieldNames(setFieldNames);
	bobMergedRecord.appendElements(*pNewRecord);
	for(it=setFieldNames.begin(); it!=setFieldNames.end(); it++)
	{
		strFieldName = *it;
		if(strFieldName.compare("_id") == 0)
		{
			continue;
		}
		if(!pNewRecord->hasField(strFieldName))
		{
			bobMergedRecord.append(pOldRecord->getField(strFieldName));
		}
	}
	return bobMergedRecord.obj();
}

BSONObj CMongodbModel::MergeBSONObj(BSONObj *pOldRecord, BSONObj *pNewRecord, BSONObj &pboChangedFields)
{
	BSONObjBuilder bobMergedRecord;
	BSONObjBuilder bobChangedFields;
	StringSet setFieldNames;
	StringSet::iterator it;
	string strFieldName;
	bobMergedRecord.appendElements(*pNewRecord);
	if(pOldRecord->isEmpty()){
		pNewRecord->getFieldNames(setFieldNames);
	}
	else{
		pOldRecord->getFieldNames(setFieldNames);
	}
	for(it=setFieldNames.begin(); it!=setFieldNames.end(); it++)
	{
		strFieldName = *it;
		if(strFieldName.compare("_id") == 0)
		{
			continue;
		}
		if(!pNewRecord->hasField(strFieldName))
		{
			bobMergedRecord.append(pOldRecord->getField(strFieldName));
		}
		else if(!pOldRecord->hasField(strFieldName))
		{
			bobChangedFields.append(strFieldName, 1);
		}
		else if((*pNewRecord)[strFieldName] != (*pOldRecord)[strFieldName])
		{
			bobChangedFields.append(strFieldName, 1);
		}
	}
	pboChangedFields = bobChangedFields.obj();
	return bobMergedRecord.obj();
}

BSONObj CMongodbModel::ConvertBSONObj(BSONObj boRecord, map<string, string> mapField)
{
	BSONObjBuilder bobCenRecord;
	map<string, string>::iterator mit;
	int iFieldType;
	try{
		for (mit = mapField.begin(); mit != mapField.end(); mit++)
		{
			if (boRecord.hasField(mit->second)){
				iFieldType = boRecord[mit->second].type();
				switch (iFieldType)
				{
				case BSON_STRING_TYPE:
					bobCenRecord.append(mit->first, boRecord.getStringField(mit->second.c_str()));
					break;
				case BSON_INT_TYPE:
					bobCenRecord.append(mit->first, boRecord[mit->second]._numberInt());
					break;
				case BSON_TIMESTAMP_TYPE:
					bobCenRecord.append(mit->first, boRecord[mit->second]._numberLong());
					break;
				case BSON_LONG_LONG_TYPE:
					bobCenRecord.append(mit->first, boRecord[mit->second]._numberLong());
					break;
				default:
					bobCenRecord.append(mit->first, boRecord[mit->second].toString(false));
				}
			}
			else{
				bobCenRecord.append(mit->first, "");
			}
		}
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMongodbModel", "ConvertBSONObj", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bobCenRecord.obj();
}

int CMongodbModel::GetIntFieldValue(BSONObj boRecord, string strFieldName, 
									int iExceptionValue)
{
	int iValue = iExceptionValue;
	if (boRecord.hasField(strFieldName))
	{		
		try 
		{
			iValue = boRecord.getIntField(strFieldName.c_str());
		}
		catch(exception& ex) {}
	}

	return iValue;
}

string CMongodbModel::GetStringFieldValue(BSONObj boRecord, string strFieldName, string strExceptionValue)
{
	string strValue = strExceptionValue;
	if (boRecord.hasField(strFieldName))
	{		
		try 
		{
			strValue = boRecord.getStringField(strFieldName.c_str());
		}
		catch(exception& ex) {}
	}

	return strValue;
}

bool CMongodbModel::GetArrayFieldValue(const BSONObj& boInfo, 
									   string strFieldName, 
									   std::vector<BSONElement>& vtValue)
{
	bool bResult = false;
	if (boInfo.hasField(strFieldName))
	{
		BSONElement beInfo = boInfo[strFieldName];		
		vtValue = beInfo.Array();	
		bResult = true;
	}	

	return bResult;
}

BSONObj CMongodbModel::RemoveFields(BSONObj *pRecord, StringArray &arrFieldName) {
	BSONObjBuilder b;
	BSONObjIterator i(*pRecord);
	while (i.more()) {
		BSONElement e = i.next();
		const char *fname = e.fieldName();
		StringArray::iterator it = find(arrFieldName.begin(), arrFieldName.end(), fname);
		if (it == arrFieldName.end())
			b.append(e);
	}
	return b.obj();
}