#include "Processor/UpdateAccessSwitchUSpaceProcessor.h"
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

	if (CUtilities::CheckExistingProcess("cmdbUSpaceAccessSwitch") != -1)
	{
		printf("Process is existed !!\n");
		return 0;
	}
	//===============================FORK==================================//
	printf("Starting Update AccessSwitch U Space Process : %s !!\n", argv[0]);

	child_id = fork();
	if (child_id) {
		cout << "I'm parent of " << child_id << endl;
	}
	else {
		CUpdateAccessSwitchUSpaceProcessor *pUpdateAccessSwitchUSpaceProcessor = new CUpdateAccessSwitchUSpaceProcessor("Config.ini");
		pUpdateAccessSwitchUSpaceProcessor->Proceed();
		delete pUpdateAccessSwitchUSpaceProcessor;
	}

	return 0;
}
