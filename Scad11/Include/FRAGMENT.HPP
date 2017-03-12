#ifndef FRAGMENT_FLAG_H
#define FRAGMENT_FLAG_H
#pragma pack(push,1)

#include <BaseClass.hpp>

struct FRAGMENT_STR
{
       LPSTR       Text;
       int         Quantity;
       int       * List;
       double      Angle;
};

struct FRAGMENT_INF
{
       BYTE            CalcLoad;
       BYTE            CalcRSN;
       BYTE            Res[2];
       int             QuantityElem;
       int           * NumElem;
};


class FRAGMENT : public SCAD_BASE_CLASS
{

public:

 	FRAGMENT()      {  Init();    }
  ~FRAGMENT(void)  {  Destroy();  }

void  SCHEMA_EXPORT  Init();
void  SCHEMA_EXPORT  Destroy();

void  SCHEMA_EXPORT  Delete();
void  SCHEMA_EXPORT  DeleteAllNode(void) {  SCAD_BASE_CLASS::Delete();  }
void  SCHEMA_EXPORT  DeleteElem(void);

void  SCHEMA_EXPORT  Copy( FRAGMENT & );
void  SCHEMA_EXPORT  Read(  FILEBASE &Work, DOCUMENT &Out );
void  SCHEMA_EXPORT  ReadOld(  FILEBASE &Work, DOCUMENT &Out );
void  SCHEMA_EXPORT  Write( FILEBASE &Work, DOCUMENT &Out );

int   SCHEMA_EXPORT  GetQuantityListNode();
FRAGMENT_STR * Get(int Num) {  return (FRAGMENT_STR*)GetObject(Num);  }
FRAGMENT_INF * GetInf() {  return (FRAGMENT_INF*)GetCommon();  }

void  SCHEMA_EXPORT  SetListElem( int Qnt, int  *Lst );
void  SCHEMA_EXPORT  GetListElem( int &Qnt, int **Lst );

int   SCHEMA_EXPORT  Include( double, int Qnt,int *Lst );
void  SCHEMA_EXPORT  Change(int Num, double , int Qnt,int *Lst );
void  SCHEMA_EXPORT  GetListNode( int Num,double &, int &Qnt,int **Lst );

void  SCHEMA_EXPORT  Compress( int EqualName, int QuantityOldElem, int NumElem[], int QuantityOldNode, int NumNode[] );

void  SCHEMA_EXPORT  Export( int NumDoc,  FILEPRINT &Work );
void  SCHEMA_EXPORT  Print( void *Inp );

};

#pragma pack(pop)
#endif
