#ifndef INFORM_BIT_H
#define INFORM_BIT_H
#pragma pack(push, 1)
/*-------------------------------------------------------------*/
/*     The function switch off, on, read the bit number n      */
/*              from the address given by c                    */
/*-------------------------------------------------------------*/
/*     Author     V.S.Karpilovsky    17.03.95                  */
/*-------------------------------------------------------------*/
EXPORT void  BitOff(BYTE *c,int n);

EXPORT void  BitOn(BYTE *c,int n);

EXPORT int   BitRead(BYTE *c,int n);

EXPORT void  ConvStrBit(LPCSTR Inp,LPSTR Out);

EXPORT int   DecodeNumBit( BYTE *Inp, BYTE Quantity, BYTE *Num);

EXPORT void  DecodeStrBit( BYTE *Inp, int Qntt, BYTE *Out);

EXPORT int   SumBit(BYTE *Inp, int Length );

EXPORT void  AddBit(BYTE *Inp, BYTE *Out, int Length );

//BOOL   CopyFile(NameFileInp,NameFileOut,BOOL = FALSE );
#pragma pack(pop)
#endif
