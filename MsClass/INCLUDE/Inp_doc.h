#ifndef INPUT_DOCUMENT_FLAG_H
#define INPUT_DOCUMENT_FLAG_H
#pragma pack(push, 1)
#include "classwin.h"
#include "loadcomb.h"

    struct DOC01 {
	   short  tke;
	   short  ntg;
	   short  nu[4]; };

#define TKE01(I)    doc01[(I)].tke
#define NTG01(I)    doc01[(I)].ntg
#define NU01(I,J)   doc01[(I)].nu[(J)]

    struct DOC02 {
	   short  nke;
	   short  uke;
	   short  swu; };

#define NKE02(i)   doc02[(i)].nke
#define UKE02(i)   doc02[(i)].uke
#define SWU02(i)   doc02[(i)].swu

    struct DOC03R {
	   short  ntg;
	   short  kg;
	   TYPE_DATA_SF SF[9];   };

#define NTG03R(I)   doc03r[(I)].ntg
#define KG03R(I)    doc03r[(I)].kg
#define C03R(I,J)   doc03r[(I)].SF[(J)].b
#define G03R(I,J)   doc03r[(I)].SF[(J)].lf

    struct DOC03 {
	   short        ntg;
	   short        kg;
	   TYPE_DATA_SF SF[9];   };

#define NTG03(I)   doc03[(I)].ntg
#define KG03(I)    doc03[(I)].kg
#define C03(I,J)   doc03[(I)].SF[(J)].b
#define G03(I,J)   doc03[(I)].SF[(J)].lf

    struct DOC04 {
	   double x;
	   double y;
	   double z;  };

#define X(I)        doc04[(I)].x
#define Y(I)        doc04[(I)].y
#define Z(I)        doc04[(I)].z

    struct DOC05 {
	   short  nu;
	   short  nsw[6]; };

#define NU05(I)     doc05[(I)].nu
#define NSW05(I,J)  doc05[(I)].nsw[(J)]

#define MNS(I,J)    NumUnknown[(long)((I)*(long)KSW+(J))]

    struct DOC06 {
	   short  nue;
	   BYTE  qw;
	   BYTE  qn;
	   short  lpm;
	   short  nng;        };

    struct DOC06W {
	   WORD  nue;
	   BYTE  qw;
	   BYTE  qn;
	   WORD  lpm;
	   short nng;        };

#define NUE06(I)    doc06[(I)].nue
#define QW06(I)     doc06[(I)].qw
#define QN06(I)     doc06[(I)].qn
#define LPM06(I)    doc06[(I)].lpm
#define NNG06(I)    doc06[(I)].nng

    struct DOC07 {
	   short  ntf;
	   short  kh;
	   double h[4];        };

#define NTF07(I)    doc07[(I)].ntf
#define KH07(I)     doc07[(I)].kh
#define H07(I,J)    doc07[(I)].h[J]

    struct DOC07_POS {  DWORD NumPos;  WORD QuantityValue;  };
#define NumPos07(I)     Pos07[I].NumPos
#define QnttValue07(I)  Pos07[I].QuantityValue


    struct DOC08 {
	   short  krs[8];
	   float  rs[18];  };

#define KRS08(I,J)    doc08[(I)].krs[(J)]
#define RS08(I,J)     doc08[(I)].rs[(J)]

    struct DOC15 {
	   short   ls15;            /*  длина строки в байтах         */
	   short   ia15[5];
	   float  ra15[200];  };   /*  длина rs любая                */

    struct DOC15Axsel {
	   short   ls15;            /*  длина строки в байтах         */
	   short   ia15[5];
	   float   ra15[3];
           float   Mastab;
	   float   ra15a[3];
           float   DeltaTime;
	   float   Time;
	   char    Name[256];
           };

#define LS15          doc15->ls15
#define IA15(I)       doc15->ia15[(I)]
#define RA15(I)       doc15->ra15[(I)]

      struct S39 {  short ls;  short ngs; char s[1000];  };

struct KOORLINE {	BYTE Type; char Name[16]; double Pos; };
struct S_Doc21  { WORD XLineQuantity; WORD YLineQuantity; WORD HLineQuantity; KOORLINE Line[1]; };
#pragma pack(pop)

#endif
