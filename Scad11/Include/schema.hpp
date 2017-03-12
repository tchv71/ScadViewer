#ifndef SCHEMA_FLAG_H
#define SCHEMA_FLAG_H
#pragma pack(push,1)

#define MAX_DOCUMENT  	      200
#define MAX_TREE              300
#define MAX_SCHEMA_LOAD      1024
#define MAX_LENGTH_NAME_LOAD  511

#ifdef  SCHEMA_EXPORTS
#define SCHEMA_EXPORT __declspec(dllexport)
#else
#define SCHEMA_EXPORT __declspec(dllimport)
#endif

#include <classwin.hpp>
#include "Element.hpp"
#include "ObjectList.hpp"
#include "DataRigid.hpp"
#include "Insert.hpp"
#include "fragment.hpp"
#include "ScadLoadList.hpp"
#include "profile.hpp"
#include "steel.hpp"
#include "sysunits.h"
#include "SchemaStr.hpp"
#include "stepdata.h"
#include "SystemCoord.hpp"
#include "s_stabil.h"
#include "litera.h"
#include "scad_rsn.hpp"
#include "ObjectUnite.hpp"
#include "dataload.h"
#include "armatura.hpp"
#include "CoordLine.hpp"
#include "rsu.hpp"
#include "ScadHistory.hpp"
#include "ForceTime.hpp"
#include "ForumForce.hpp"
#include "destruction.hpp"

#include "body.hpp"

class SCHEMA : public MEMORY
{

public:

	char         *   Name;      //  Имя пpоекта
	char         *   Company;   //  Имя компании
	char         *   Customer;  //  Заказчик
	char         *   Object;    //  Объект
	char         *   Executor;  //  Исполнитель
	char             FileName[MAXPATH];      // Имя файла сxемы
	char             WorkCatalog[MAXPATH];   // Каталог для pаботы
	char             FileHistory[MAXPATH];       // Имя файла истории

    WORD             Version;
	TYPE_SYSTEM      TypeSystem;             // Тип сxемы

	UNITS            Units[5];               //  Система единиц
	WORD             TypeSchema;             // Тип сxемы генеpации


	WORD             QuantityCraneForce;     // Число кpановыx нагpузок
	WORD             QuantityBrakeForce;     // Число тоpмозныx нагpуз.

	TREE             Tree[MAX_TREE];         // Деpево pасчета

    int              QuantityElem;
    FORMAT         * pFormat;

	int              QuantityNode;           // Число узлов
	int              QuantityAllocNode;
	CK             * Coord;        // Кооpдинаты узлов
	GrafCK         * GrafCoord;    // Гpафические кооpдинаты узлов
	DefCK          * DCoord;       // Кооpдинаты узлов деф. сxемы
	GrafCK         * DGrafCoord;   // Гpаф. кооpд. узлов деф. сxемы

	WORD             NumLoadBuf;   // Номеp нагpужения в _Load

    PROFILE         _Profile;     // База сечений

    LOOK_BODY        Video;
    SCHEMA_PARAM     Param;
    SYSTEMTIME       TimeNull;

    BYTE             YesExportRepeat;

    BYTE             YesOrderNumber;   // Наличие ортов для нумерации
    double           OrderNumber[10];  // Порядок нумерации по ортам
    BYTE             YesPredForce;	   // наличие преднапряжения 

	BYTE             Modify;           // Пpиэнак модификации данныx
	BYTE             ModifyCalc;
	BYTE             ModifyAll[8];

    RESURCE_TEXT    _Resurce;

    int              QuantityStrDoc08;
    DOC08         *  Doc08;

    dlg_stab      *  StabilData;
    ltr_se        *  LiteraData;

    void            (*Progress)(int);
	
	BYTE            * WorkPoint;   //  используется при сортировке элементов
	BYTE              OldProject;  //  прочитан старый проект

    char            _Reserve1[252];

//*******************  КЛАССЫ ***************************************

    UNITE_SCHEMA      UniteSchem;
    ELEMENT          _Element;
	DATA_RIGID       _Rigid;        // жесткости

    OBJECT_FILE      _ListFile;
	SCAD_LOAD_LIST   _LoadList;     // Инфоpмация о нагpуженияx
	SCAD_LOAD_LIST   _LoadGroup;    // Инфоpмация о гpуппаx нагpужений
    OBJECT_DOUBLE    _Mass;         // Сбор масс в узлы
	SCAD_LOAD        _Load;         // Рабочее нагpужение

