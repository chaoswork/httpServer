#ifndef  SOCKETSTREAM_H
#define  SOCKETSTREAM_H

#include    "package.h"
#ifdef WIN32
#	include <windows.h>
#else
#	include <unistd.h>
#	include	<errno.h>
#endif

#include    "error.h"
#include  <string>
#include  <string.h>
CW_BEGIN

const int SSMAXLEN=8196;
class SocketStream{
public:
	SocketStream(int sk):handle(sk)
	{
		uncnt=0;
		ssbufp=ssbuf;
	}
	~SocketStream(){}

	/* read and write without buffer */
	int readn(char* usrbuf,int n);
	int writen(char* usrbuf,int n);
	/* read with buffer */
	int readb(char* usrbuf,int n);
	int readlineb(char* usrbuf,int maxlen);
private:
	int handle;
	int uncnt;//unread bytes
	char* ssbufp;
	char ssbuf[SSMAXLEN];
};

CW_END



#endif  /*SOCKETSTREAM_H*/
