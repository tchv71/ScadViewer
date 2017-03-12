#ifndef INPUT_FLAG_H
#define INPUT_FLAG_H
#pragma pack(push,1)

#include  "schema.hpp"
#include  "SystemCoord.hpp"
#include  "inp_data.hpp"
#include  "InputOldDoc.h"
#include  "fe_form.h"

struct RECORD {
       BYTE   Control;
       int    Num;
       int    NumDocument;
       int    NumStrDocument;
       int    PosString;
       };

struct TEXT_LENGTH {
   int Length;  char Text[1024];
   FILEPRINT *Print;
};

class  INPUT : public MEMORY {

public:

   SCHEMA   *  _Schema;
   int         QuantityNode;
   int         QuantityElem;

   int         MaxQuantityStrDoc;
   int         MaxLengthBuffer;
   int         ImportRigidOld;

   FILEBASE    Work;
	MESSAGE     Message;
	FILEPRINT   Print;
   FILEWORK    Form;

   BOOL    (*SetPercent) (int);

   BYTE        YesDoc[MAX_DOCUMENT];
   DOCUMENT    Document[MAX_DOCUMENT];

   RECORD      Record;
   int         NumStrDoc;
   LPSTR       TextInp;
   DWORD       LenTextInp;
   DWORD       PosTextInp;

   LPSTR       InpBuffer;
   LPSTR       WordBuffer;
   LPSTR       OutBuffer;

   int         NumInputLoad;
   int         NumInputLoadGroup;

   DOCUMENT    StrDoc[MAX_DOCUMENT];
   BYTE        YesStringHead[MAX_STRING_HEAD];
   BYTE        CheckStringHead[MAX_STRING_HEAD];

   char        StepName[16][5];

	BYTE      * SizeGraf;
	BYTE     ** StructDocument;

	BYTE        OrderStep[20];     // TypeStep[NSW(i)]
	BYTE        nxyz[3];

   PRINT_DATA  PrintData;
   double      EpsCheckFE;

	short      ValuePercent;
	short      DeltaPercent;

   long    *  NumUnknown;

	INPUT_DATA FormatHead;

	LPSTR      IZ;

//   BYTE       TypeConvert;

   float      RotorShell;

   OBJECT_STRING NameLoad;
   OBJECT_STRING NameLoadGroup;

   OBJECT_LIST   ChangeElem;
   OBJECT_LIST   DeleteElem;             //  флаги удаление
   OBJECT_LIST   DeleteNode;

   SYSTEM_COORD  SysCoord;
   STEEL_DATA    SteelData;

   OBJECT_STRING NameGroupNode;
   OBJECT_STRING NameGroupElem;

   OBJECT_STRING NameImpuls;              //  для старого вариантв
   OBJECT_STRING NameRigid;               //  для старого вариантв
   OBJECT_STRING NameSection;             //  для старого вариантв
   OBJECT_LIST   Dynamic35;               //  для старого вариантв стр.35
   
   double        End;

public:

