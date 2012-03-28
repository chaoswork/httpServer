#include    "HttpSocket.h"

USING_CW

HttpSocket::HttpSocket()
{
	create(AF_INET,SOCK_STREAM);
}
void HttpSocket::start(unsigned short port)
{
	bind(port);
	listen(1024);
#ifdef linux
	Socket cli;
	for(;;)
	{	accept(cli);
		pid_t childpid;
		if((childpid=fork())==0)
		{
			handleRequest(cli);
			close();
		}
	}
	close();
#else
	throw Error("Win32 HttpSocket start under construction...");
#endif

}

void HttpSocket::handleRequest(const Socket& req)
{
	char buf[MAXLINE],method[MAXLINE],uri[MAXLINE],version[MAXLINE];

	SocketStream ss=getSocketStream();
	ss.readn(buf,MAXLINE);
	fputs(buf,stdout);
}
