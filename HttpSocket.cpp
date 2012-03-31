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
	{
		/* here may exist a close error,the server
		 * do not close the cli.m_socket!,so I change
		 * the Socket::close() function.Not perfect yet*/
		accept(cli);
		pid_t childpid;
		if((childpid=fork())==0)
		{
			close();
			handleRequest(cli);
			cli.close();
			exit(0);
		}
		cli.close();
	}
#else
	//throw Error("Win32 HttpSocket start under construction...");
	Socket cli;
	for(;;)
	{
		accept(cli);
		handleRequest(cli);
		cli.close();
	}
#endif

}

void HttpSocket::handleRequest(Socket& req)
{
	char buf[MAXLINE];//,method[MAXLINE],uri[MAXLINE],version[MAXLINE];

	SocketStream ss=req.getSocketStream();
	ss.readlineb(buf,MAXLINE);
	fputs(buf,stdout);
	char ret[MAXLINE];
	char body[MAXLINE];
	//send the response
	
	sprintf(body,"<html>\
			<title>test Web Server</title>\
			<body>\
				Hello World!Just a Web Server test:)\
			</body>\
			</html>\r\n");
	sprintf(ret,"HTTP/1.0 200 OK\r\n\
			Server: test Web Server\r\n\
			Content-type: text/html\r\n\
			Content-length: %d\r\n\r\n",strlen(body));
	ss.writen(ret,strlen(ret));
	ss.writen(body,strlen(body));
}
