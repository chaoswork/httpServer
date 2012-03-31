#include    "error.h"

CW_BEGIN


Error::Error(string msg)
{
	this->msg=msg;
}
void Error::showError()
{
#ifdef CRIT_MSGBOX
	MessageBox(0,msg.c_str(),"Internal error",MB_OK);
#else
	fprintf(stderr,"\nInternal error: %s\n",msg.c_str());
#endif
}

CW_END


