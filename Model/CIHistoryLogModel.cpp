#include "CIHistoryLogModel.h"

CCIHistoryLogModel::CCIHistoryLogModel(void)
{
	m_pBobOldValues = new BSONObjBuilder();
	m_pBobNewValues = new BSONObjBuilder();
}

CCIHistoryLogModel::~CCIHistoryLogModel(void)
{
	if (NULL != m_pBobOldValues)
	{
		delete m_pBobOldValues;
	}

	if (NULL != m_pBobNewValues)
	{
		delete m_pBobNewValues;
	}
}

void CCIHistoryLogModel::AppendOldValues(BSONObj boOldValue)
{
	m_pBobOldValues->appendElements(boOldValue);
}

void CCIHistoryLogModel::AppendNewValues(BSONObj boNewValue)
{
	m_pBobNewValues->appendElements(boNewValue);
}

void CCIHistoryLogModel::Unset()
{
	m_strUsername = "";
	m_beObjectId = BSONElement();

	if (NULL != m_pBobOldValues)
	{
		delete m_pBobOldValues;
	}

	if (NULL != m_pBobNewValues)
	{
		delete m_pBobNewValues;
	}

	m_pBobOldValues = new BSONObjBuilder();
	m_pBobNewValues = new BSONObjBuilder();
	m_strObjectCode = "";
	m_iChangeType = NULL;
	m_lChangeDate = NULL;
}

BSONObj CCIHistoryLogModel::GetCIHistoryLog()
{
	BSONObj boLog = BSON("username"<<m_strUsername<<"change_type"<<m_iChangeType<<"ci_id"<<m_beObjectId<<"ci_code"<<m_strObjectCode
					<<"old_value"<<m_pBobOldValues->obj()<<"new_value"<<m_pBobNewValues->obj()<<"change_date"<<m_lChangeDate);
	return boLog;
}

