
CC = cl
CFLAGS = -c /D "WIN32" 

all: server.exe
server.exe: server.obj HttpSocket.obj Socket.obj error.obj SocketStream.obj
	link server.obj HttpSocket.obj Socket.obj error.obj SocketStream.obj   "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib

server.obj: server.cpp HttpSocket.h
	$(CC) $(CFLAGS) server.cpp 
Socket.obj: Socket.cpp Socket.h package.h SocketStream.h error.h
	$(CC) $(CFLAGS) Socket.cpp
HttpSocket.obj: HttpSocket.h HttpSocket.cpp 
	$(CC) $(CFLAGS) HttpSocket.cpp
error.obj: error.cpp error.h
	$(CC) $(CFLAGS) error.cpp
SocketStream.obj: SocketStream.cpp SocketStream.h
	$(CC) $(CFLAGS) SocketStream.cpp
clean:
	del *.obj
