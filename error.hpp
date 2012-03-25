#ifndef  ERROR_HPP
#define  ERROR_HPP

#ifndef PACKAGE_H
#include    "package.h"
#endif

#include  <string>
#include  <stdlib.h>
#include  <stdio.h>


#if defined(WIN32) && !defined(NO_CRIT_MSGBOX)
#include  <windows.h>
#define	CRIT_MSGBOX
#endif


CW_BEGIN

using std::string;
class Error{
public:
	Error(string msg);
	void showError();

private:
	string msg;
};

Error::Error(string msg)
{
	this->msg=msg;
}
void Error::showError()
{
#ifdef CRIT_MSGBOX
	MessageBox(0,msg,"Internal error",MB_OK);
#else
	fprintf(stderr,"\nInternal error: %s\n",msg.c_str());
#endif
}

CW_END


#endif  /*ERROR_HPP*/
