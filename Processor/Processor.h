#pragma once
#include "../Common/Common.h"
#include "../Model/MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CMongodbController;
class CMySQLController;
class CMongodbModel;

union Controller {
	CMongodbController* pMongodbController;
	CMySQLController* pMySQLController;
};

//typedef vector<CMongodbModel*> MongodbModelArray;
//typedef vector<CMongodbController*> MongodbControllerArray;

typedef vector<Controller > ControllerArray;
typedef map<string, ControllerArray > mapDBGroup2ControllerArray;
typedef vector<CMongodbModel*> MongodbModelArray;

class CProcessor
{
public:
	CProcessor(const string& strFileName);
	virtual ~CProcessor(void);
protected:
	// RegisterController for Mongodb
	void RegisterController(CMongodbController* pController, string strDBGroup = "");
	// RegisterMySQLController for MySQL
	void RegisterController(CMySQLController* pController, string strDBGroup = "");

	virtual bool Connect();
protected:
	// MongodbControllerArray m_arrMongodbController;
	mapDBGroup2ControllerArray m_mapDBGroup2ControllerArray;
};
