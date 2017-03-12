#ifndef DESTRUCTION_FLAG_H
#define DESTRUCTION_FLAG_H
#pragma pack(push,1)

#include "scadload.hpp"

struct DESTRUC_STR {
    LPSTR   Text;
    int     QuantityElem;
    int   * ListElem;

	BYTE    Type;          // служебное   
	BYTE    LevelMark;     // уровень оценки, 0 - осторожная, 1 - нет  
	
	WORD    NumComb;       // номер комбинации
	WORD    NumGroupForce; // номер группы нагрузок

    BYTE    YesSave;       //  Сохранить задачу с доп. именем ".DST.SPR"
	BYTE    Res[3];

	BYTE    TypeProcess;   // 0 - линейный расчет, 1 - нелинейный 
	BYTE    MethodStep;    // метод шага, 0 - простой шаговый, 1 - шагово-итерац., 2 - итерационный
	WORD    QuantityStep;  // число шагов 
	WORD    QuantityIter;  // число итераций

    double  CoeffDynamic;  //  коэффициент динамичности для даленных элементов. По умолчанию 2
    double  CoeffGroup;    //  коэффициент для падающих конструкций (группы)

	double  YellowDelta;   //  Интервал неопределенности, в котором еще держит элемент

};

class  DESTRUCTION : public SCAD_BASE_CLASS
{

public:
      DESTRUCTION()     {  Init();   }
     ~DESTRUCTION(void) {  Delete(); }

void          Init()  {  SCAD_BASE_CLASS::Init(0,0,40,40,1,20);  LenData[0] = sizeof(int);  }
	 
int   SCHEMA_EXPORT   Add( DESTRUC_STR  &DS, int Qnt, int *List );
void                  Add( DESTRUCTION &Bnd, int Qntt, int NewNum[]) {  AddClass(&Bnd,1,Qntt,NewNum); }
void  SCHEMA_EXPORT   Add( void *, int LenSent, BYTE &Control );
	 
void                  Change( int Num, LPSTR Name, int Qnt, int *List ) { ChangeObject(Num,NULL,Name,Qnt,List,0); }
int   SCHEMA_EXPORT   Change( int Num, DESTRUC_STR  &DS, int Qnt, int *List );

void  SCHEMA_EXPORT   SetProcess( int Num, int TypePr, int MetStep, int QntStep );

void                 ChangeList( int Num, int Qnt, int *List, int Type=0 ) { ChangeComponent(Num,1,Qnt,List,Type);   }
	 
DESTRUC_STR       *  Get(int Num) {  return (DESTRUC_STR*)SCAD_BASE_CLASS::GetObject(Num); }
	 
void  SCHEMA_EXPORT  Export( int NumDoc, FILEPRINT &Work );
void  SCHEMA_EXPORT  Print( void *Inp, int NumDoc );
	 
};

#pragma pack(pop)
#endif
