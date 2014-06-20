CC=g++
SynchronizationFolder: SynchronizationData.o MISDivisionSynchronization.o  \
MISDepartmentSynchronization.o MISUserSynchronization.o
SynchronizationData.o: SynchronizationData.cpp SynchronizationData.h
	$(CC) -c SynchronizationData.cpp
MISDivisionSynchronization.o: MISDivisionSynchronization.cpp MISDivisionSynchronization.h
	$(CC) -c MISDivisionSynchronization.cpp
MISDepartmentSynchronization.o: MISDepartmentSynchronization.cpp MISDepartmentSynchronization.h
	$(CC) -c MISDepartmentSynchronization.cpp
MISUserSynchronization.o: MISUserSynchronization.cpp MISUserSynchronization.h
	$(CC) -c MISUserSynchronization.cpp
clean:
	rm -rf *o SynchronizationFolder
