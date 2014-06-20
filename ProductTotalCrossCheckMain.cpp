#include "Processor/ProductTotalCrossCheckProcessor.h"
//#include "Common/Common.h"
//#include "Common/DBCommon.h"
//------------------------------------
#include <unistd.h>
//------------------------------------

int main(int argc, char* argv[])
{
	int child_id;
	string strLine;

	if (CUtilities::CheckExistingProcess("ProductTotalCrossCheckMain") != -1)
	{
		printf("Process is existed !!\n");
		return 0;
	}
	//===============================FORK==================================//
	printf("Create Product Total Cross Check Process : %s !!\n", argv[0]);

	child_id = fork();
	if (child_id) {
		cout << "I'm parent of " << child_id << endl;
	}
	else {
		CProductTotalCrossCheckProcessor *pProductTotalCrossCheckProcessor = new CProductTotalCrossCheckProcessor("Config.ini");
		pProductTotalCrossCheckProcessor->ComparationProceed();
		delete pProductTotalCrossCheckProcessor;
	}

	return 0;
}
