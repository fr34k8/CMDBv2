#include "Processor/AggregationSwitchInfoMappingProcessor.h"
#include "Processor/AccessSwitchInfoMappingProcessor.h"
#include "Processor/CoreSwitchInfoMappingProcessor.h"
#include "Processor/ChassisInfoMappingProcessor.h"
#include "Processor/ServerInfoMappingProcessor.h"
#include "Common/Common.h"
#include "Common/DBCommon.h"
//------------------------------------
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>

//------------------------------------
extern "C"
{
#include <pthread.h>
}
#include <iostream>
using namespace std;
#define ListConfig "ConfigList"

int main(int argc, char* argv[])
{
	int child_id;
	string strLine;

	if (CUtilities::CheckExistingProcess("cmdbMapCIModel") != -1)
	{
		printf("Process is existed !!\n");
		return 0;
	}
	//===============================FORK==================================//
	printf("Starting Model Mapping Process : %s !!\n", argv[0]);

	child_id = fork();
	if (child_id) {
		cout << "I'm parent of " << child_id << endl;
	}
	else {
		CAggregationSwitchInfoMappingProcessor *pAggregationSwitchInfoMappingProcessor = new CAggregationSwitchInfoMappingProcessor("Config.ini");
		CAccessSwitchInfoMappingProcessor *pAccessSwitchInfoMappingProcessor = new CAccessSwitchInfoMappingProcessor("Config.ini");
		CCoreSwitchInfoMappingProcessor *pCoreSwitchInfoMappingProcessor = new CCoreSwitchInfoMappingProcessor("Config.ini");
		CChassisInfoMappingProcessor *pChassisInfoMappingProcessor = new CChassisInfoMappingProcessor("Config.ini");
		CServerInfoMappingProcessor *pServerInfoMappingProcessor = new CServerInfoMappingProcessor("Config.ini");
		pAggregationSwitchInfoMappingProcessor->Proceed();
		pAccessSwitchInfoMappingProcessor->Proceed();
		pCoreSwitchInfoMappingProcessor->Proceed();
		pChassisInfoMappingProcessor->Proceed();
		pServerInfoMappingProcessor->Proceed();
		delete pAggregationSwitchInfoMappingProcessor;
		delete pAccessSwitchInfoMappingProcessor;
		delete pCoreSwitchInfoMappingProcessor;
		delete pChassisInfoMappingProcessor;
		delete pServerInfoMappingProcessor;
	}

	return 0;
}
