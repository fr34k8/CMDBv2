#pragma once
#include "../Common/Common.h"

class CCollectorModel;
typedef char* (*CollectorInfo)(string& strErrorMsg);
typedef char* (*HardwareInfo)(string& strErrorMsg, char* pSerialNumber);

class CBaseChecker
{
public:
	CBaseChecker(void);
	~CBaseChecker(void);

	char* CallSnSService(CCollectorModel* pData);
	inline char* GetSerialNumber() { return m_pSerialNumber; }
	inline void SetSerialNumber(char* pSerialNumber) { m_pSerialNumber = pSerialNumber; }

protected:
	char* m_pSerialNumber;
};
