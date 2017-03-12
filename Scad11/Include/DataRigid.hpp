#ifndef DATA_RIGID_FLAG_H
#define DATA_RIGID_FLAG_H

#include "classwin.hpp"
#include "ObjectData.hpp"
#include <identificator.hpp>
#pragma pack(push,1)

struct RIGID_STR
{
       LPSTR          Text;

       int            QuantityRgd;
       int         *  ListRgd;

       int            QuantityElem;
       int         *  ListElem;

       BYTE           Type;
       BYTE           Icon;
       BYTE           Control;
       BYTE           Res[5];
       double         Alfa;
};

struct RIGID_LIST_OLD
{
	int            Num;
	BYTE           Type;
	int            QuantityRgd;
	int            Quantity;  /*   List  */
	TYPE_DATA_SF * pRgd;
	int          * List;
	BYTE           Icon;
	double         Alfa;
};

class DATA_RIGID : public SCAD_BASE_CLASS
{

public:
       OBJECT_FILE   * ListFile;
       IDENTIFICATOR   Ident;

	   int             QuantityTDS;
	   RIGID_LIST_OLD  RigidList;

DATA_RIGID & operator = ( DATA_RIGID &DR ) {
	   Copy(DR);
	   return *this;	}

	   DATA_RIGID()      {  Init();    }
  ~DATA_RIGID(void)  {  Destroy();  }

void  SCHEMA_EXPORT  Init();
void  SCHEMA_EXPORT  Destroy();

void  SCHEMA_EXPORT  Delete();

void  SCHEMA_EXPORT  Copy( DATA_RIGID & );
void  SCHEMA_EXPORT  Read(  FILEBASE &Work, DOCUMENT &Doc  );
void  SCHEMA_EXPORT  Write( FILEBASE &Work, DOCUMENT &Out );

void          SetListFile(OBJECT_FILE * LF) {  ListFile = LF;  Ident.SetListFile(LF);  }

void SCHEMA_EXPORT   DeleteSection( int Num );

void SCHEMA_EXPORT   DeleteElem( int Num );
void SCHEMA_EXPORT   DeleteElem( int Quantity, int *ListNum);

int SCHEMA_EXPORT    Include( BYTE Tp, LPSTR Name, int QntRgd, IDENT_STR *pRgd, int Qnt, int *Lst );
int SCHEMA_EXPORT    Include( BYTE Tp, LPSTR Name, int QntRgd, int *pRgd, int Qnt, int *Lst );
int SCHEMA_EXPORT    Include( BYTE Tp, LPSTR Name, LPSTR Idnt, int QntDbl, double *Dbl, int Qnt, int *Lst );
int SCHEMA_EXPORT    Include( BYTE Tp, LPSTR Name, IDENTIFICATOR &ID, int QntID=0, int *ListID=NULL, int Qnt=0, int *Lst=NULL);

RIGID_STR *   Get(int Num)  {  return (RIGID_STR*)GetObject(Num);  }
void  SCHEMA_EXPORT  GetRigid(int NumPP, BYTE &Tp, int &QntRgd,   int **ListRgd, IDENT_STR **IdLst, int &Qnt, int **Lst );

void  SCHEMA_EXPORT  Change( int Num, BYTE Tp, LPSTR Name, int QntRgd, IDENT_STR *pRgd );
void  SCHEMA_EXPORT  Change( int Num, BYTE Tp, LPSTR Name, int QntRgd, IDENT_STR **pRgd );
int   SCHEMA_EXPORT  ChangeSection( int Num, int Type, LPSTR NameFile, LPSTR Name, int QntDbl, double *Dbl, int Qnt=0, int *Lst=NULL );
int   SCHEMA_EXPORT  ChangeSection( int Num, LPSTR NameBase, LPSTR NameString, int NumString, int QntDbl, double *Dbl, int Qnt, int *Lst );
int   SCHEMA_EXPORT  Change( int Num, int Tp, LPSTR Name, IDENTIFICATOR &ID, int QntID=0, int *ListID=NULL, int Qnt=0, int *Lst=NULL);

void  SCHEMA_EXPORT  ChangeList( int Num, int Quantity, int *List, int Type=0 );
void  SCHEMA_EXPORT  AddElem(int Num, int Quantity, int *ListNum, int Type=1 );
void  SCHEMA_EXPORT  GetIdent( int Num, char *Ident, BYTE LenCMP, IDENT_STR **IdentList );
void  SCHEMA_EXPORT  GetIdentType( int Num, int Type, IDENT_STR **IdentList );
void  SCHEMA_EXPORT  Compress( int EqualRigid, int EqualName, int QuantityOld, int * NewNum  );
void  SCHEMA_EXPORT  CompressType( BYTE *YesList );

int   SCHEMA_EXPORT  ChangeIdent( int Num, char *Ident, BYTE LenCMP, LPSTR Name, int Qnt, double *Data );

void  SCHEMA_EXPORT  DeleteIdent( int Num, LPSTR Ident, BYTE LenCMP );
void  SCHEMA_EXPORT  DeleteIdentType( int Num, int Type );

void  SCHEMA_EXPORT  RigidType( RIGID_STR & RS, BYTE &Type );

void  SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control );
void  SCHEMA_EXPORT  Add( DATA_RIGID &DR, int Quantity, int NumNew[] );
int   SCHEMA_EXPORT  Add( DATA_RIGID &DR, int Num, int Qnt, int NumNew[] );

