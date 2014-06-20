#include <iostream>
#include <string.h>
#include <dlfcn.h>
using namespace std;

int main() {
	
	char* pResult = NULL;
	char* pSerialNumber;

	string strLibName;
	string strApiName;
	string strErrorMsg = "";

	strLibName = "libSnSWSService-3.0.so";
	//strApiName = "GetServerStatistic";
	strApiName = "GetHardwareInfoBySerialNumber";
	pSerialNumber = (char*)"SGH940XNAF";

    cout << "C++ dlopen demo\n\n";

    // open the library
    cout << "Opening hello.so...\n";
    void* handle = dlopen((const char*)strLibName.c_str(), RTLD_LAZY);
    
    if (!handle) {
        cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }
    
    // load the symbol
    cout << "Loading symbol hello...\n";
    typedef char* (*CollectorInfo)(string&, char*);

    // reset errors
    dlerror();
    CollectorInfo apiCollectorInfo = (CollectorInfo) dlsym(handle, (const char*)strApiName.c_str());
    
	const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol 'hello': " << dlsym_error <<
            '\n';
        dlclose(handle);
        return 1;
    }
	
	pResult = apiCollectorInfo(strErrorMsg, pSerialNumber);
	if (strErrorMsg != "")
		cout << "Error:" << strErrorMsg << endl;
	cout << pResult << endl;
	if (NULL != pResult)
		delete pResult;

    // use it to do the calculation
    cout << "Calling hello...\n";    
    // close the library
    cout << "Closing library...\n";
    dlclose(handle);
	
	return 0;
}