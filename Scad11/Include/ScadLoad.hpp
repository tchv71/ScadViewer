#ifndef SCAD_LOAD_FLAG_H
#define SCAD_LOAD_FLAG_H
#pragma pack(push,1)

#include "classwin.hpp"
#include "ScadForce.hpp"
#include "DynamicMetod.h"

class SCAD_LOAD
{
public:
   BYTE          TypeLoad;
   BYTE          TypeDynamic;
   WORD          QuantityForm;
   WORD          NumAddLoad;
   WORD          ListMass;    //  список узлов, в которые собираются массы из док.13
   WORD          MaskMass;
   WORD          NumAksX;
   WORD          NumAksY;
   WORD          NumAksZ;
   WORD          NumBettaX;
   WORD          NumBettaY;
   WORD          NumBettaZ;
   WORD          Res[5];
   double        Weight;
   DYNAMIC_METOD DynMet; 

   WORD          QuantityData;
   double        Data[32];      //  данные для динамики

   WORD          NumUnite;

   WORD          NumLoadUnite;
   BYTE          YesDispl;

private:
   BYTE          Modify;
public:

   OBJECT_FILE * ListFile;

   SCAD_FORCE    ForceNode;
   SCAD_FORCE    ForceFE;
   SCAD_FORCE    ForceLoad;

 	SCAD_LOAD()  {  Init();    }
  ~SCAD_LOAD()  {  Destroy();  }

void  SCHEMA_EXPORT   Init();
void  SCHEMA_EXPORT   Delete();
void  SCHEMA_EXPORT   Destroy();

void  SCHEMA_EXPORT   SetClass( OBJECT_FILE * LF );

void  SCHEMA_EXPORT   SetTypeLoad( int Type);
void  SCHEMA_EXPORT   SetWeight( double W );
double SCHEMA_EXPORT  GetWeight() {  return Weight;  }

void  SCHEMA_EXPORT   Copy( SCAD_LOAD * );

void  SCHEMA_EXPORT   Compress( int QuantytiElemOld, int QntFE,   int * NumElem,
    int QuantytiNodeOld, int QntNode, int * NumNode , int QnttLoad);

void  SCHEMA_EXPORT   DeleteForceNode(int Quantity, int *List, BYTE qw, BYTE qn);
void  SCHEMA_EXPORT   DeleteForceFE(int Quantity, int *List, BYTE qw, BYTE qn);
void  SCHEMA_EXPORT   DeleteForceLoad(int Quantity, int *List, BYTE qw, BYTE qn);

void  SCHEMA_EXPORT   DeleteForceNode( int NumList, int Quantity, int *List );
void  SCHEMA_EXPORT   DeleteForceFE( int NumList, int Quantity, int *List );
void  SCHEMA_EXPORT   DeleteForceLoad( int NumList, int Quantity, int *List );

void  SCHEMA_EXPORT   Read( FILEBASE &Input, DOCUMENT & );
void  SCHEMA_EXPORT   Write( FILEBASE &Output, DOCUMENT &Doc );

int   SCHEMA_EXPORT   YesForce();
int   SCHEMA_EXPORT   GetModify();
void  SCHEMA_EXPORT   ClearModify();

void  SCHEMA_EXPORT   Include(LPSTR Name, BYTE Qw, BYTE Qn, int NumFile,int QntData, double Data[], int QntList, int List[] );
void           Include( BYTE Qw, BYTE Qn, int NumFile, int QntData, double Data[], int QntList, int List[] )
{    Include("",Qw,Qn,NumFile,QntData,Data,QntList,List);   }
void  SCHEMA_EXPORT   Add( int QuantityElem, BYTE TypeElem[], SCAD_LOAD &DtLd, BYTE MaskQw, double Coef );

void SCHEMA_EXPORT    Add( SCAD_LOAD &DtLd, BYTE MaskQw, BYTE MaskQn );
void SCHEMA_EXPORT    Add( int QuantityElem, void *pFrm, SCAD_LOAD &DtLd, double Coef, BYTE MaskQw, BYTE MaskQn );
void           ChangeData( void *, int Type, int  Num, LPSTR Sent, DWORD LenSent, LPSTR Name, BYTE & Control );

void SCHEMA_EXPORT    Compress( int EqualName, int OldQuantityNode, int NumNode[], int OldQuantityElem, int NumElem[] );

int  SCHEMA_EXPORT    YesData() {
               if ( ForceNode.Quantity || ForceFE.Quantity || ForceLoad.Quantity ) return 1;
               return 0;  }
void SCHEMA_EXPORT    EqualElem( void *Sch, BYTE MaskQw, BYTE MaskQn );
void SCHEMA_EXPORT    EqualNode( BYTE MaskQw, BYTE MaskQn );
void SCHEMA_EXPORT    EqualForce( void *Sch, SCAD_FORCE &FrcGrp, BYTE MaskQw, BYTE MaskQn );

SCAD_LOAD & operator = ( SCAD_LOAD &SL ) {
	   Copy(&SL);
	   return *this;	}

};

struct DATA_AXSEL {
       double  Gamma;
       double  cx,  cy;
       double  MastabA, MastabB, MastabZ;
       double  CoeffTime;
       };

#pragma pack(pop)
#endif
