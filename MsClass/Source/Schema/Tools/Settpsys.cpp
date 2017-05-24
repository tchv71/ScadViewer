#include <stdafx.h>
#include "schema.h"

EXPORT int SCHEMA::SetTypeSystem(BYTE Num)
{
	WORD i;
	static TYPE_SYSTEM Sys[] = {
	    {  1, 2, 1, 3 },
	    {  2, 3, 1, 3, 5 },
	    {  3, 3, 3, 4, 5 },
	    {  4, 3, 1, 2, 3 },
	    {  5, 6, 1, 2, 3, 4, 5, 6 },
	    {  8, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
	    {  9, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14, 15 },
	    { 10, 15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
	    { 11, 2, 3, 10 }
	    };
	for ( i=0; i<sizeof(Sys) / sizeof(TYPE_SYSTEM); i++ )
	   if ( Sys[i].Num == Num ) goto _10;
        memcpy(&TypeSystem,&Sys[4],Sys[4].QuantityStep+2);
        return 1;

_10:    if ( TypeSystem.Num != Num ) Modify = 1;
	memcpy(&TypeSystem,&Sys[i],Sys[i].QuantityStep+2);
	return 0;

}