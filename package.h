#ifndef  PACKAGE_H
#define  PACKAGE_H

//
// conditional namespace declarations
//
#define CHAOSWORK_NAMESPACE cw

#ifdef CHAOSWORK_NAMESPACE
#	define CW_BEGIN		namespace cw{
#	define CW_END		}
#	define USING_CW		using namespace cw;
#else
#	define CHAOSWORK_NAMESPACE
#	define CW_BEGIN
#	define CW_END
#	define USING_CW
#endif 	/* CHSOAWORK_NAMESPACE  */

CW_BEGIN
class Uncopyable 
{
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator= (const Uncopyable&);
public:
	Uncopyable() {}
	~Uncopyable() {}
};
CW_END


#endif  /*PACKAGE_H*/
