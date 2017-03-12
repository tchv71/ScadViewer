#ifndef PROFILE_FLAG_H
#define PROFILE_FLAG_H
#pragma pack(push,1)

#define MAX_SECTION_NAME     100
#define MAX_STRING_NAME       21
#define MAX_QUANTITY_GRAF    100

#ifdef  PROFILE_EXPORTS
#define PROFILE_EXPORT __declspec(dllexport)
#else
#define PROFILE_EXPORT __declspec(dllimport)
#endif

#include <classwin.hpp>
#include <sysunits.h>
#include <proffull.hpp>

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

class PROFILE : public MEMORY {

public:
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

void PROFILE_EXPORT    Init();

void  PROFILE_EXPORT SectionUser ( int Num, float RdSize, double  *f, int QuantityDbl, BYTE & Control );

void  RodSection00( float rodsize, int QuantityDbl, double *f, BYTE & Control );
void  RodSection01( float rodsize, int QuantityDbl, double *f, BYTE & Control );
void  RodSection02( float rodsize, int QuantityDbl, double *f, BYTE & Control );
void  RodSection03( float rodsize, int QuantityDbl, double *f, BYTE & Control );
void  RodSection04( float rodsize, int QuantityDbl, double *f, BYTE & Control );
void  RodSection05( float rodsize, int QuantityDbl, double *f, BYTE & Control );
void  RodSection06( float rodsize, int QuantityDbl, double *f, BYTE & Control );
void  RodSection07( float rodsize, int QuantityDbl, double *f, BYTE & Control );
void  RodSection08( float rodsize, int QuantityDbl, double *f, BYTE & Control );
void  RodSection199( int QuantityDbl, double  *f, BYTE & Control );

void  PROFILE_EXPORT ClearString();

public:

	 PROFILE() { Init(); };
	 PROFILE(LPCSTR FileName, int Language = 0 ) { Init(FileName,Language); };
	 ~PROFILE() {   Delete();  };

PROFILE_EXPORT  int          Init(LPCSTR FileName);
PROFILE_EXPORT  int          Init(LPCSTR FileName, int Language );
PROFILE_EXPORT  void         Delete();

inline LPSTR         GetNameBase()  { return NameBase; };
inline LPSTR         GetNameFile()  { return NameFile; };
inline int           GetTypeBase()  { return TypeBase; };
PROFILE_EXPORT LPSTR         GetName( int NumLanguage=0 );
PROFILE_EXPORT LPSTR         GetNameSection( int NumPP );
PROFILE_EXPORT LPSTR         GetNameSection( LPSTR NameFile );
PROFILE_EXPORT LPSTR         GetNameFileSection( LPCSTR Name );
PROFILE_EXPORT int           GetNumSection ( LPCSTR Name,  BYTE TypeName=0 );

PROFILE_EXPORT BYTE          GetGroupSection( int NumPP );
PROFILE_EXPORT BYTE          GetGroupSection( LPCSTR name, BYTE TypeName=0 );

PROFILE_EXPORT int           GetQuantityString( int NumPP );
PROFILE_EXPORT int           GetQuantityString( LPCSTR name, BYTE TypeName=0 );

PROFILE_EXPORT  LPCSTR       GetStringName( LPCSTR Name, int NumString, BYTE TypeName=0 );
PROFILE_EXPORT  LPCSTR       GetStringName( int NumPP, int NumString );

void                 Code(LPCSTR NameInput, LPCSTR NameOutput );

PROFILE_EXPORT  void         SetUnit( UNITS &M, UNITS &S, UNITS &T );
PROFILE_EXPORT  void         SetUnitAdd( UNITS &PL );

inline  int          GetQuantityTypeSection()  { return QuantityTypeSection; };

PROFILE_EXPORT  void         SetLanguage ( int Language );

PROFILE_EXPORT  void         GetNamePrintSection( LPCSTR name,
                     int &Quantity, BYTE *Num, UNITS *, BYTE TypeName=0 );
PROFILE_EXPORT  float      * GetPrintString( LPCSTR name, int NumString, BYTE TypeName=0 );

PROFILE_EXPORT  STRING_PROFILE * GetInformOld( TYPE_DATA_SF *f, int Quantity, BYTE &Control );
PROFILE_EXPORT  STRING_PROFILE * GetString( LPCSTR name, int NumString, BYTE TypeName=0 );
PROFILE_EXPORT  STRING_PROFILE * GetString( int NumPP, int NumString);

void PROFILE_EXPORT  PROFILE::AddElast( STRING_PROFILE *pSP );

PROFILE_EXPORT  STRING_PROFILE * GetPrivateString( int NumString );
PROFILE_EXPORT  int              SetPrivateString( STRING_PROFILE * );
PROFILE_EXPORT  int              ChangePrivateString( int NumString, STRING_PROFILE * );
PROFILE_EXPORT  void             DeletePrivateString( int NumString );

PROFILE_EXPORT  float            GetE();
inline  float            GetNU()  { return nu;  };
PROFILE_EXPORT  float            GetRO();

int    inline    GetQuantityMask() {  return QuantityMask;  };

void             InitMask();
PROFILE_EXPORT  LPSTR    GetNameMask( int NumPP );
PROFILE_EXPORT  void     SetMask( int NumPP );
PROFILE_EXPORT  void     DeleteMask( int NumPP );
PROFILE_EXPORT  int      AddMask( LPSTR Name, int Reg=1 );
PROFILE_EXPORT  void     ChangeMask( int NumPP, LPSTR Name );
PROFILE_EXPORT  int      YesModifyMask( int NumPP );

PROFILE_EXPORT  int      GetMask( int NumSectPP, int NumString );

PROFILE_EXPORT  SECTION FAR *  GetSection( LPCSTR Name, BYTE Type=0 );

PROFILE_EXPORT  float * GetGraf( LPCSTR name, int NumString, BYTE TypeName, int NumGraf, LPSTR UnitsGraf );

};

int   ReadProfString( FILETEXT &Inp, LPSTR Buf, int &LenBuf );
int   ReadProfWord( FILETEXT &Inp, LPSTR Buf, int &LenBuf );

PROFILE_EXPORT  int   GetNameProfile( LPCSTR FileName, LPSTR Buf, int Language=0 );

#pragma pack(pop)
#endif
