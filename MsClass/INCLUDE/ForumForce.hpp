#ifndef FORUM_FORCE_FLAG_H
#define FORUM_FORCE_FLAG_H
#pragma pack(push,1)

#include "classwin.h"
#include "ObjectList.hpp"
#include "ObjectString.hpp"


struct FORUM_FORCE_COMMON
{
	    BYTE    AutoDeadWeight;  // јвтоматическое назначение собственного веса
	    BYTE    WhatForm;        // 0 - формирование групп нагрузок, 1 - формирование загружений
	    BYTE    TypeValues;      // 0 - нормативное значение, 1 - расчетное значение;
        BYTE    ResB[5];
        double  Res[7];
};

struct FORUM_FORCE_STR
{
      LPSTR    Text;
      int      Quantity;
      int    * NumConstr;
      double   StandartForce;          // Ќормативное значение нагрузки
      double   CalculValueForce;       // –асчетное значение нагрузки
      double   SafetyFactor;           //  оэф. надежности по нагрузке
      double   Res[4];
	  int      NumNameConstr;
	  int      ResWord;
};

struct TYPE_CONSTR_STR
{
	LPSTR    Text;
	COLORREF Clr;
};

class  TYPE_CONSTR: public BASE_CLASS
{
public:
	 TYPE_CONSTR()     {  Init();    }
	~TYPE_CONSTR(void) {  Destroy();  }
	
	void Init() {  BASE_CLASS::Init(0,0,sizeof(COLORREF),sizeof(COLORREF),0,0);  }
	
int  EXPORT Add(LPSTR Text, COLORREF Clr ) {  
	   AddObject(NULL,Text);     
       Get(Quantity)->Clr = Clr;
	   return Quantity;
}

EXPORT TYPE_CONSTR_STR * Get( int Num ) {  return (TYPE_CONSTR_STR *)GetObject(Num);  }
	
};

class FORUM_FORCE
{
public:
       FORUM_FORCE_COMMON  Common;

       TYPE_CONSTR     TypeConstr;
       OBJECT_LIST     ListElem;

       BASE_CLASS      ConstantForce;
       BASE_CLASS      TimeForce;

public:

      FORUM_FORCE()      {  Init(); }
     ~FORUM_FORCE(void)  {  Destroy(); }

void  EXPORT Init() {
      Delete();
	  TypeConstr.Init();
	  ListElem.Init();
      ConstantForce.Init(0,0,8*sizeof(double),8*sizeof(double),1,20);
      ConstantForce.LenData[0] = sizeof(int);
      TimeForce.Init(0,0,8*sizeof(double),8*sizeof(double),1,20);
}

void Delete() {  
  	  TypeConstr.Delete();
	  ListElem.Delete();
      ConstantForce.Delete();
      TimeForce.Delete();
      ZeroMemory(&Common,sizeof(Common));
}

void Destroy() {  
      ListElem.Destroy();
      ConstantForce.Destroy();
      TimeForce.Destroy();
      ZeroMemory(&Common,sizeof(Common));
}

void SetCommon( FORUM_FORCE_COMMON &FC ) {  memcpy(&Common,&FC,sizeof(FORUM_FORCE_COMMON)); }
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
EXPORT  int    DeleteTypeConstr( int NumPP );
EXPORT  int    GetTypeElem( int NumElem );
EXPORT  void   GetTypeListElem( int Type, int &Qnt, int **List );

int   EXPORT   AddConstantForce( LPSTR Ident, FORUM_FORCE_STR &FS );
FORUM_FORCE_STR *     GetConstantForce( int NumPP ) { return (FORUM_FORCE_STR *) ConstantForce.GetObject(NumPP); }
void  EXPORT   ChangeConstantForce( int NumPP, LPSTR Ident, FORUM_FORCE_STR &FS  );
void  EXPORT   ChangeConstantForceListConstr( int NumPP, int Qnt, int *List );
void                  ChangeNameConstantForce( int NumPP, LPSTR Text ) { ConstantForce.SetText(NumPP,Text); };
void                  DeleteConstantForce( int NumPP ) { ConstantForce.Delete(NumPP); };

int   EXPORT   AddTimeForce( int NumConstr, FORUM_FORCE_STR &FS );
int   EXPORT   GetNumTimeForce( int NumConstr ); 
FORUM_FORCE_STR *     GetTimeForce( int NumPP ) { return (FORUM_FORCE_STR *) TimeForce.GetObject(NumPP); }
void  EXPORT   ChangeTimeForce( int NumPP, FORUM_FORCE_STR &FS  );
void                  DeleteTimeForce( int NumPP ) { TimeForce.Delete(NumPP); };

EXPORT  void   AddListElem( int NumConstr, int Qnt, int Num[] );
EXPORT  void   DeleteListElem( int Qnt, int Num[] );

EXPORT  void   Compress( int QuantityOld, int * NewNum );

EXPORT  void   Copy( FORUM_FORCE &);
EXPORT  void   Read( FILEBASE &Input, DOCUMENT & );
EXPORT  void   Write( FILEBASE &Output, DOCUMENT &Doc );

};
#pragma pack(pop)
#endif

