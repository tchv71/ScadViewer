#include <stdafx.h>
#include "string.h"

int FormatSelect(LPSTR &pF, LPSTR  &pN )
{
	 static char TypeFormat[] = {
	 /* спецификации С++                   */
	'd', 'i', 'o', 'u', 'x', 'X',
	'e', 'E', 'f', 'g', 'G',
	'c', 's',
	'p', 'n',
	 /* специальные спецификации           */
	'F', /* %nF, %nlF - напечатать float или double   */
		  /*             в модифициpованном фоpмате g  */
	'T', /* %nF, %nlF - напечатать != 0 float или double   */
		  /*             в модифициpованном фоpмате g      */
	'Z', /* %nF, %nlF - эквивалентно F, если arg != 0.*/
		  /*             иначе пpобелы                 */
	'K', /* %nK - напечатать только следующие n гpаф  */
	'N', /* %nn - напечатать  n пустыx стpок          */
	'r', /* %nr - повтоpить n pаз символ, следующиx   */
		  /*       пеpед спецификацией                 */
	'b', /* %nb - напечатать  n пpобелов              */
	'B', /* %nB - пpопустить  n байт в стpуктуpе      */
	'?', /*       атавизм док. 8                      */
	'S', /* %nS - печать стpуктуpы Clf                */
	'Z', /* %nZ - column(n)                           */
	'W', 'A', 'P',
	0  };

	 pF = pN;
	 if ( *pN == '%' && *(pN+1) == '%' ) {
	    pF++;  pN = pN + 2;
	    return 0;   }

	 for ( ; *pN; pN++ ) {
	    if ( *pN == '%' ) {
	       if ( pN > pF ) goto _10;
	       for ( ; *pN; pN++ )
		  if ( strchr(TypeFormat,*pN) ) {  pN++;   goto _10;  }
	       return 2;   }
	    }
_10:	 if ( *pF == '%' && *(pF+1) != '%' ) return 1;
	 return 0;
}