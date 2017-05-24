#ifndef PROFILE_FLAG_H
#define PROFILE_FLAG_H
#pragma pack(push, 1)

#define MAX_SECTION_NAME     100
#define MAX_STRING_NAME       21
#define MAX_QUANTITY_GRAF    100

#include <classwin.h>
#include <sysunits.h>
#include <proffull.h>

struct GRAF {
	 char  Name[MAX_STRING_NAME];  /*  идентификация стpоки       */
    BYTE  Mask;
	 float Coef[1];               /*   содеpжимое                */
	 };

struct SECTION {

	 BYTE    Group;           /*   номеp гpуппы                  */
	 char    NameFile[9];     /*   имя  файла                    */
	 BYTE    QuantityGraf;    /*   число граф                    */
    BYTE    TypeInGroup;
	 WORD    QuantityString;  /*   число строк                   */
    WORD    LengthNamePrint;

	 char ** Name;            /*   имя  сечения                  */
	 BYTE  * TypeGraf;        /*   типы  граф                    */
	 BYTE  * GrafPrint;       /*   Номера граф печати;           */
	 LPSTR * NameGraf;        /*   Имена  граф печати;           */

    LPSTR   Graf;

	 };

class PROFILE : private MEMORY {

private:
         BYTE            QuantityLanguage;
	      BYTE            QuantityTypeGraf;       /*   число типов граф              */
	      WORD            QuantityTypeSection;    /*   число различных сечений       */
         BYTE            TypeBase;               /*   Тип базы: 0 - рус. ( швеллер вертикально)       */
                                                 /*             1 - франц.  ( швеллер горизонтально ) */
         BYTE            Res[3];
         float           E;
         float           nu;
         float           ro;

         char            NameBase[9];
         WORD            NumLanguage;
         char         ** Name;
         char            NameFile[MAXPATH];

         UNITS         * UnitGraf;
         UNITS           UnitOutM;
         UNITS           UnitOutT;
         UNITS           UnitOutS;
         UNITS           UnitOutPL;
         UNITS           UnitOutRes1;
         UNITS           UnitOutRes2;

         WORD            QuantityMask;
         DWORD         * PosMask;
         BYTE          * BufMask; 

         DWORD           LenMaskData; 
         BYTE          * MaskData;

         STRING_PROFILE  FullInfo;

	      SECTION       * Section;

void EXPORT    Init();

void  SectionUser ( int Num, float RdSize, TYPE_DATA_SF  *f, int QuantityDbl, BYTE & Control );

void  RodSection00( float rodsize, int QuantityDbl, TYPE_DATA_SF *f, BYTE & Control );
void  RodSection01( float rodsize, int QuantityDbl, TYPE_DATA_SF *f, BYTE & Control );
void  RodSection02( float rodsize, int QuantityDbl, TYPE_DATA_SF *f, BYTE & Control );
void  RodSection03( float rodsize, int QuantityDbl, TYPE_DATA_SF *f, BYTE & Control );
void  RodSection04( float rodsize, int QuantityDbl, TYPE_DATA_SF *f, BYTE & Control );
void  RodSection05( float rodsize, int QuantityDbl, TYPE_DATA_SF *f, BYTE & Control );
void  RodSection06( float rodsize, int QuantityDbl, TYPE_DATA_SF *f, BYTE & Control );
void  RodSection07( float rodsize, int QuantityDbl, TYPE_DATA_SF *f, BYTE & Control );
void  RodSection08( float rodsize, int QuantityDbl, TYPE_DATA_SF *f, BYTE & Control );
void  RodSection199( int QuantityDbl, TYPE_DATA_SF  *f, BYTE & Control );

void  ClearString();

public:

	 PROFILE() { Init(); };
	 PROFILE(LPCSTR FileName, int Language = 0 ) { Init(FileName,Language); };
	 ~PROFILE() {   Delete();  };

int    EXPORT        Init(LPCSTR FileName);
int    EXPORT        Init(LPCSTR FileName, int Language );
void   EXPORT        Delete();

inline LPSTR         GetNameBase()  { return NameBase; };
inline LPSTR         GetNameFile()  { return NameFile; };
inline int           GetTypeBase()  { return TypeBase; };
LPSTR  EXPORT        GetName( int NumLanguage=0 );
LPSTR  EXPORT        GetNameSection( int NumPP );
LPSTR  EXPORT        GetNameSection( LPSTR NameFile );
LPSTR  EXPORT        GetNameFileSection( LPCSTR Name );
int    EXPORT        GetNumSection ( LPCSTR Name,  BYTE TypeName=0 );

BYTE   EXPORT        GetGroupSection( int NumPP );
BYTE   EXPORT        GetGroupSection( LPCSTR name, BYTE TypeName=0 );

int    EXPORT        GetQuantityString( int NumPP );
int    EXPORT        GetQuantityString( LPCSTR name, BYTE TypeName=0 );

LPCSTR EXPORT        GetStringName( LPCSTR Name, int NumString, BYTE TypeName=0 );
LPCSTR EXPORT        GetStringName( int NumPP, int NumString );

void                 Code(LPCSTR NameInput, LPCSTR NameOutput );

EXPORT void          SetUnit( UNITS &M, UNITS &S, UNITS &T );
EXPORT void          SetUnitAdd( UNITS &PL );

inline int           GetQuantityTypeSection()  { return QuantityTypeSection; };

EXPORT void          SetLanguage ( int Language );

EXPORT void          GetNamePrintSection( LPCSTR name,
                     int &Quantity, BYTE *Num, UNITS *, BYTE TypeName=0 );
EXPORT float  *      GetPrintString( LPCSTR name, int NumString, BYTE TypeName=0 );

EXPORT STRING_PROFILE * GetInform( TYPE_DATA_SF *f, int Quantity, BYTE &Control );

EXPORT STRING_PROFILE *  GetString( LPCSTR name, int NumString, BYTE TypeName=0 );
EXPORT STRING_PROFILE *  GetString( int NumPP, int NumString);

EXPORT void   PROFILE::AddElast( STRING_PROFILE *pSP );

EXPORT STRING_PROFILE * GetPrivateString( int NumString );
EXPORT int              SetPrivateString( STRING_PROFILE * );
EXPORT int              ChangePrivateString( int NumString, STRING_PROFILE * );
EXPORT void             DeletePrivateString( int NumString );

EXPORT float            GetE();
inline  float           GetNU()  { return nu;  };
EXPORT float            GetRO();

int    inline    GetQuantityMask() {  return QuantityMask;  };

void             InitMask();
EXPORT LPSTR     GetNameMask( int NumPP );
EXPORT void      SetMask( int NumPP );
EXPORT void      DeleteMask( int NumPP );
EXPORT int       AddMask( LPSTR Name, int Reg=1 );
EXPORT void      ChangeMask( int NumPP, LPSTR Name );
EXPORT int       YesModifyMask( int NumPP );


EXPORT SECTION FAR *    GetSection( LPCSTR Name, BYTE Type=0 );

EXPORT float * GetGraf( LPCSTR name, int NumString, BYTE TypeName, int NumGraf, LPSTR UnitsGraf );

};

int   ReadProfString( FILETEXT &Inp, LPSTR Buf, int &LenBuf );
int   ReadProfWord( FILETEXT &Inp, LPSTR Buf, int &LenBuf );

EXPORT int   GetNameProfile( LPCSTR FileName, LPSTR Buf, int Language=0 );

#pragma pack(pop)
#endif
