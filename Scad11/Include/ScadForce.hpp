#ifndef SCAD_FORCE_FLAG_H
#define SCAD_FORCE_FLAG_H
#pragma pack(push,1)

#include "classwin.hpp"
#include "BaseClass.hpp"

struct FORCE_STR
{
       LPSTR          Text;
       int            QuantityData;
       double       * Data;
       int            Quantity;
       int          * List;
       BYTE           Type;   //   служебное
       BYTE           Qw;
       BYTE           Qn;
       BYTE           Res[3];
       WORD           NumFile;
};

class  SCAD_FORCE : public SCAD_BASE_CLASS
{
public:
       OBJECT_FILE *  ListFile;

 	SCAD_FORCE()  {  Init();    }
  ~SCAD_FORCE()  {  Destroy();  }

void          Init()  {  SCAD_BASE_CLASS::Init(sizeof(OBJECT_FILE *),0,8,8,2,20);   LenData[0] = sizeof(double);  LenData[1] = sizeof(int); }

void          DeleteForce( int Quantity, int *List, BYTE qw=0xFF, BYTE qn=0xFF );
FORCE_STR   * Get(int Num) { return (FORCE_STR *)GetObject(Num);  }
void SCHEMA_EXPORT   DeleteForce( int Num, int Qnt, int *List );

void          SetListFile(OBJECT_FILE * LF) {  ListFile = LF; }

void Compress( int EqualName, int QuantityOld, int * NewNum )
{
              CompressObject(EqualName,0,1,2,QuantityOld,NewNum,0,-1);
}

void SCHEMA_EXPORT   ChangeList( int NumStr, int Qnt, int List[], int Type=0 ) {
              ChangeComponent(NumStr,2,Qnt,List,Type);    }

void SCHEMA_EXPORT   ChangeValue( int NumStr, int Qnt, double Data[] ) {
              ChangeComponent(NumStr,1,Qnt,Data);    }

void SCHEMA_EXPORT   Add( int QuantityElem, void *pF, SCAD_FORCE &FrcGrpInp, BYTE MaskQw, BYTE MaskQn, double Coef );

void SCHEMA_EXPORT   Add( SCAD_FORCE &FrcGrpInp, BYTE MaskQw, BYTE MaskQn );

void SCHEMA_EXPORT   Copy( SCAD_FORCE *FrcGrpInp );

SCAD_FORCE & operator = ( SCAD_FORCE &SF ) {
	   Copy(&SF);
	   return *this;	}

};

#pragma pack(pop)
#endif

