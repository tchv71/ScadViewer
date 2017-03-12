#ifndef INPUT_DOCUMENT_FLAG_H
#define INPUT_DOCUMENT_FLAG_H
#pragma pack(push,1)

    struct DOC01 {
	   short  tke;
	   short  ntg;
	   short  nu[4]; };

#define TKE01(I)    doc01[(I)].tke
#define NTG01(I)    doc01[(I)].ntg
#define NU01(I,J)   doc01[(I)].nu[(J)]

    struct DOC02 {
	   WORD   nke;
	   WORD   uke;
	   WORD   swu; };

#define NKE02(i)   doc02[(i)].nke
#define UKE02(i)   doc02[(i)].uke
#define SWU02(i)   doc02[(i)].swu

    struct DOC03R {
	   WORD   ntg;
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
	   int    nu;
	   short  nsw[6]; };

#define NU05(I)     doc05[(I)].nu
#define NSW05(I,J)  doc05[(I)].nsw[(J)]

#define MNS(I,J)    NumUnknown[(long)((I)*(long)KSW+(J))]

    struct DOC06 {
	   int    nue;
	   BYTE   qw;
	   BYTE   qn;
	   int    lpm;
	   short  nng;        };

    struct DOC06W {
	   int    nue;
	   BYTE   qw;
	   BYTE   qn;
	   int    lpm;
	   short  nng;        };

#define NUE06(I)    doc06[(I)].nue
#define QW06(I)     doc06[(I)].qw
#define QN06(I)     doc06[(I)].qn
#define LPM06(I)    doc06[(I)].lpm
#define NNG06(I)    doc06[(I)].nng

    struct DOC07 {
	   int    ntf;
	   WORD   kh;
	   double h[4];        };

#define NTF07(I)    doc07[(I)].ntf
#define KH07(I)     doc07[(I)].kh
#define H07(I,J)    doc07[(I)].h[J]

    struct DOC07_POS {  DWORD NumPos;  WORD QuantityValue;  };
#define NumPos07(I)     Pos07[I].NumPos
#define QnttValue07(I)  Pos07[I].QuantityValue

    struct DOC15 {
	   short   ls15;            /*  ¤«Ё­  бва®ЄЁ ў Ў ©в е         */
	   short   ia15[5];
	   float   ra15[200];  };   /*  ¤«Ё­  rs «оЎ п                */

    struct DOC15AxselFull {
	    short  ls15;
       short  NumMod;
       WORD   QuantityForm;
       short  ia15[3];   //  резерв
       float  Gamma;
       float  cx,  cy;
       float  MastabA, MastabB, MastabZ;
       float  CoeffTime;
       char   Name[3][256];
       };

    struct DOC15Axsel {
	   short   ls15;            /*  ¤«Ё­  бва®ЄЁ ў Ў ©в е         */
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

struct DOC15Arm {
	   short   ls15;
	   short   Type;
	   short   QuantityForm;
	   short   ir[3];           //  резерв
      float   Correction;      //  Поправочный коэффициент
      float   k0;              //  коэффициент грунтовых условий (табл.1.3)
      float   k1;              //  коэффициент, учитывающий допустимые повреждения
                               //    конструкций (табл.2.4)
      float   k2;              //  коэффициент ответственности сооружений по табл. 2.5
      float   A;               //  Коэффициент сесмичности, п.2.9.
      float   KA;              //  Поправочный множитель к А для верт. направления, п.2.14.
                               //  По умолчанию принимается значение 0.7
      float   Ground;          //  Категория грунта:1 -2 -3 -4 - график
      float   CX, CY, CZ;      //  косинусы: CX с осью X; CY - с осью Y; CZ - с осью Z -
                               //    задают направление действия поступательной сейсмической
                               //    нагрузки. Вектор нормируется в программе.
      float   Res;
};

struct DOC15Atom {
	   short   ls15;
	   short   Type;
	   short   QuantityForm;
	   short   ir[3];           //  резерв
      float   ke;              //  Коэффициент, учитывающий особые условия эксплуатации АС
      float   TypeGraf;        //  Тип графика коэффициента динамичности
                               //  0 - по рис.П3.1.
                               //  1 - единый для всех  направлений
                               //  2 - различный для всех направлений
      float   Dl;              //  логарифмический декремент колебаний
      float   Axy;             //  Максимальные ускорения грунта в горизонтальной плоскости
      float   KA;              //  Максимальные ускорения грунта в направлении Z
      float   CX, CY, CZ;      //  косинусы: CX с осью X; CY - с осью Y; CZ - с осью Z -
                               //    задают направление действия поступательной сейсмической
                               //    нагрузки. Вектор нормируется в программе.
      char    Name[3][256];     //  имена графиков

};

	struct S39 {  short ls;  short ngs; char s[1000];  };
	
	struct  REPID_OLD { char s[4];  short n1;  short n2;  short n3;  };

#pragma pack(pop)
#endif
