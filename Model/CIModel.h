#pragma once
#include "MongodbModel.h"

class CCIModel: public CMongodbModel
{
public:
	CCIModel(void);
	virtual ~CCIModel(void);

	inline int GetCIType() { return m_iCIType; }
	void SetCIType(int iCIType) { m_iCIType = iCIType; }
protected:
	int m_iCIType;
};