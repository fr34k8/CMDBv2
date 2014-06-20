CC=g++
NotificationFolder: NotificationAPI.o DCProductNotificationAPI.o \
		DCServerNotificationAPI.o MISProductNotificationAPI.o SnSServerNotificationAPI.o
NotificationAPI.o: NotificationAPI.cpp NotificationAPI.h
	$(CC) -c NotificationAPI.cpp
DCProductNotificationAPI.o: DCProductNotificationAPI.cpp DCProductNotificationAPI.h
	$(CC) -c DCProductNotificationAPI.cpp
DCServerNotificationAPI.o: DCServerNotificationAPI.cpp DCServerNotificationAPI.h
	$(CC) -c DCServerNotificationAPI.cpp
MISProductNotificationAPI.o: MISProductNotificationAPI.cpp MISProductNotificationAPI.h
	$(CC) -c MISProductNotificationAPI.cpp
SnSServerNotificationAPI.o: SnSServerNotificationAPI.cpp SnSServerNotificationAPI.h
	$(CC) -c SnSServerNotificationAPI.cpp
clean:
	rm -rf *o NotificationFolder
