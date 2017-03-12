#ifndef SCHEMA_INTERFACE_FLAG_H
#define SCHEMA_INTERFACE_FLAG_H
#pragma pack(push,1)

struct RIGID_IDENT_HELP
{
       char          Text[256];
       int           Quantity;
       double        Data[32];
};

void  SCHEMA_EXPORT  InitProject();
void  SCHEMA_EXPORT  DeleteProject();

int   SCHEMA_EXPORT  ReadProject( LPSTR NameFile );
int   SCHEMA_EXPORT  WriteProject( LPSTR NameFile );

void  SCHEMA_EXPORT  SetNameProject( LPCSTR Name );

void  SCHEMA_EXPORT  SetTypeSystem( int Num );

int   SCHEMA_EXPORT  AddElemProject( int TypeElem, int TypeRigid, int QuantityNodeElem, int ListNodeElem[] );
int   SCHEMA_EXPORT  AddNodeProject( int QuantityNode, CK CoordNode[] );

void  SCHEMA_EXPORT  SetLoadName( int Num, LPSTR Text );

void  SCHEMA_EXPORT  IncludeForce( int NumLoad, BYTE Qw, BYTE Qn, int QntData, double Data[], int QntList, int ListElem[] );

int   SCHEMA_EXPORT  IncludeRigid( BYTE Tp, LPSTR Name, int QntRgd, RIGID_IDENT_HELP *pRgd, int Qnt, int *LstElem );

void  SCHEMA_EXPORT  IncludeCorner( int TypeRigid, double Data[6], char TypeCorner[], int QuantityElem, int ListElem[] );

void  SCHEMA_EXPORT  IncludeInsert( double Data[6], int TypeInsert, int QuantityElem, int ListElem[] );

#endif
