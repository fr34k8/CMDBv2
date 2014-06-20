#include "CIInfoIndexModel.h"

CCIInfoIndexModel::CCIInfoIndexModel(void)
{
}

CCIInfoIndexModel::~CCIInfoIndexModel(void)
{
}

Query CCIInfoIndexModel::IsExistedIndexQuery(string strValue)
{
	BSONObj boCondition = BSON("key"<<strValue<<"info"<<BSON("id"<<OID(m_strCIID)<<"field"<<m_strFieldName));
	Query queryCondition = Query(boCondition);
	return queryCondition;
}
Query CCIInfoIndexModel::GetAddIndexQuery()
{
	Query queryCondition = QUERY("key"<<m_strNewValue);
	return queryCondition;
}
Query CCIInfoIndexModel::GetDeleteIndexQuery()
{
	Query queryCondition = QUERY("key"<<m_strOldValue);
	return queryCondition;
}
BSONObj CCIInfoIndexModel::GetAddIndexRecord()
{
	
	BSONObj boInfo = BSON("id"<<OID(m_strCIID)<<"field"<<m_strFieldName);
	BSONObj boRecord = BSON("$push"<<BSON("info"<<boInfo));
	return boRecord;
}
BSONObj CCIInfoIndexModel::GetDeleteIndexRecord()
{
	BSONObj boRecord = BSON("$pull"<<BSON("info"<<BSON("id"<<OID(m_strCIID)<<"field"<<m_strFieldName)));
	return boRecord;
}
BSONObj CCIInfoIndexModel::GetCIInfoChange()
{
	BSONObj boInfo = BSON("id"<<OID(m_strCIID)<<"field"<<m_strFieldName<<"old"<<m_strOldValue<<"new"<<m_strNewValue<<"clock"<<m_lClock);
	return boInfo;
}

CCIInfoIndexModel* CCIInfoIndexModel::Clone()
{
	CCIInfoIndexModel* pCIInfoIndexModel = new CCIInfoIndexModel();
	pCIInfoIndexModel->m_lClock = m_lClock;
	pCIInfoIndexModel->m_strFieldName = m_strFieldName;
	pCIInfoIndexModel->m_strNewValue = m_strNewValue;
	pCIInfoIndexModel->m_strObjectID = m_strObjectID;
	pCIInfoIndexModel->m_strOldValue = m_strOldValue;
	pCIInfoIndexModel->m_objBSON = m_objBSON;

	return pCIInfoIndexModel;
}

void CCIInfoIndexModel::Load(const BSONObj& boRecord)
{
	m_strObjectID  = boRecord.hasField("_id") ? CUtilities::GetMongoObjId(boRecord["_id"].toString(false)) : "";
	m_strCIID = boRecord.hasField("id") ? CUtilities::GetMongoObjId(boRecord["id"].toString(false)) : "";
	m_strOldValue = boRecord.hasField("old") ? boRecord.getStringField("old") : "";
	m_strNewValue = boRecord.hasField("new") ? boRecord.getStringField("new") : "";
	m_strFieldName = boRecord.hasField("field") ? boRecord.getStringField("field") : "";
	m_lClock = boRecord.hasField("clock") ? boRecord["clock"]._numberLong() : 0;
}