	INPUT()     {  Init();   }
  ~INPUT(void) {  Delete(); }

void  SCHEMA_EXPORT Delete();

void         CoordSystem(void);

void         ContactCheck(DOC05 *doc05,int QuantityString,BYTE *YesNodeSE );
void         ContactNullFE( int *NumNode);
void         ContactNumber( int *NumNode, long *NumUnknown );
void         ContactOrder( int  *NumNode);
void         ContactSE( int *NumNode);

void         ConvertJointOld();
void         ConvertBoundOld();

void         DocumentPrint( int NumDoc, int NumInfName, int NumInfHead, int NumInfFormat,LPCSTR FieldDoc,DWORD LengthDoc, BYTE RegPrint, int NumBegin );
void         ElementChange();

int          Foreword( LPCSTR NameInp, LPCSTR NameOut, int TypeEdit, PARAM_PRINT & );
int          ForewordOld( LPCSTR NameInp, LPCSTR NameOut, int TypeEdit, PARAM_PRINT & );
void         ForewordEnd();

int          Format(SCHEMA &Schm, int TypeEdit );
void         FormatBegin( int TypeEdit );
int          FormatBase();
void         FormatContact();

void         FormatUnicum();

void SCHEMA_EXPORT  Init();
void         InitLib( int TypeEdit, PARAM_PRINT &ParamPrint, BYTE Regime );
void         InputData();
void         InputDataOld();
int          InputString(LPSTR OutString, LPSTR Separate);
void         InputAddCoord( int LenSent, BYTE &Control );
//void         InsertPrint( OBJECT_INSERT &Insert, int NumInfName, int NumInfHead );
void         InputLoadOld( SCAD_LOAD_LIST &, int NumDoc );
void         Head();

void         MessageLoad( 	  int Num, RESURCE_INFORM &Inf );
void         ModifyDoc8(DOC08 *doc08, int QntStr );

void         PrintNameDocument();

void         PrintHeadPage(void *);
void         PrintHeadDoc( );

void         PrintHead( int NumStrDoc, LPCSTR Sent, DWORD LenSent );
void         PrintHeadSchema();
void         PrintHeadSchema( int NumStr, OBJECT_LIST &Bnd, BYTE Type );
void         PrintHeadSchema( int NumStr, OBJECT_DATA &Ins );
void SCHEMA_EXPORT  Printing( SCHEMA &Schm, int TypeEdit, PARAM_PRINT &ParamPrint, BYTE *FlagPrintDoc=NULL );


void         PrintCoordContact();
void         PrintCorner();
void         PrintCornerNapr();
void         PrintPasternakFoundation();
void         PrintJoint();
void         PrintInsert();
void         PrintElem();
void         PrintSteelUni();

void         PrintEndDoc( );
void         PrintFormat( int NumInform);
void         PrintFormat( int NumInform, void FAR *Field, int LenField);
void         PrintFormatByte( int NumInform, BYTE b);
void         PrintFormatList( int NumInform,double *s, int QuantityDbl);
void         PrintFormatList( int NumInform, int NumInformNext,BYTE QuantityDblString,double *s, int QuantityDbl);
//void         PrintFormatList( int NumInform, PLACE *str,double *s);
void         PrintFormatEnd( int NumInform );
void         PrintList( int NumText, int Quanity, int List[], int SetBoard=10 );
void         PrintListDouble( int NumText, int Quantity, double Data[], int SetBoard );
void         PrintRigid( int NumDoc, DATA_RIGID & );
void         PrintRigidRod( int Num, double * );
void         PrintRigidPlate( int Num, double *, int kg );
void         PrintRigidVolume(int Num, double * );
//void         PrintRigidSE( int Num, double *,int);
void         PrintRigidMG( int Num, double *,int);
//void         PrintRigidSPB( int Num, double *,int);
void         PrintRigidOSD( int Num, double * );
void         PrintLoad( int NumDoc, SCAD_LOAD_LIST &LL );
void         PrintLoadForce( int Type, SCAD_FORCE &SF, int &Num );
void         PrintMass();
void         PrintSteel();
void         PrintSystemCoord( int NumDoc );

int          ReadStepString( LPSTR Sent, int LenSent );
int          ReadString3( LPSTR Sent, int LenSent );
void         ReadReplaseString( int &LenSent, DWORD &PosSent, LPSTR Word, int Repl[3], int Qnt, BYTE &Control );
void         Repeat(void);

void         RigidAdaption( DATA_RIGID &WorkRigid, int Type, OBJECT_STRING *NameRigid =NULL );
void  SCHEMA_EXPORT RigidFormat( int NumEl, int NumDoc, DATA_RIGID &WorkRigid, int NumRgd, int &kD, double *pD, BYTE &Control, BYTE &ContrType );
void         RigidMG( int NumEl, int NumDoc, DATA_RIGID &WorkRigid, int NumTypeRigid, int NumElem, int QuantityIdentn, IDENT_STR **pIdent, double *DblOut,int & QuantityDblOut,BYTE & Control);
void         RigidPlate( int NumEl, int NumTypeRigid, int QuantityIdentn, IDENT_STR **pIdent, double *DblOut,int & QuantityDblOut,BYTE & Control);
void         RigidPlateControl( int NumTypeRigid,double *DblOut, BYTE &Control);
void         RigidRod( int NumEl, int QuantityIdentn, IDENT_STR **pIdent, double *DblOut,int & QuantityDblOut,BYTE & Control);
//void         RigidSuperFE(int NumDoc, DATA_RIGID &WorkRigid, int NumTypeRigid,int NumElem, int QuantityIdentn, IDENT_STR **pIdent, double *DblOut,int & QuantityDblOut,BYTE & Control);
void         RigidVolume( int NumEl, int NumTypeRigid, int QuantityIdent, IDENT_STR **pIdent, double *DblOut,int & QuantityDblOut,BYTE & Control);
void         RigidVolumeControl( int ntg,double *s,BYTE & knt);
//void         RigidSPB(int NumDoc, DATA_RIGID &WorkRigid, int NumTypeRigid,int NumElem, int QuantityIdentn, IDENT_STR **pIdent, double *DblOut,int & QuantityDblOut,BYTE & Control);
void         RigidOSD(  int NumEl, int QuantityIdentn, IDENT_STR **pIdent, double *DblOut,int & QuantityDblOut,BYTE & Control);

void         Sentence( int NumDoc, LPCSTR Sent, int &LenSent, LPSTR Out, int &LenOut,BYTE &Control);
void         SentenceHead( LPSTR Sent, int Len );
void         SentenceHeadOld( LPSTR Sent, int Len );
void         SentenceLoad( int &Num, SCAD_LOAD_LIST &LL, int LenSent, BYTE &Control );
void         SentenceLoadInf( int Type, SCAD_LOAD_LIST &LL, int LenSent, BYTE &Control );
void         Sentence16( DWORD LenSent, BYTE & Control );
void         SentenceFund( DWORD LenSent, BYTE & Control );
void         SentenceFundOld( DWORD LenSent, BYTE & Control );
void         SentenceStabil( LPSTR BUF, DWORD LenSent, BYTE & Control );
void         SentenceLitera( LPSTR Sent, DWORD LenSent, BYTE & Control );

void         SentenceDinamicOld( LPSTR Sent, DWORD LenSent, int &LenOut, BYTE & Control );

inline  void SetPercentFunc( BOOL Func(int) ) {  SetPercent = Func;   }
void         SetPrintData(int NumName, int NumHead, int Reg=0 );


int          Title( LPCSTR NameInp, LPCSTR NameOut, int TypeEdit, PARAM_PRINT &, int Type=1 );
void         TitleDocument();
void         TitleDocumentOld();
void         Unroll( int NumDoc,LPSTR DocInp, DWORD LenInp, LPSTR DocOut, BYTE & Control);
void         SentenceCoordLine( WORD NumStr, LPSTR Sent, DWORD LenSent, LPSTR Out, BYTE & Control );

/*
void    ContactCheck(DOC05 *doc05,int QuantityString,BYTE *YesNodeSE );
void    ContactNullFE(WORD *NumNode);
void    ContactNumber(WORD *NumNode, long *NumUnknown );
void    ContactOrder(WORD  *NumNode);
void    ContactSE(WORD *NumNode);
int     Check(HWND hwnd,HINSTANCE hInst, short TypeEdit, LPSTR FileName);
void    CheckDyn();

void    CheckInf();
void    CheckNonlinear(void);
void    CheckSchema(void);

void    DocumentAdd(void);
//void    DocumentAddFunc( TDSTR *ni ...);
void    DocumentEnd(short &NumDoc,WORD &NumStrDoc, char cc);
void    DocumentPrint( short NumDoc, WORD NumInfName, WORD NumInfHead,WORD NumInfFormat,LPCSTR FieldDoc,DWORD LengthDoc, BYTE RegPrint, WORD NumBegin);
void    DocumentPrintLong(short NumDoc,short QuantityInt,short NumInfName,short NumInfHead,long Length,LPSTR Doc);
void    DocumentPrint16(long Length,LPSTR Doc);

void    Force(void);
void    ForceCheck(int QuantityStrDoc06, DOC06 *, int QuantityStrDoc07, DOC07 *, DOC07_POS * , int Type );
void    ForceSysHead(int QuantityStrDoc06, DOC06 *, float *Frc, DOC07_POS * );
void    ForewordMiddle(HWND hwnd, HINSTANCE hInst, short TypeEdit );


void    ImportContact(void);
void    ImportElement(void);
void    ImportDynamic(void);
void    ImportForce(int QuantityStrDoc06, DOC06 *, float *Frc, DOC07_POS *, int Type );
void    IncludeControl( WORD NumDefine,LPCSTR NameDefine);

//void SCHEMA_EXPORT  Init() { memset(this,0,sizeof(INPUT)); }
void    InputData();
int     InputHeadRead(LPSTR OutString,BYTE &LenString);


void    InsertPrint( INSERT &Insert, WORD NumInfName, WORD NumInfHead );

void    Head();
void    HeadString05( int LevelPrint,BYTE FAR * SignPrint);
//void    HeadString15(STRUPR *String,short Quantity);
void    HeadString28(WORD *NumNode);
void    HeadSrting33(void);
void    HeadString34(void);
void    HeadString36(BYTE *YesNodeSE);
void    HeadString38(void);
void    HeadString39(int Type);
void    HeadTable(void);

//void    ListTypeA(short NumString,short NumRegime,STRUPR *,short Begin,short End,BYTE FAR *kz, int MaxPos,BYTE & Control);
//void    ListTypeB(short ns,STRUPR *,short Quantity, int maximum,BYTE *Control);
//void    ListTypeC(short NumString, STRUPR *, int End,BYTE FAR *kz, int MaxPos,BYTE & Control );

void    MessageLoad(WORD Num, RESURCE_INFORM * );




void    PrintCoordContact(char *RegPrnt);
void    PrintForce( BYTE YesPrint[] , int Type );
void    PrintForce( int Type, DWORD QuantityStr, DOC06 *doc06, DATA_LOAD &DtLd );

void *  ReadDocument(DOCUMENT &);

void    RigidInput(void);
void    SCHEMA_EXPORT RigidFormat( int NumElem, WORD &kD,double *pD, BYTE &Control );


void    SchemaInFormat(HWND hwnd, HINSTANCE hInst, LPCSTR FileNameFormat, WORD LenBuf, short TypeEdit );
void    SentenceLong( short NumDoc, WORD NumStr, LPSTR Sent, DWORD LenSent, LPSTR Out, DWORD & LenOut, DWORD mem, BYTE & Control );
void    Sentence16( WORD NumStr, LPSTR Sent, DWORD LenSent, LPSTR Out, DWORD & LenOut, BYTE & Control );
void    SentenceFund( int NumStr, LPCSTR Sent, DWORD &LenSent, BYTE &Control);
void    SentenceRSN( WORD NumStr, LPSTR Sent, DWORD LenSent, LPSTR Out, DWORD & LenOut, BYTE & Control );
void    SentenceStabil( WORD NumStr, LPSTR Sent, DWORD LenSent, LPSTR Out, DWORD & LenOut, BYTE & Control );
void    SentenceLitera( WORD NumStr, LPSTR Sent, DWORD LenSent, LPSTR Out, DWORD & LenOut, BYTE & Control );
void    SentenceSteel( WORD NumStr, LPSTR Sent, DWORD LenSent, BYTE & Control );
void    SentenceSteelRigid( LPSTR Sent, DWORD LenSent, BYTE & Control );
void    WriteRSN();
//void    SentenceStabil( WORD NumStr, LPSTR Sent, DWORD LenSent, LPSTR Out, DWORD & LenOut, BYTE & Control );
//void    SentenceLitera( WORD NumStr, LPSTR Sent, DWORD LenSent, LPSTR Out, DWORD & LenOut, BYTE & Control );

void    WriteDocument(void *Buffer,DWORD LengthBuffer,DOCUMENT &);



private:
int     ReadAksel( WORD NumStr, LPCSTR NameAxs, float &Mastab, float &Time, float &DeltaTime, float **Value );
*/
};

