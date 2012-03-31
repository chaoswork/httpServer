#include    "Socket.h"


CW_BEGIN

// windows socket init

#ifdef WIN32
static class sock_init{
public:
	sock_init();
	~sock_init();
}_init;

sock_init::sock_init()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2,0);

	err=WSAStartup(wVersionRequested,&wsaData);
	
	if(err) throw Error("Winsock init error");

}

sock_init::~sock_init()
{
	WSACleanup();
}
#endif


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
				(optval_t)&optval,sizeof(int))<0)
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
//Socket Socket::accept(struct sockaddr_in* cliAddr)
void Socket::accept(Socket& SK,struct sockaddr_in* cliAddr)
{
	SOCKET sk=-1;
	if(cliAddr==0)//don't care the request socket address
	{
		struct sockaddr_in cliaddr;
		memset(&cliaddr,0,sizeof(cliaddr));
		socklen_t socklen=sizeof(cliaddr);
		if((sk=::accept(m_socket,(struct sockaddr*)&cliaddr,&socklen))<0)
			throw Error("socket accept error");
	}
	else
	{
		socklen_t socklen=sizeof(*cliAddr);
		if((sk=::accept(m_socket,(struct sockaddr*)cliAddr,&socklen))<0)
			throw Error("socket accept error");
	}
	SK.m_socket=sk;

}
/* close socket */
void Socket::close()
{
	//if(socketClosed) return;
#ifdef WIN32
	if(closesocket(m_socket));// throw Error("close socket error");
	else socketClosed=true;
#else
	if(::close(m_socket)<0); //throw Error("close socket error");
	else socketClosed=true;
#endif
}

SocketStream Socket::getSocketStream()
{
	return SocketStream(m_socket);
}
CW_END
