#include  <iostream>
#include  <time.h>
#include	"Socket.h"
USING_CW


int main(int argc, char *argv[])
{
	try{	
		Socket serv(AF_INET,SOCK_STREAM);
		serv.bind(13);
		serv.listen(1024);
		for(;;)
		{
			Socket req;
			serv.accept(req);
			time_t ticks=time(NULL);
			SocketStream ss=req.getSocketStream();
			char buff[1024];
			snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
			ss.writen(buff,strlen(buff));
			req.close();
		}
	}catch(Error x)
	{
		x.showError();
	}
	return 0;
}