void   SCHEMA_EXPORT Export( int NumDoc, FILEPRINT &Work );

int    SCHEMA_EXPORT Compare( int Num1, int Num2 );
void          ReadOld( void *, FILEBASE &FilePrj, DOCUMENT &Doc, OBJECT_STRING &OS );
void          WriteOld( FILEBASE &FileWork, DOCUMENT &Doc, OBJECT_DATA &Foundation, OBJECT_STRING &OS );
void          WriteOld( FILEBASE &FileWork, DOCUMENT &Doc, OBJECT_STRING &OS );

void  SCHEMA_EXPORT  CopyRigidIdent( int Num, IDENTIFICATOR &ID );

//     старье
int                   GetQuantityRigid() {  return Quantity;  }
int   SCHEMA_EXPORT   Include(BYTE Tp, int QntRgd,TYPE_DATA_SF *, int Qnt, int *Lst );
int   SCHEMA_EXPORT   ChangeType( int Num, BYTE Tp, int QntRgd, TYPE_DATA_SF *, int Qnt=0, int *Lst=NULL );
int   SCHEMA_EXPORT   ChangeIdent( int Num, BYTE LenCMP, int QntRgd, TYPE_DATA_SF * );               //   устаревшее
void  SCHEMA_EXPORT   GetIdent( int Num, char Ident[],  BYTE LenCMP, int &QntRgd, TYPE_DATA_SF ** ); //   устаревшее

SCHEMA_EXPORT  RIGID_LIST_OLD *  GetRigid( int Num );
void  SCHEMA_EXPORT   GetRigid( int Num, BYTE &Tp, int &QntRgd, TYPE_DATA_SF **pRgd, int &Qnt, int **Lst );

};

struct UG {  char Name[8]; char p; BYTE i;  };  //  Вспомогательная структура для местных систем координат

SCHEMA_EXPORT  BYTE   RigidCorner( int TypeRigid, LPCSTR Name );
SCHEMA_EXPORT  BYTE   RigidCornerNapr( int TypeRigid, LPCSTR Name );
SCHEMA_EXPORT  UG   * RigidCorner( BYTE Type );
SCHEMA_EXPORT  UG   * RigidCornerNapr( BYTE Type );
void  SCHEMA_EXPORT   TypeRigid( IDENTIFICATOR &ID, int QuantityRgd, int ListId[], BYTE &Type );

#pragma pack(pop)
#endif
