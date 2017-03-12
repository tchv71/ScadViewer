#ifndef IDENTIFICATOR_FLAG_H
#define IDENTIFICATOR_FLAG_H
#pragma pack(push,1)

#include "classwin.hpp"
#include "ObjectFile.hpp"

struct IDENT_STR
{
       LPSTR          Text;

       int            Quantity;
       double       * Data;

       int            LengthInf;
       void         * DataInf;

       BYTE           Type;
       BYTE           Comment;
       WORD           NumFile;
       BYTE           Res[4];
};

struct BASE_PROF { LPSTR Name;  LPSTR Section;  WORD NumStr;  int Quantity; double *Data; };

class IDENTIFICATOR : public SCAD_BASE_CLASS
{

public:
       OBJECT_FILE *  ListFile;

 	IDENTIFICATOR()      {  Init(); }
  ~IDENTIFICATOR(void)  {  Destroy();  }

void  SCHEMA_EXPORT  Init() {   SCAD_BASE_CLASS::Init(0,0,8,8,2,20);  LenData[0] = sizeof(double);  }

void          SetListFile(OBJECT_FILE * LF) {  ListFile = LF; }

int   SCHEMA_EXPORT  Add( LPSTR Ident, int Qnt, double *Data, BYTE Type=0 );

void  SCHEMA_EXPORT  Get( int Num, LPSTR *Ident, int *Qnt, double **Data, void ** );


int   SCHEMA_EXPORT  Add( LPSTR NameFile, LPSTR Name, int Qnt, double *Data, BYTE Type, int &Code  );
void  SCHEMA_EXPORT  Add( IDENTIFICATOR &Ident, int NewNum[]);
int   SCHEMA_EXPORT  Add( IDENT_STR &IS ) {  return AddObject((OBJECT*)&IS);  }
int                  Add( IDENT_STR &IDS, OBJECT_FILE &LF );

void  SCHEMA_EXPORT  Add( LPSTR StrInp, DWORD LenStr, BYTE &Control );

IDENT_STR *   Get(int Num) { return (IDENT_STR*)GetObject(Num);  }

void  SCHEMA_EXPORT  Get(int Num, int &Qnt, double ** );

int   SCHEMA_EXPORT  SetBase(LPSTR Name, LPSTR String, int NumStr, int Qnt=0, double *Dbl=NULL );

void  SCHEMA_EXPORT  Compress( int ** NewNumber );

int   SCHEMA_EXPORT  Compare( int Num1, int Num2 );

SCHEMA_EXPORT IDENT_STR * GetIdentType( int Type, int Qnt=0, int *Num =NULL, int NumPP=0 );

void  SCHEMA_EXPORT  IDENTIFICATOR::Copy( IDENTIFICATOR *pID );

};

SCHEMA_EXPORT  BASE_PROF * GetBaseInform( IDENT_STR &Ident, BYTE &Control );

// типы идентификаторов:
//          0 - текст с  double
//         11 - пользовательское сечение
//         12 - S199 данные из конструктора
//         21 - база сечений
//         22 - спаренное сечение
//         31 - конструктор сечений
//         41 - материал

#pragma pack(pop)
#endif

