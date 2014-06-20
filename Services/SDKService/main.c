#include <sstream>
#include <time.h>
#include <map>
#include <iterator> // for ostream_iterator
#include "../../Config/md5.h"
#include <dlfcn.h>

using namespace std;

string ConvertIntToString(int number)
{
	stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

int main() {
	
	char* pResult = NULL;
	char* pClientId;
	char* pChecksum;
	char* pOperation;
	char* pRequestData = NULL;

	unsigned int iTime;

	string strLibName;
	string strApiName;
	string strErrorMsg = "";

	strLibName = "libSKDWSService-1.0.so";
	strApiName = "CallSDKService";
	
    cout << "C++ dlopen demo\n\n";

   //=========================================
	//Parameter Connect Web Service
	//=========================================
	// Get request time
	time_t ltime;
	time(&ltime); 
	iTime = (unsigned int)ltime;
	
	//*********************************************************
	// Password && CheckSum
	//*********************************************************
	string strPassword = "sdks$rv!c$!";
	string strRequestTime = ConvertIntToString(iTime);
	string strCheckSum = strRequestTime + strPassword;
	strCheckSum = md5(strCheckSum);

	pClientId = (char*)"sdk";
	pChecksum = (char*)strCheckSum.c_str();
	pOperation = (char*)"GetODAHostInfoList"; 
	//==========================================
    cout << "C++ dlopen demo\n\n";

    // open the library
    cout << "Opening libSKDWSService-1.0.so...\n";
    void* handle = dlopen((const char*)strLibName.c_str(), RTLD_LAZY);
    
    if (!handle) {
        cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }
    
    // load the symbol
    cout << "Loading symbol CallSDKService...\n";
    typedef char* (*CollectorInfo)(string&, char*,char*,char*,unsigned int,char*);
	cout << "Loaded symbol okie" << endl;
    // reset errors
    dlerror();
    CollectorInfo apiCollectorInfoInfo = (CollectorInfo)dlsym(handle, (const char*)strApiName.c_str());
	cout << "Loaded api okie" << endl;
	const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol 'CallSDKService': " << dlsym_error <<
            '\n';
        dlclose(handle);
        return 1;
    }
	pRequestData = (char*)"{}";
	cout << "Calling GetODAHostInfoList...\n"; 
	pResult = apiCollectorInfoInfo(strErrorMsg, pClientId, pChecksum, pOperation, iTime, pRequestData);
	
	if(strErrorMsg != "")
		cout << "Error:" << strErrorMsg << endl;

	if (NULL != pResult)
	{
		cout << "Response:" << pResult << endl;
		delete pResult;
	}
    // use it to do the calculation
   
    // close the library
    cout << "Closing library...\n";
    dlclose(handle);
	
	return 0;
}