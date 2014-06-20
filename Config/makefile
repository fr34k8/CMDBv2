CC=g++
ConfigFolder: ConfigReader.o ConfigFile.o md5.o
ConfigReader.o: ConfigReader.cpp ConfigReader.h
	$(CC) -c ConfigReader.cpp
ConfigFile.o: ConfigFile.cpp ConfigFile.h ConfigReader.o
	$(CC) -c ConfigFile.cpp
md5.o: md5.cpp md5.h
	$(CC) -c md5.cpp
clean:
	rm -rf *o ConfigFolder
