/*-------------------------------------------------------------*/
/*     The function switch off, on, read the bit number n      */
/*              from the address given by c                    */
/*-------------------------------------------------------------*/
/*     Author     V.S.Karpilovsky    17.03.95                  */
/*-------------------------------------------------------------*/

#include <stdafx.h>
#include <defclass.h>

EXPORT void BitOff(BYTE *c,int n)
{
     static BYTE ic[8] = {  0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F };
     c[ n / 8 ] &= ic[ n % 8 ];
}

EXPORT  void BitOn(BYTE *c,int n)
{
     static BYTE ic[8] = {  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
     c[ n / 8 ] |= ic[ n % 8 ];
}

EXPORT  int BitRead(BYTE *c,int n)
{
     static BYTE ic[8] = {  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
     return c[ n / 8 ] & ic[ n % 8 ] && 1;
}

EXPORT  void ConvStrBit(LPCSTR Inp,LPSTR Out)
{
     int i;
     for ( i=0; Inp[i]; i++ )
        if ( Inp[i] - '0' ) BitOn((BYTE*)Out,i);
        else BitOff((BYTE*)Out,i);

}

EXPORT  int DecodeNumBit( BYTE *Inp, BYTE Quantity, BYTE *Num)
{
      int i, k=0;
      for ( i=0; i<8*Quantity; i++ )
         if ( BitRead(Inp,i) ) Num[k++] = (BYTE)i;
      return k;
}

EXPORT  void DecodeStrBit( BYTE *Inp, int Qntt, BYTE *Out)
{
      int i, k = (int)(Qntt*BITSPERBYTE);
      ZeroMemory(Out,k);
      for ( i=0; i<k ; i++) if ( BitRead(Inp,i)) Out[i] = '1';
}

EXPORT  int SumBit( BYTE *Inp, int Length )
{
	 int i, Qntt=0, l= Length * BITSPERBYTE;
	 for ( i=0; i<l; i++) if ( BitRead(Inp,i)) Qntt++;
	 return Qntt;
}

EXPORT  void AddBit( BYTE *Inp, BYTE *Out, int Length )
{
	 int i, l= Length * BITSPERBYTE;
	 for ( i=0; i<l; i++) if ( BitRead(Inp,i)) BitOn(Out,i);
}