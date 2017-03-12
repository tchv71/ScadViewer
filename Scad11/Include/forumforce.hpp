#ifndef FORUM_FORCE_FLAG_H
#define FORUM_FORCE_FLAG_H
#pragma pack(push,1)

#include "baseclass.hpp"
#include "ObjectList.hpp"
#include "ObjectString.hpp"


struct FORUM_FORCE_COMMON
{
	    BYTE    AutoDeadWeight;  // Автоматическое назначение собственного веса
	    BYTE    WhatForm;        // 0 - формирование групп нагрузок, 1 - формирование загружений
	    BYTE    TypeValues;      // 0 - нормативное значение, 1 - расчетное значение;
        BYTE    ResB[5];
		double ConcreteCoef;    // Коэф. надежности по нагрузке для ж/б
		double SteelCoef;       // Коэф. надежности по нагрузке для стали
		double AnotherCoef;     // Коэф. надежности по нагрузке для прочих
        double  Res[4];
};

struct FORUM_FORCE_STR
{
      LPSTR    Text;
      int      Quantity;
      int    * NumConstr;
      double   StandartForce;          // Нормативное значение нагрузки
      double   CalculValueForce;       // Расчетное значение нагрузки
      double   SafetyFactor;           // Коэф. надежности по нагрузке
      double   Res[4];
	  int      NumNameConstr;
	  int      ResWord;
};

struct TYPE_CONSTR_STR
{
	LPSTR    Text;
	COLORREF Clr;
};

class  TYPE_CONSTR: public SCAD_BASE_CLASS
{
public:
	 TYPE_CONSTR()     {  Init();    }
	~TYPE_CONSTR(void) {  Destroy();  }
	
	void Init() {  SCAD_BASE_CLASS::Init(0,0,sizeof(COLORREF),sizeof(COLORREF),0,0);  }
	
int  SCHEMA_EXPORT Add(LPSTR Text, COLORREF Clr ) {  
	   AddObject(NULL,Text);     
       Get(Quantity)->Clr = Clr;
	   return Quantity;
}

SCHEMA_EXPORT TYPE_CONSTR_STR * Get( int Num ) {  return (TYPE_CONSTR_STR *)GetObject(Num);  }
	
};

class FORUM_FORCE
{
public:
       FORUM_FORCE_COMMON  Common;

       TYPE_CONSTR         TypeConstr;
       OBJECT_LIST         ListElem;

       SCAD_BASE_CLASS     ConstantForce;
       SCAD_BASE_CLASS     TimeForce;
	   
	   BYTE                Modify;

public:

      FORUM_FORCE()      {  Init(); }
     ~FORUM_FORCE(void)  {  Destroy(); }

void  SCHEMA_EXPORT Init();

void  SCHEMA_EXPORT Delete();

void  SCHEMA_EXPORT Destroy();

void SetCommon( FORUM_FORCE_COMMON &FC ) {  memcpy(&Common,&FC,sizeof(FORUM_FORCE_COMMON));  Modify = 1; }
FORUM_FORCE_COMMON * GetCommon() {  return &Common; }

int    AddTypeConstr( LPSTR Text, COLORREF Clr = RGB(0,0,0) )     {  return TypeConstr.Add(Text,Clr);  }
void   ChangeTypeConstr( int NumPP, LPSTR Text, COLORREF Clr = RGB(0,0,0) )     {  
	TypeConstr.SetText(NumPP,Text); 
	if(NumPP > 0 && NumPP <= TypeConstr.Quantity)
		TypeConstr.Get(NumPP)->Clr = Clr;  }
LPCSTR GetNameTypeConstr( int NumPP ) {  return TypeConstr.GetText(NumPP);  }
COLORREF GetColTypeConstr(int NumPP) {
	if(NumPP > 0 && NumPP <= TypeConstr.Quantity)
		return TypeConstr.Get(NumPP)->Clr;
	else
		return RGB(0,0,0);
}
SCHEMA_EXPORT int    DeleteTypeConstr( int NumPP );
SCHEMA_EXPORT int    GetTypeElem( int NumElem );
SCHEMA_EXPORT void   GetTypeListElem( int Type, int &Qnt, int **List );

int   SCHEMA_EXPORT AddConstantForce( LPSTR Ident, FORUM_FORCE_STR &FS );
FORUM_FORCE_STR *     GetConstantForce( int NumPP ) { return (FORUM_FORCE_STR *) ConstantForce.GetObject(NumPP); }
void  SCHEMA_EXPORT ChangeConstantForce( int NumPP, LPSTR Ident, FORUM_FORCE_STR &FS  );
void  SCHEMA_EXPORT ChangeConstantForceListConstr( int NumPP, int Qnt, int *List );
void                  ChangeNameConstantForce( int NumPP, LPSTR Text ) { ConstantForce.SetText(NumPP,Text); };
void                  DeleteConstantForce( int NumPP ) { ConstantForce.Delete(NumPP); };

int   SCHEMA_EXPORT AddTimeForce( int NumConstr, FORUM_FORCE_STR &FS );
int   SCHEMA_EXPORT GetNumTimeForce( int NumConstr ); 
FORUM_FORCE_STR *     GetTimeForce( int NumPP ) { return (FORUM_FORCE_STR *) TimeForce.GetObject(NumPP); }
void  SCHEMA_EXPORT  ChangeTimeForce( int NumPP, FORUM_FORCE_STR &FS  );
void                  DeleteTimeForce( int NumPP ) { TimeForce.Delete(NumPP); };

SCHEMA_EXPORT void   AddListElem( int NumConstr, int Qnt, int Num[] );
SCHEMA_EXPORT void   DeleteListElem( int Qnt, int Num[] );

SCHEMA_EXPORT void   Add( void *Inp, int NumComponent=1, int QuantityNum=0, int *NewNumber=NULL );  //  в список

SCHEMA_EXPORT void   Compress( int QuantityOld, int * NewNum );

SCHEMA_EXPORT void   Copy( FORUM_FORCE &);
SCHEMA_EXPORT void   Read( FILEBASE &Input, DOCUMENT & );
SCHEMA_EXPORT void   Write( FILEBASE &Output, DOCUMENT &Doc );

SCHEMA_EXPORT int    GetModify( ); 

};
#pragma pack(pop)
#endif

