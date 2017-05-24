#include <stdafx.h>
#include <classwin.h>

EXPORT void  CrashMessage( void OutMessage(LPCSTR), int NumError ... );

EXPORT int MathError( _exception *e )
{
	char *mess;

	switch(e->type)
	{
		case DOMAIN:
		mess = "DOMAIN";
         break;
		case SING:
		mess = "SIGN";
         break;
		case OVERFLOW:
		mess = "OVERFLOW";
         break;
		default:
		return(1);
	}
   CrashMessage(52,mess,e->name,e->arg1,e->arg2);
   return 0;

}