	OBJECT_LIST      _Bound;        // связи
	OBJECT_LIST      _Joint;        // шаpниpы
    OBJECT_LIST      _ElemEffors;   //  списки для вычисления усилий 
	OBJECT_LIST      _List[10];     //   см. schema.hlp
    OBJECT_LIST      _Contur;       // Запомненные контура
    OBJECT_LIST	     _Blocks;           //  Блоки в FORUMе

	INSERT           _Insert;       // ж/вставки
	OBJECT_DATA      _Corner;       // углы ж/x
	OBJECT_DATA      _CornerNapr;   // углы вычисления напpяжений
    OBJECT_DATA      _PasternakFoundation; //  упругое основание

    SYSTEM_COORD     _SystemCoord;  //   Местные системы координат узлов
    SYSTEM_COORD     _ForceCoord;   //   Местные системы координат нагрузок

    SCAD_STEP        _Step;
	
    FRAGMENT         _Fund;
    SCAD_RSN         _Rsn;

    STEEL            _Steel;
    DATA_RIGID       _SteelRigid;   // жесткости подбора сечений
    OBJECT_LIST      _SteelUni;     // унификация металла

    OBJECT_LIST      _NodeSE;       // номера узлов SE

    OBJECT_LIST      _Acceleration; // списки постпроцессора вычисления ускорений
//********************************************************************

    ARMATURA         _Beton;
    COORD_LINE       _CoordLine;

    SCAD_RSU_CLASS   _Rsu; 

	FORUM_FORCE      _ForumForce;
	FORCE_TIME       _ForceTime;
    DESTRUCTION      _Destruction;
	
