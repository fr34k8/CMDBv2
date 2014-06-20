#include "Processor/UpdateServerUSpaceProcessor.h"
#include "Processor/UpdateChassisUSpaceProcessor.h"
#include "Processor/UpdateAggregationSwitchUSpaceProcessor.h"
#include "Processor/UpdateAccessSwitchUSpaceProcessor.h"
#include "Processor/UpdateCoreSwitchUSpaceProcessor.h"
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

	if (CUtilities::CheckExistingProcess("cmdbUpdateUSpace") != -1)
	{
		printf("Process is existed !!\n");
		return 0;
	}
	//===============================FORK==================================//
	printf("Starting Update U Space Process : %s !!\n", argv[0]);

	child_id = fork();
	if (child_id) {
		cout << "I'm parent of " << child_id << endl;
	}
	else {
		CUpdateServerUSpaceProcessor *pUpdateServerUSpaceProcessor = new CUpdateServerUSpaceProcessor("Config.ini");
		CUpdateChassisUSpaceProcessor *pUpdateChassisUSpaceProcessor = new CUpdateChassisUSpaceProcessor("Config.ini");
		CUpdateAggregationSwitchUSpaceProcessor *pUpdateAggregationSwitchUSpaceProcessor = new CUpdateAggregationSwitchUSpaceProcessor("Config.ini");
		CUpdateAccessSwitchUSpaceProcessor *pUpdateAccessSwitchUSpaceProcessor = new CUpdateAccessSwitchUSpaceProcessor("Config.ini");
		CUpdateCoreSwitchUSpaceProcessor *pUpdateCoreSwitchUSpaceProcessor = new CUpdateCoreSwitchUSpaceProcessor("Config.ini");
		pUpdateServerUSpaceProcessor->Proceed();
		pUpdateChassisUSpaceProcessor->Proceed();
		pUpdateAggregationSwitchUSpaceProcessor->Proceed();
		pUpdateAccessSwitchUSpaceProcessor->Proceed();
		pUpdateCoreSwitchUSpaceProcessor->Proceed();
		delete pUpdateServerUSpaceProcessor;
		delete pUpdateChassisUSpaceProcessor;
		delete pUpdateAggregationSwitchUSpaceProcessor;
		delete pUpdateAccessSwitchUSpaceProcessor;
		delete pUpdateCoreSwitchUSpaceProcessor;
	}

	return 0;
}
