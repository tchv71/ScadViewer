#include <stdafx.h>
#include <defclass.h>

EXPORT void SpaceSet( void *Out, BYTE Value, DWORD Quantity ) {
	for ( HPSTR pO=(HPSTR)Out; pO < (HPSTR)Out + Quantity; pO++ )
	   *pO = Value;
//       FillMemory(Out,Quantity,Value);
}
EXPORT void SpaceSet( void *Out, DWORD Quantity ) {
	for ( HPSTR pO=(HPSTR)Out; pO < (HPSTR)Out + Quantity; pO++ )
	   *pO = 0;
//       ZeroMemory(Out,Quantity);
}

EXPORT int SpaceCompare(void *Out,void *Inp,DWORD Quantity) {
     LPSTR pI = (LPSTR)Inp;
     LPSTR pO = (LPSTR)Out;
     for ( DWORD i=0; i<Quantity; i++ ) {
       if ( *pO != *pI ) return 1;
       pO++;  pI++;  }
     return 0;
}