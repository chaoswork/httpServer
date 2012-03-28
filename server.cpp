#include    "HttpSocket.h"

int main(int argc, char *argv[])
{
	try{
		HttpSocket server;
		server.start(80);
	}catch(Error x)
	{
		x.showError();
	}
	return 0;
}
