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
int SocketStream::readb(char* usrbuf,int n)
{
	if(handle<0) return -1;

	int cnt;
	while(uncnt<=0)// refill if buf is empty
	{
#ifdef WIN32
	unsigned long nwrittrn;
	if(!WriteFile(HANDLE(handle),ssbuf,sizeof(ssbuf),&nwritten,0))
		return -1;
	uncnt=(int)nwritten;//this maybe a bug!
#else
		uncnt=::read(handle,ssbuf,sizeof(ssbuf));
#endif
		if(uncnt<0)
		{
			if(errno!=EINTR) return -1;
		}
		else if(uncnt==0) //EOF
			return 0;
		else
			ssbufp=ssbuf;
	}
	cnt=uncnt<n?uncnt:n;
	memcpy(usrbuf,ssbufp,cnt);
	ssbufp+=cnt;
	uncnt-=cnt;
	return cnt;

}
int SocketStream::readlineb(char* usrbuf,int maxlen)
{
	int n,rc;
	char c,*bufp=usrbuf;
	for(n=1;n<maxlen;++n)
	{
		if((rc=readb(&c,1))==1){
			*bufp++=c;
			if(c=='\n') break;
		}
		else if(rc==0)
		{
			if(n==1) return 0;//EOF,no data read
			else break;//EOF,some data was read
		}
		else return -1;
	}
	*bufp=0;
	return n;
}
CW_END