	SCHEMA & operator = ( SCHEMA &Sch ) {
	   Copy(Sch);
	   return *this;	}

/*----------------Констpуктоpы и дестpуктоp -----------------*/

SCHEMA() {   Init();  };
~SCHEMA(void) {  Destroy(); }

void   SCHEMA_EXPORT   Init();
void   SCHEMA_EXPORT   Init(LPCSTR Catalog);
int    SCHEMA_EXPORT   Init( int QntElem, int QntNodeSchema, int TypeElem, int QntNodeElem );

void   SCHEMA_EXPORT   Destroy();
void   SCHEMA_EXPORT   Delete();
void            DeleteHelp();

int    SCHEMA_EXPORT   Read( LPCSTR Name, int Type=0 );
int                    ReadIn( LPCSTR Name, int Type=0 );

int    SCHEMA_EXPORT   ReadGeometry( LPCSTR Name );
int             ReadSchemaUnite( FILEBASE &FilePrj, DOCUMENT &Doc, int Type);
int    SCHEMA_EXPORT   Write(LPCSTR FileName);
int                    Write(LPCSTR FlName, LPSTR NameTMP );

void            ChangeSchema(SCHEMA &Schem);
void            ModifyListFile();

void            SetName(LPCSTR s)    {  SetVoid((void*)s,strlen(s)+1,(void**)&Name); }
inline LPSTR    GetName() {  if ( Name == NULL ) return "";  return Name;  }

void            SetCompany(LPCSTR s) {  SetVoid((void*)s,strlen(s)+1,(void**)&Company); }
inline LPSTR    GetCompany() {  if ( Company == NULL ) return "";  return Company;  }

void   SCHEMA_EXPORT   SetCustomer(LPCSTR s) {  SetVoid((void*)s,strlen(s)+1,(void**)&Customer); }
inline LPSTR    GetCustomer() {  if ( Customer == NULL ) return "";  return Customer;  }

void   SCHEMA_EXPORT   SetObject(LPCSTR s)   {  SetVoid((void*)s,strlen(s)+1,(void**)&Object); }
inline LPSTR    GetObject() {  if ( Object == NULL ) return "";  return Object;  }

void   SCHEMA_EXPORT   SetExecutor(LPCSTR s) {  SetVoid((void*)s,strlen(s)+1,(void**)&Executor); }
inline LPSTR    GetExecutor() {  if ( Executor == NULL ) return "";  return Executor;  }

inline TREE  *  GetTree() {  return Tree;  }
TREE         *  GetTree( int Num);
void            SetTree();
void   SCHEMA_EXPORT   SetTreeTime(int Num);
void            SetTree( int Num);

void   SCHEMA_EXPORT   FillTree();
void   SCHEMA_EXPORT   FillTreeFull(int Type=0);
int    SCHEMA_EXPORT   GetModify();

int    SCHEMA_EXPORT   Hasp();

public:

inline LPCSTR GetFileName() { return FileName;  }
inline void   SetFileName(LPCSTR Fl) {  strncpy(FileName,Fl,MAXPATH);  }

int    SCHEMA_EXPORT SetTypeSystem( int Num );
inline int    GetTypeSystem() {    return TypeSystem.Num;  }

inline void   SetTypeSchema( int ts) {  if ( ts ) TypeSchema = ts;  ModifyCalc = 1;  }
inline int    GetTypeSchema()        {  return TypeSchema; }

inline int    GetQuantityElem()      {  return QuantityElem;  }
inline int    GetQuantityNodeBody()  {  return Video.QuantityNodeBody;    }
inline int    GetQuantityNode()      {  return QuantityNode;      }
inline int    GetQuantityLoad()      {  return _LoadList.Quantity;      }

//--------------------- Параметры для ввода и расчета ---------
void  SCHEMA_EXPORT  SetTypeOptimization(BYTE Num);
BYTE  SCHEMA_EXPORT  GetTypeOptimization();
void  SCHEMA_EXPORT  SetPrecessionSolver(BYTE Prec);
BYTE  SCHEMA_EXPORT  GetPrecessionSolver();
void  SCHEMA_EXPORT  SetPrecessionDynamic(BYTE Prec);
BYTE  SCHEMA_EXPORT  GetPrecessionDynamic();
void  SCHEMA_EXPORT  SetCheckSolution(BYTE);
BYTE  SCHEMA_EXPORT  GetCheckSolution();
void  SCHEMA_EXPORT  SetUnitsOut( UNITS *Un );
void  SCHEMA_EXPORT  GetUnitsOut( UNITS *Un );

// Информаци

int   SCHEMA_EXPORT   JointElem( int NumElem, WORD &Mask1, WORD &Mask2);
void  SCHEMA_EXPORT   DataInFormat();

void  SCHEMA_EXPORT   DeleteLookBody();

FORMAT *       GetFormat(int NumFormat) {
                   if ( NumFormat < 1 || NumFormat > QuantityElem ) return NULL;
                   return &pFormat[NumFormat-1];  }

SCHEMA_EXPORT FORMAT * GetFormatFull( int NumFormat ); 

int   SCHEMA_EXPORT   AddElem( int Qnt=1 );
int   SCHEMA_EXPORT   AddElemList( int QnttElem, int QnttNode );

int   SCHEMA_EXPORT   AddElem( int TypeElem, int ListNode ...);
int   SCHEMA_EXPORT   AddElem( int Type, int QuantityNode, int *ListNode );
int   SCHEMA_EXPORT   UpdateElem( int NumElem, int TypeElem, int ListNode ...);
void  SCHEMA_EXPORT   UpdateElem( int Num, int Type, int QuantityNode, int *ListNode ) {  _Element.UpdateElem(Num,Type,QuantityNode,ListNode); }
void  SCHEMA_EXPORT   SetListTypeElem( int ElemBegin, int ElemEnd, int TypeElem );
void  SCHEMA_EXPORT   SetElemOneNode( int NumElem, int NumPP, int NumNode );
void           DeleteLastElement() {  _Element.Delete(_Element.Quantity);  }

int   SCHEMA_EXPORT   AddElemOrder( int TypeElem, int QuantityNode, int *ListNode, double del );
int   SCHEMA_EXPORT   CheckVolumeOrder( int NumElem );
int   SCHEMA_EXPORT   AddVolumeOrder( int TypeElem, int Quantity, int *List, double del );

int   SCHEMA_EXPORT   YesOrder( int NumElem, int *ListNode, double del );
int   SCHEMA_EXPORT   ElemSize( int n1, int n2, int n3, double s[3] );

void  SCHEMA_EXPORT   SetBitFlag( int NumElem, int NumFlag);
int   SCHEMA_EXPORT   GetBitFlag( int NumElem, int NumFlag);
void  SCHEMA_EXPORT   ClearFlag ( int NumElem, int NumFlag);
void  SCHEMA_EXPORT   ClearFlag ( int NumFlag);
void  SCHEMA_EXPORT   ClearFlag();

int   SCHEMA_EXPORT   AddNode( int Quantity );
int   SCHEMA_EXPORT   AddNode( CK *, int Quantity=1 ); // Return Beg Number
int                   AddNode( CK &ck ) {  return AddNode(&ck,1);  }
int                   AddNode( int Quantity, CK *ck  ) {  return AddNode(ck,Quantity);  }
void  SCHEMA_EXPORT   UpdateNode(int  NumNode,CK &, LPSTR Name="" );
void  SCHEMA_EXPORT   UpdateNode( int Begin, int Quantity, CK *, LPSTR Name="" ); // Return Beg Number
void  SCHEMA_EXPORT   DeleteLastNode(int);
inline CK     * GetCoord() { return Coord; }
SCHEMA_EXPORT  CK   * GetCoord(  int NumNode);
SCHEMA_EXPORT  double GetCoordX( int NumNode);
SCHEMA_EXPORT  double GetCoordY( int NumNode);
SCHEMA_EXPORT  double GetCoordZ( int NumNode);
inline void SetDCoordX( int NumNode,double x) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].x = x;  }
inline void SetDCoordY( int NumNode,double y) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].y = y;  }
inline void SetDCoordZ( int NumNode,double z) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].z = z;  }

