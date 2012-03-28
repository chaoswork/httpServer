#include    "SocketStream.h"
CW_BEGIN



int SocketStream::readn(char* usrbuf,int n)
{
	if(handle<0) return -1;
	int nleft=n;
	char* bufp=usrbuf;
#ifdef WIN32
	unsigned long nread;
	if(!ReadFile(HANDLE(handle),usrbuf,n,&nread,0))
#else
	int nread;
	while(nleft>0)
	{
		if((nread=::read(handle,bufp,nleft))<0)
		{
			/* read again*/
			if(errno==EINTR) nread=0;
			else throw Error("read error");
		}
		else if(nread==0) break;//EOF
		nleft-=nread;
		bufp+=nread;
	}
#endif
	return n-nleft;
}
int SocketStream::writen(char* usrbuf,int n)
{
	if(handle<0) return -1;
	int nleft=n;
	char *bufp=usrbuf;
#ifdef WIN32
	unsigned long nwritten;
	if(!WriteFile(HANDLE(handle),usrbuf,n,&nwritten,0))
	{
		ret=-1;
		throw Error("Write error");
	}
#else
	int nwritten;
	while(nleft>0)
	{
		if((nwritten=::write(handle,bufp,nleft))<=0)
		{
			if(errno==EINTR) nwritten=0;
			else throw Error("Write error");
		}
		nleft-=nwritten;
		bufp+=nwritten;
	}
#endif
	return n;
}

CW_END



