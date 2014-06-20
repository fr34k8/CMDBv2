CC=g++
DataCheckerFolder: BaseChecker.o ServerChecker.o HardwareChecker.o
BaseChecker.o: BaseChecker.cpp BaseChecker.h
	$(CC) -c BaseChecker.cpp
ServerChecker.o: ServerChecker.cpp ServerChecker.h
	$(CC) -c ServerChecker.cpp
HardwareChecker.o: HardwareChecker.cpp HardwareChecker.h
	$(CC) -c HardwareChecker.cpp
clean:
	rm -rf *o DataCheckerFolder