LPSTR  SCHEMA_EXPORT  GetNodeName( int NumNode );
void   SCHEMA_EXPORT  SetNodeName( int NumNode, LPSTR Name );

int    SCHEMA_EXPORT   GetTypeElem(int Num );
int    SCHEMA_EXPORT   GetElemQuantityNode( int Num );
int    SCHEMA_EXPORT   GetElemNode( int Num, int k );
int    SCHEMA_EXPORT   GetElemTypeRigid( int Num );

void  SCHEMA_EXPORT   SetCoordX( int NumNode,double x);
void  SCHEMA_EXPORT   SetCoordY( int NumNode,double y);
void  SCHEMA_EXPORT   SetCoordZ( int NumNode,double z);
void  SCHEMA_EXPORT   ClearNode(int Num);

void  SCHEMA_EXPORT   SetNodeBitFlag( int NumNode, int NumFlag );
int   SCHEMA_EXPORT   GetNodeBitFlag( int NumNode, int NumFlag );
void  SCHEMA_EXPORT   ClearNodeFlag ( int NumNode, int NumFlag );
void  SCHEMA_EXPORT   ClearNodeFlag ( int NumFlag );
void  SCHEMA_EXPORT   ClearNodeFlag();

int   SCHEMA_EXPORT   AllocGrafCoord(void);
void  SCHEMA_EXPORT   AllocDCoord(int  NodeQuantity);
void  SCHEMA_EXPORT   AllocDGrafCoord(int  NodeQuantity);
void  SCHEMA_EXPORT   SetDCoordNUNK( int NumNode,int *NumSW, BYTE QuantitySW);
SCHEMA_EXPORT GrafCK *GetGrafCoord(int NumNode);
int   SCHEMA_EXPORT   GetGrafCoordX(int NumNode);
int   SCHEMA_EXPORT   GetGrafCoordY(int NumNode);
void  SCHEMA_EXPORT   SetGrafCoordX(int NumNode,int x);
void  SCHEMA_EXPORT   SetGrafCoordY(int NumNode,int y);

inline void SetDCoordUX(int NumNode,double ux) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].ux = ux;  }
inline void SetDCoordUY(int NumNode,double uy) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].uy = uy;  }
inline void SetDCoordUZ(int NumNode,double uz) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].uz = uz;  }
inline double GetDCoordX(int NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].x ;
	  return 0;  }
inline double GetDCoordY(int NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].y ;
	  return 0;   }
inline double GetDCoordZ(int NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].z ;
	  return 0;   }
inline double GetDCoordUX(int NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].ux ;
	  return 0;   }
inline double GetDCoordUY(int NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].uy ;
	  return 0;   }
inline double GetDCoordUZ(int NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].uz ;
	  return 0;   }
inline int * GetDCoordNUNK(int NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].n_unk;
	  return NULL;  }
inline void SetDGrafCoordX(int NumNode, int x) {
	  if ( --NumNode < QuantityNode ) DGrafCoord[NumNode].x = x;  }
inline void SetDGrafCoordY(int NumNode, int y) {
	  if ( --NumNode < QuantityNode ) DGrafCoord[NumNode].y = y;  }
