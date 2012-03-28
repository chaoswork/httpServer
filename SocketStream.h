#ifndef  SOCKETSTREAM_H
#define  SOCKETSTREAM_H

#include    "package.h"
#include    "error.h"
#ifdef WIN32
#	include <windows.h>
#else
#	include <unistd.h>
#	include	<errno.h>
#endif

#include  <string>
CW_BEGIN


class SocketStream{
public:
	SocketStream(int sk):handle(sk){}
	~SocketStream(){}

	/* read and write without buffer */
	int readn(char* usrbuf,int n);
	int writen(char* usrbuf,int n);
	/* read and write with buffer */
	//int breadn
	//int bwriten
private:
	int handle;
	int uncnt;
	char buf[8196];
};

CW_END



#endif  /*SOCKETSTREAM_H*/
