#ifndef  HTTPSOCKET_H
#define  HTTPSOCKET_H

#include    "Socket.h"
#include    "error.h"
USING_CW

const int MAXLINE=512;

/* HttpSocket handle the Http web,
 * maybe there should be a TcpSocket between
 * HttpSocket and Socket. But for now,just 
 * inheritance Socket.*/
class HttpSocket:public Socket{
public:
	HttpSocket();
	void start(unsigned short port);
	void handleRequest(Socket& req);
};

#endif  /*HTTPSOCKET_H*/
