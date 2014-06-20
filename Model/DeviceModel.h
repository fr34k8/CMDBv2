#pragma once
#include "CIModel.h"

#define FIELD_U	"u"
#define SAVE_RACK_MAP 0

class CDeviceModel :
	public CCIModel
{
public:
	CDeviceModel(void);
	virtual ~CDeviceModel(void);

	inline int GetU() { return m_iU; }
	inline int GetToU() { return m_nToU; }
	inline int GetSpace() { return m_iSpace; }
	inline BSONObj GetDevice() { return m_boDevice; }

	void SetU(int iU) { m_iU = iU; }
	void SetSpace(int iSpace) { m_iSpace = iSpace; }
	void SetDevice(BSONObj boDevice) { m_boDevice = boDevice.copy(); }
	virtual BSONObj GetModelMappingRecord(BSONObj boRecord);
	virtual BSONObj GetModelMappingCondition(BSONObj boRecord);
	virtual void Load(const BSONObj& boRecord);
protected:
	virtual void BuildBSONObj(BSONObjBuilder& boBuilder, int iFormat = 0);
protected:
	int m_iU;
	int m_iSpace; 
	int m_nToU;
	BSONObj m_boDevice;
};