//#define Schema         _Schema[0]
#define NXYZ(i)        nxyz[i]


int  SCHEMA_EXPORT ForewordInput( BOOL (*)(int),
       LPCSTR NameInp, LPCSTR NameOut, LPCSTR WorkCatalog,
       int TypeEdit,  PARAM_PRINT &ParamPrint,
       int &QnttErr, int &QnttWr, int Type=0 );

int  SCHEMA_EXPORT  Format( SCHEMA &Schm, short TypeEdit, BOOL Func(int) );
void SCHEMA_EXPORT  Printing( SCHEMA &Schm, int TypeEdit, PARAM_PRINT &ParamPrint, BOOL Func(int) );
void    CoordSystemWork( CK *ck, int NumSysCoord, double *ParamSysCoord,BYTE &Control);

void    ForceSysType(CK *ck,double f[3],char NumSysCoord, double ParamSysCoord[10]);

void    HeadPrintHead(void*);

void    PrintEndDocEntry(void*);
void    PrintHeadEntry(void *);
/*
void    RigidFormat( SCHEMA &, BYTE Type, WORD Quantity, TYPE_DATA_SF *,WORD &kD,double *pD, WORD QuantityErr, WORD NumErr[] );
void    RigidMG( SCHEMA &, WORD QuantityStructRgd,INFRGD *infrgd,double *DblOut,WORD & QuantityDblOut, WORD QnttErr, WORD NumErr[] );
void    RigidPlate( SCHEMA &, WORD QuantityStructRgd,INFRGD *infrgd,double *DblOut,WORD & QuantityDblOut, WORD QnttErr, WORD NumErr[] );
void    RigidRod( SCHEMA &,WORD QuantityStructRgd,INFRGD *infrgd,double *DblOut,WORD & QuantityDblOut, WORD QnttErr, WORD NumErr[] );
void    RigidSuperFE( SCHEMA &, WORD QuantityStructRgd,INFRGD *infrgd,double *DblOut,WORD & QuantityDblOut, WORD QnttErr, WORD NumErr[] );
void    RigidVolume( SCHEMA &, WORD QuantityStructRgd,INFRGD *infrgd,double *DblOut,WORD & QuantityDblOut, WORD QnttErr, WORD NumErr[] );
void    RigidNonLinear( SCHEMA &,WORD NumTypeRigid,LPCSTR Text, WORD QuantityStructRgd,INFRGD *infrgd,double *DblOut,WORD & QuantityDblOut,BYTE & Control,short & nztype);

*/
void    RigidCopy(IDENT_STR *pIL, int QuantityStructRgd,void * Out,BYTE & Control,BYTE & Ind, BYTE TypeCopy );

#pragma pack(pop)
#endif
