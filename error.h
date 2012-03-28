#ifndef  ERROR_H
#define  ERROR_H

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


CW_END


#endif  /*ERROR_H*/
