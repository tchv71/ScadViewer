#include <stdafx.h>
#include <defclass.h>

/********************************************************************/
/* The function INDEX returns the minimal position in the string s1 */
/* from which begins the text coinsiding with the string s2. If the */
/* substring s2 not found the function returns  (-1);               */
/*------------------------------------------------------------------*/
/*  Author  M.A.Perelmuter                                          */
/********************************************************************/
#include "string.h"

EXPORT short  index(LPSTR s1,short l1,LPSTR s2,short l2)
{
	short  k;

	k = l1 - l2;
	for (short i=0; i <= k; i++)
		if (!strncmp(&s1[i],s2,l2)) return(i);
	return(-1);
}