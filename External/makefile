CC=g++
ExternalFolder: BaseExternal.o SDKService.o
BaseExternal.o: BaseExternal.cpp BaseExternal.h
	$(CC) -c BaseExternal.cpp
SDKService.o: SDKService.cpp SDKService.h
	$(CC) -c SDKService.cpp
clean:
	rm -rf *o ExternalFolder
