#ifndef TYPE_DATA_FLAG_H
#define TYPE_DATA_FLAG_H
#pragma pack(push, 1)

struct TYPE_DATA_SF { BYTE b;  double d; };

union TYPE_DATA {
      short   hi;
      WORD    w;
      int     i;
      UINT    ui;
      long    l;
      DWORD   dw;
      float   f;
      double  d;
      long double  ld;
      char    c;
      char    s[2];
      BYTE    b;
      LPSTR   p;
      TYPE_DATA_SF SF;
  };

#define DataHI     Data->hi
#define DataW      Data->w
#define DataI      Data->i
#define DataL      Data->l
#define DataDW     Data->dw
#define DataF      Data->f
#define DataD      Data->d
#define DataLD     Data->ld
#define DataC      Data->c
#define DataS      Data->s
#define DataP      Data->p
#define DataB      Data->b
#define DataSF     Data->SF
#define DataSFB    Data->SF.b
#define DataSFD    Data->SF.d

#pragma pack(pop)
#endif