inline int GetDGrafCoordX(int NumNode) {
	  if ( --NumNode < QuantityNode ) return DGrafCoord[NumNode].x ;
	  return 0;   }
inline int GetDGrafCoordY(int NumNode) {
	  if ( --NumNode < QuantityNode ) return DGrafCoord[NumNode].y ;
	  return 0;   }

int   SCHEMA_EXPORT   CompareSchem( SCHEMA &S2,int Level );
//  Загружени

double SCHEMA_EXPORT  ElemWeight( int Num );
void   SCHEMA_EXPORT  ReadLoadBuf( int NumLoad )      {  _LoadList.Read(NumLoad,_Load);  }
void   SCHEMA_EXPORT  ReadLoadGroupBuf( int NumLoad ) {  _LoadGroup.Read(NumLoad,_Load);           }
void   SCHEMA_EXPORT  WriteLoad( int NumLoad, LPSTR Name ) {  _LoadList.Write(NumLoad,Name,_Load);   }
void   SCHEMA_EXPORT  WriteLoadGroup( LPSTR Name )  { _LoadGroup.Write(_LoadGroup.Quantity+1,Name,_Load);  }

void   SCHEMA_EXPORT  AddLoad( int NumLoad, BYTE MaskQW=0xFF, double Coef=1 );
void   SCHEMA_EXPORT  AddLoadGroup( int NumLoadGroup, BYTE MaskQW=0xFF, double Coef=1 );

LPCSTR SCHEMA_EXPORT  GetLoadName( int Num ) {  return _LoadList.GetText(Num);  }
LPCSTR SCHEMA_EXPORT  GetLoadGroupName( int Num ) {  return _LoadGroup.GetText(Num);  }

void   SCHEMA_EXPORT  SetLoadName( int Num, LPSTR Text  ) {  _LoadList.SetText(Num,Text);  }
void   SCHEMA_EXPORT  SetLoadGroupName( int Num, LPSTR Text  ) {  _LoadGroup.SetText(Num,Text);  }

void   SCHEMA_EXPORT  DeleteZeroLoad();
void   SCHEMA_EXPORT  DeleteLoad( int NumPP );
void   SCHEMA_EXPORT  ClearLoad( int Num );
void   SCHEMA_EXPORT  DeleteLoadGroup( int Num );

void  SCHEMA_EXPORT   EqualForceElem( BYTE MaskQw=0xFF, BYTE MaskQn=0xFF );
void  SCHEMA_EXPORT   EqualForceNode( BYTE MaskQw=0xFF, BYTE MaskQn=0xFF );
void  SCHEMA_EXPORT   ForceElemDivide( int NumOld, int Quantity, int ListElem[] );
void           ForcePlateDivide( SCAD_LOAD_LIST &LL, int NumOld, int Quantity, int ListElem[] );
void           ForceRodDivide( SCAD_LOAD_LIST &LL, int NumOld, int Quantity, int ListElem[] );
void           ForceVolDivide( SCAD_LOAD_LIST &LL, int NumOld, int Quantity, int ListElem[] );

void  SCHEMA_EXPORT   LookBody( double * MK, BYTE TypeProfile, BYTE TypePlate );
void           ProfileInform( FORMAT &pF, int &kNode, int &kElem );
int            ProfileNode( double MK[9], DECART  *LookCoord, int NumElem, ELEM_BODY * pEB );
int            ProfileNode( STRING_PROFILE *pSP, double &Del, int NodeBase, int &kNode, int Type, double &Profile, double &z0 );
int            ProfileNodeConstr( int NumRigid, int &kNode, double &y0, double &z0, double &Del);
int            ProfileNodeConstrTonus( int NumRigid, int &kNode, double &y0, double &z0, double &Del);
int            ProfileNodeConstrConsul( int NumRigid, int &kNode, double &y0, double &z0, double &Del);

int            ProfileElem( int NumElem, float Eps, double MKR[], DECART  *LookCoord, ELEM_BODY  * pEB, int & );
int            ProfilePlate( double *MK,  ELEM_BODY * pEB, DECART  *LookCoord );
void           LookVolume( ELEM_BODY * pEB, DECART  *LookCoord, int &kElem );
void           LookProc( BODY_EQUIVALENT *VectorBody, double Eps, DECART  *LookCoord, int kG,  ELEM_BODY_FULL *, int  * NumBody, int TypeEnd );
int            LookInto( BODY_EQUIVALENT *VectorBody, double Eps, ELEM_BODY_FULL *, int ki, int Num[], int &kGr,  DECART  * LookCoord, int  *NumBody );

