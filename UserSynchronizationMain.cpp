#include "Processor/UserInfoSynchronizationProcessor.h"
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
	if( argc != 2)   
    { 
     cout <<" Usage: sync_process collector_name" << endl;
     return -1;
    }

	int child_id;
	string strCollectionName = "";
	strCollectionName = argv[1];

	if(CUtilities::CheckExistingProcess("cmdbUserSync") != -1)
	{
		printf ("Process is existed !!\n");
		return 0;
	}
	//===============================FORK==================================//
	printf ("Create Product Notification Process : %s !!\n", argv[0]);

	child_id = fork();
	if (child_id) {
		cout << "I'm parent of " << child_id << endl;
	}
	else {
			CUserInfoSynchronizationProcessor *pUserSyncProcessor = new CUserInfoSynchronizationProcessor("Config.ini");
			pUserSyncProcessor->ProceedSynchronizeInfo(strCollectionName);
			delete pUserSyncProcessor;
	}
	
	return 0;
}
