#ifndef  SOCKET_HPP
#define  SOCKET_HPP

#ifndef	PACKAGE_H
#include    "package.h"
#endif

#ifndef ERROR_H
#include    "error.hpp"
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
#else //WIN32
#include  <winsock.h>
#endif

CW_BEGIN

using std::string;
/* Socket is class to handle socket,can't copy publicly.
 * With the action connect,close,and server action bind,
 * listen and accept.
 * I tried to make it Exception safety and thread safe and
 * cross linux and windows platform.*/
class Socket{
public:
	//Socket(SOCKET sk=-1);
	Socket(int af,int type,int protocol=0);
	~Socket();
	void connect(const string& ipAddr,unsigned short port);
	/* bind,listen and accept should used for server*/
	void bind(unsigned short port);
	void listen(int backlog);
	Socket accept(struct sockaddr_in* cliAddr=0);
	void close();
private:
	void create(int af,int type,int protocol=0);
	/* accept return a Socket Object,so we make the copy constructor
	 * as private,and also disallow the operator= used public*/
	Socket(const Socket& SK){m_socket=SK.m_socket;}
	Socket& operator=(const Socket&);
	explicit Socket(SOCKET sk=-1);

	SOCKET m_socket;
	bool socketClosed;
};
/* create an unconnected socket,or reference to sk */
Socket::Socket(SOCKET sk)
{
	m_socket=sk;
	socketClosed=false;
}
/* Socket constructor,create a new socket */
Socket::Socket(int af,int type,int protocol)
{
	create(af,type,protocol);
}
Socket::~Socket()
{
	/* close the socket if it was not closed yet */
	if(!socketClosed) close();
}
/* create a socket */
void Socket::create(int af,int type,int protocol)
{
	m_socket=socket(af,type,protocol);
	if(m_socket<0)//socket create error
	{
		socketClosed=true;
		throw Error("Socket Create Error!");
	}
	else socketClosed=false;//make the socket mark as unclosed

}
/* connect to ipAddr:port */
void Socket::connect(const string& ipAddr,unsigned short port)
{
	struct sockaddr_in servAddr;
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(port);
	if(inet_pton(AF_INET,ipAddr.c_str(),&servAddr.sin_addr)<=0)
		throw Error("inet_pton error for "+ipAddr);
	if(::connect(m_socket,(struct sockaddr*)&servAddr,sizeof(servAddr))<0)
		throw Error("connect error");
}
/* bind to a port,server action */
void Socket::bind(unsigned short port)
{
	struct sockaddr_in servAddr;
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=INADDR_ANY;
	servAddr.sin_port=htons(port);

	/* eliminates "Addr already in use" error from bind */
	int optval=1;
	if(setsockopt(m_socket,SOL_SOCKET,SO_REUSEADDR,
				(const void*)&optval,sizeof(int))<0)
		throw Error("setsockopt error");
	if(::bind(m_socket,(struct sockaddr*)&servAddr,sizeof(servAddr))<0)
		throw Error("bind error,usually permission denied");
}
/* make it a listening socket ready to accept connection requests */
void Socket::listen(int backlog)
{
	if(::listen(m_socket,backlog)<0)
		throw Error("socket listen error");
}
/* accept a connection request */
Socket Socket::accept(struct sockaddr_in* cliAddr)
{
	SOCKET sk=-1;
	if(cliAddr==0)//don't care the request socket address
	{
		struct sockaddr_in cliaddr;
		memset(&cliaddr,0,sizeof(cliaddr));
		unsigned int socklen=sizeof(cliaddr);
		if((sk=::accept(m_socket,(struct sockaddr*)&cliaddr,&socklen))<0)
			throw Error("socket accept error");
	}
	else
	{
		unsigned int socklen=sizeof(*cliAddr);
		if((sk=::accept(m_socket,(struct sockaddr*)cliAddr,&socklen))<0)
			throw Error("socket accept error");
	}
	return Socket(sk);

}
/* close socket */
void Socket::close()
{
	if(::close(m_socket)<0) throw Error("close socket error");
	else socketClosed=true;
}
CW_END
#endif  /*SOCKET_HPP*/
