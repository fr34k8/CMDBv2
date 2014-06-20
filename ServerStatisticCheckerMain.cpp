#include "Processor/ServerCheckerProcessor.h"
#include "Common/Common.h"
#include "Common/DBCommon.h"
//------------------------------------
#include <ctime>
#include <string.h>
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

	if(CUtilities::CheckExistingProcess("cmdbServStat") != -1)
	{
		printf ("Process is existed !!\n");
		return 0;
	}
	//===============================FORK==================================//
	printf ("Create Server Statistic Process : %s !!\n", argv[0]);

	child_id = fork();
	if (child_id) {
		cout << "I'm parent of " << child_id << endl;
	}
	else {
			CServerCheckerProcessor *pServerCheckerProcessor = new CServerCheckerProcessor("Config.ini");
			pServerCheckerProcessor->ProceedCheckDataInfo(SERVER_STATISTIC);
			delete pServerCheckerProcessor;
	}
	
	return 0;
}