// tools
void           SetDocFile( DOCUMENT &, DWORD PosFile, DWORD DocLength);
void  SCHEMA_EXPORT   WriteDocument(FILEBASE &, void FAR *Buffer,DWORD LengthBuffer, DOCUMENT & );
LPSTR SCHEMA_EXPORT   ReadDocument( FILEBASE &, DOCUMENT & );
LPSTR          ConstructionFileName( LPCSTR File, LPCSTR Ext, BYTE Type );
LPSTR SCHEMA_EXPORT   ConstructionFileName(LPCSTR Ext);
LPSTR SCHEMA_EXPORT   ConstructionDataName(LPCSTR Ext);
LPSTR SCHEMA_EXPORT   ConstructionDataName(LPCSTR File, LPCSTR Ext);
void  SCHEMA_EXPORT   DeleteFile(LPCSTR Name[]);

int  SCHEMA_EXPORT    SchemaMatrCos( int NumElem, double *MatrCosOut, BYTE YesAlfa=1);
int  SCHEMA_EXPORT    SchemaMatrCos( int Quantity, int List[], double *MatrCosOut );

//=====================
void           SetLookBodyFragm( BYTE );
int   SCHEMA_EXPORT   LookRod( int NumElem, double CoordNode[3], double mk[9], double &AL , BYTE YesAlfa = 1 );
void           LookEqBody( std::vector<BODY_EQUIVALENT> &VectorBody, DECART  * LookCoord, ELEM_BODY_FULL  * EBF, double Eps );
int            ConturPlate( ELEM_BODY  * pEB, DECART  *LookCoord );
void           ConturPlate( ELEM_BODY  * pEB );

inline DWORD   QuantityElemBody() {  return Video.QuantityElemBody; };
inline ELEM_BODY * GetElemBody( int Num ) {
       if ( --Num < Video.QuantityElemBody ) return (ELEM_BODY*)&Video.ElemBody[Num];
       return NULL;   }
inline DWORD GetOrderElemBody( int Num ) {
       if ( --Num < Video.QuantityElemBody ) return Video.Order[Num];
       return 0;   }

void  SCHEMA_EXPORT  ExportVersion31( LPCSTR FileName );

void  SCHEMA_EXPORT  ExportText(LPCSTR FileName);
void          ExportHead(FILEPRINT &);
void          ExportCoord(FILEPRINT &Print, int YesRepl );
void          ExportLoad( int NumDoc, SCAD_LOAD_LIST &LL, FILEPRINT &Work );
void          ExportLoadForce( FILEPRINT &Work, int NumLoad, SCAD_FORCE &SF, int &Num );

void          CornerInfAdd(void *Input =NULL);
void          CornerNaprInfAdd(void *Input=NULL);
void          PasternakFoundationAddInf( void *Inp =NULL);

void SCHEMA_EXPORT   DeleteVoid( void **pV ) {   if ( *pV ) MemoryFree(*pV);   *pV = NULL;  }
void SCHEMA_EXPORT   SetVoid( void *Inp,  int Length, void ** );

void SCHEMA_EXPORT   SetStabilData( dlg_stab *pDS );
void SCHEMA_EXPORT   DeleteStabilData() {  DeleteVoid((void**)&StabilData);  }

void SCHEMA_EXPORT   SetLiteraData( ltr_se *LS );
void SCHEMA_EXPORT   DeleteLiteraData() {  DeleteVoid((void**)&LiteraData);  }

void SCHEMA_EXPORT   SetRSU(DOC08 *, int QuantityStr );
void SCHEMA_EXPORT   DeleteRSU();

//=======================================
void SCHEMA_EXPORT Compress( int YesFragment, int EqualElem, int EqualTypeElem, int EqualRigid,
   int TypeDeleteNode, int TypeDeleteNodeEq, int NodeUnion, double PrecesionCoincidence );

void    CompressElem( int YesFragment, int Type, int EqualTypeElem, int EqualRigid, int NumElem[] );
void    CompressNode( int YesFragment, int TypeDelete, int TypeDeleteEq, int NodeUnion, double PrecesionCoincidence, int NumNode[] );
void    CompressFile();

