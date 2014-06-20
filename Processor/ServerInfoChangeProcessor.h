#pragma once
#include "CIInfoChangeProcessor.h"

class CServerInfoChangeProcessor :
	public CCIInfoChangeProcessor
{
public:
	CServerInfoChangeProcessor(const string& strCfgFile);
	~CServerInfoChangeProcessor(void);
	//auto_ptr<DBClientCursor> LoadDB();
};