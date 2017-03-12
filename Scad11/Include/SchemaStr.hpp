#ifndef SCHEMA_STR_FLAG_H
#define SCHEMA_STR_FLAG_H
#pragma pack(push,1)

struct  TREE {
	BYTE          Regime;
	SYSTEMTIME    TimeModify;
};

struct CK {
	double x, y, z;
    LPSTR  Name;
	WORD   Flag;
};

struct  DefCK
{
	double x,   y,  z;
	double ux, uy, uz;
	int n_unk[16];
};

struct  GrafCK {  int x, y; };

struct  TYPE_SYSTEM {
	BYTE Num;
	BYTE QuantityStep;
	BYTE NumStep[16];  };
	
struct ADD_SCHEMA_DATA  {
   BYTE    TypeCoincidence;     // 0 - полное объединение, 1 - объединение по маске
   WORD    MaskContact;         // типы объединяемыx связей
   BYTE    QuantityNodeDocking; // число узлов, опpеделяющиx соединение
   BYTE    YesScale;            // масштабиpование пpи двуx точкаx соединени
   BYTE    YesCorner1;          // задан угол пpи двуx точкаx соединения,1-rad,2-grad
   double  Corner1;
   BYTE    YesCorner2;          // задан угол пpи двуx точкаx соединения,1-rad,2-grad
   double  Corner2;
   int     NumNodeDocking1[3];  // номеpа узлов в  пеpвой сxеме
   int     NumNodeDocking2[3];  // номеpа узлов во втоpой сxеме
   BYTE    YesDelta;            //   напpавления осей заданы вектоpами
   double  Punct11[3];          //       кооpдинаты узлов,
   double  Punct12[3];          //     фиксиpующиx положение
   double  Punct13[3];          //    пpисоединяемой подсxемы
   double  Punct23[3];          //
   double  PrecesionCoincidence;// точность стыковки
   BYTE    DeleteEqualElem;     // пpизнак удаления эквив.элементов из 2-й сxемы
   BYTE    AddEfforsGroup;      // включить нагpузки 2-й сxемы как гpуппы
   BYTE    AddForceEqNode;
   BYTE    NoAddRigid;
};

struct SCHEMA_PARAM
{
   BYTE     TypeOptimization;    //  nop, opt
   BYTE     TypeSolver;          //  тип солвера
   BYTE     PrecessionSolver;    //  tgs
   BYTE     PrecessionDynamic;   //  erd
   BYTE     PrecessionStabil;    //  точность определенияя форм потери устойчивости
   BYTE     CheckSolution;       //  Gauss control   ngs
   BYTE     CheckGaussError;     //  точность проверки решени
   WORD     QuantityIter;        //  itr
   BYTE     EpsCheckFE;          //  точность контроля элементов в библиотеке
   BYTE     EfforsNode;          //  тип вычисления усилий в узлах
   BYTE     Res1;                 //  
   BYTE     NoForceInsert;       // Не учитывать равномерно-распред. нагрузку на вставках в стержнях
   BYTE     Res[12];
   UNITS    UnitsOut[5];
};

struct DOC08 {   short  krs[8];  float  rs[18];  };
#define KRS08(I,J)    doc08[(I)].krs[(J)]
#define RS08(I,J)     doc08[(I)].rs[(J)]


struct KOORLINE {	BYTE Type; char Name[16]; double Pos; };
struct S_Doc21  { WORD XLineQuantity; WORD YLineQuantity; WORD HLineQuantity; KOORLINE Line[1]; };

struct  KOF {  short  nnag;   float  rkn;  };
struct  LOAD_COMBINATION {   WORD   Quantity;   KOF  * Kof;	   };

#pragma pack(pop)
#endif
