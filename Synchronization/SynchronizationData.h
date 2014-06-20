#pragma once
#include "../Common/Common.h"

class CCollectorModel;
typedef char* (*CollectorInfoChange)(char* pField);

class CSynchronizationData
{
public:
	CSynchronizationData(void);
	~CSynchronizationData(void);

	bool Synchronize(char *pUrlParameter, CCollectorModel* pData, char **_pResult);
};
