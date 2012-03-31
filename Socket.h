#ifndef  SOCKET_H
#define  SOCKET_H

#ifndef	PACKAGE_H
#include    "package.h"
#endif


#include  <string>
#include  <string.h>


#ifdef linux
#include  <sys/socket.h>
#include  <netinet/in.h>
#include  <arpa/inet.h>
#include  <netdb.h>
#include  <sys/types.h>
#include  <unistd.h>
typedef	int SOCKET;
typedef void* optval_t;
#else //WIN32
#include  <winsock2.h>
#include  <Ws2tcpip.h>
#pragma comment(lib,"WS2_32.lib")
//typedef unsigned int socklen_t;
typedef const char* optval_t;
#endif


#ifndef ERROR_H
#include    "error.h"
#endif
#include    "SocketStream.h"


CW_BEGIN





using std::string;
/* Socket is class to handle socket,can't copy publicly.
 * With the action connect,close,and server action bind,
 * listen and accept.
 * I tried to make it Exception safety and thread safe and
 * cross linux and windows platform.*/
class Socket{
public:
	explicit Socket(SOCKET sk=-1);
	Socket(int af,int type,int protocol=0);
	virtual	~Socket();
	void connect(const string& ipAddr,unsigned short port);
	/* bind,listen and accept should used for server*/
	void bind(unsigned short port);
	void listen(int backlog);
	//Socket accept(struct sockaddr_in* cliAddr=0);
	void accept(Socket& SK,struct sockaddr_in* cliAddr=0);
	void close();

	/* Socket i/o stream */
	SocketStream getSocketStream();
protected:
	void create(int af,int type,int protocol=0);
	/* accept return a Socket Object,so we make the copy constructor
	 * as private,and also disallow the operator= used public*/
	Socket(const Socket& SK){m_socket=SK.m_socket;}
	Socket& operator=(const Socket&);
private:
	//SOCKET m_socket;
	int m_socket;
	bool socketClosed;
};
CW_END
#endif  /*SOCKET_H*/