int    SCHEMA_EXPORT  Unite(LPSTR);
void   SCHEMA_EXPORT  DeleteUnite(int NumPP);
void   SCHEMA_EXPORT  ReadUnite(int);
inline int GetQuantityUnite() {  return UniteSchem.Quantity;  }
LPSTR  SCHEMA_EXPORT  GetNameUnite(int NumPP);

int   SCHEMA_EXPORT  MatrCosEffors( int NumElem, double *MatrCos );
int   SCHEMA_EXPORT  MatrCosElast( int NumElem, double *MatrCos );
int                  MatrCosOrt( int NumElem, double *MatrCos, int Type );

void  SCHEMA_EXPORT  Copy(SCHEMA &);

int  SCHEMA_EXPORT   ReadOld( FILEBASE &FilePrj, int Type );
void          ReadLoadOld( SCAD_LOAD_LIST &LL, FILEBASE &FilePrj, DOCUMENT &Doc );
void          ReadLoadOld( FILEBASE &FilePrj , SCAD_LOAD &SL, LPSTR Name);
void          ReadForceOld( FILEBASE &FilePrj, DATA_LOAD &DtLd, FORCE_GROUP &FrcGrp);
void          ForceOldConvert( DATA_LOAD &DtLd, FORCE_GROUP &FrcGrp, SCAD_LOAD &SL, int Type=0);
void          LoadOldConvert(FILEBASE &FilePrj, DOCUMENT Doc[], OBJECT_LIST &Dynamic34, OBJECT_STRING &ImpulsName );

void          LoadWriteOld ( FILEBASE &FileWork, SCAD_LOAD_LIST &SL, DOCUMENT *Doc, int NumDoc );
void          ForceWriteOld( FILEBASE &FileWork, SCAD_FORCE &SF, int Qnt, int BaseValue );

void   SCHEMA_EXPORT  HeadRSU( BYTE ** ElemRSU, BYTE ** ElemUnif, WORD **ListRSU1, WORD **ListRSU2);

void  SCHEMA_EXPORT  Draw(HWND,int,int);
void  SCHEMA_EXPORT  Draw(HWND,int,int,int,int);
void  SCHEMA_EXPORT  Draw(HWND);
void  SCHEMA_EXPORT  DrawCoord(int,int);
void  SCHEMA_EXPORT  DrawCoord(int,int,int,int);
WORD  SCHEMA_EXPORT  DrawNumNode(int X, int Y );

int   SCHEMA_EXPORT  Access( LPCSTR Name );

/*void  SCHEMA_EXPORT  DrawAll(HDC hdc);
void  SCHEMA_EXPORT  DrawSection(HWND hWnd);*/

int   SCHEMA_EXPORT SCHEMA::AddSchema( ADD_SCHEMA_DATA &AddData, SCHEMA &AddSchm );
int                 AddControl( ADD_SCHEMA_DATA &AddData, SCHEMA &AddSchm, double Beg1[3], double Beg2[3], double mk[3][3] );
void  SCHEMA_EXPORT Turn(double,double,double);

void  SCHEMA_EXPORT  DeleteNode( float PrecesionCoincidence, BYTE Type=0 );
void  SCHEMA_EXPORT FormatUnite( void **FormUn );

void                 SetProgress( void (*Prog) (int) ) {  Progress = Prog;  }

//friend class INPUT;

};


SCHEMA_EXPORT STRING_PROFILE * GetProfileInform( PROFILE &, void * Ident, BYTE &Control );
SCHEMA_EXPORT STRING_PROFILE * GetProfileInform( PROFILE &, void * DataRgd, int NumRgd, BYTE &Control );
SCHEMA_EXPORT STRING_PROFILE * GetProfileInform( PROFILE &, void *Id, int Qnt, int Num[], BYTE &Control );

//int SchemaExec(WORD,SCHEMA *,TRUSS_DATA *Input);

int    SCHEMA_EXPORT  ElemType( int NTPR );
void  SCHEMA_EXPORT  MapForceValue( void *Sch, SCAD_FORCE &FrcGrp, BYTE MaskQw, BYTE MaskQn, double * Value );

#ifdef  SCAD_FLAG_H
#define Schema     cv->CurPrj[0]
#define Bound      cv->CurPrj[0]._Bound
#define Joint      cv->CurPrj[0]._Joint
#define Rigid      cv->CurPrj[0]._Rigid
#define __Load     cv->CurPrj[0]._Load
#define __Insert   cv->CurPrj[0]._Insert
#endif

#pragma pack(pop)
#endif
