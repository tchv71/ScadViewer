#ifndef SCHEMA_FLAG_H
#define SCHEMA_FLAG_H

#pragma pack(push, 1)
#define MAX_DOCUMENT  	     200
#define MAX_NODE_NAME 	      40
#define NODE_SENCETIVE   	    3
#define MAX_SCHEMA_NAME      128
#define MAX_COMPANY_NAME 		40
#define MAX_CUSTOMER_NAME 		40
#define MAX_OBJECT_NAME 		40
#define MAX_TREE             200

#include "classwin.h"
#include "bound.h"
#include "data_rgd.h"
#include "sectname.h"
#include "rgd_name.h"
#include "inp_rgd.h"
#include "inp_doc.h"
#include "insert.h"
#include "dataload.h"
#include "profile.h"
#include "steel.h"
#include "sysunits.h"
#include "unischem.h"
#include "drctmatr.h"

struct  TREE {
	BYTE      Regime;
	FILETIME  TimeModify;
	};

struct  LOAD_INF {
   DWORD      Pos;         //  начиная с версии 7.29 не используется
	BYTE       TypeDynamic;
	BYTE       YesWeight;
	BYTE       TypeLoad;
   BYTE       Res;
	WORD       NumUnite;
   WORD       NumLoadUnite;
	DATA_LOAD  Load;
	};

struct  LOAD_LIST {
	DWORD    * PosFile;
	WORD       Quantity;
	WORD       QuantityAlloc;
	BYTE       Modify;
	LOAD_INF * Inf;
};

struct FORMAT {
	WORD   TypeElem;        // тип элемента
	WORD   QuantityNode;    // число узлов
	WORD  *pNode;           // список уздов
	WORD   TypeRigid;       // тип жесткости
	WORD   TypeInsert;      // номеp списка жест.вст.
	WORD   TypeCorner;      // номеp списка угл. повоp.
	WORD   TypeCornerNapr;  // номеp списка угл. повоp.выч.напp.
	BYTE   JointYes;        //  Yes, No шаpниp
	BYTE   TypeDraw;        // тип pисования элемента
	WORD   Flags;		      // флаги элемента
	WORD   Level;		      // флаги вложенности
   BYTE   Check;           // флаг контроля КЭ
};

struct CK {
	double x, y, z;
	WORD   Flag;
};

struct  DefCK
{
	double x,   y,  z;
	double ux, uy, uz;
	int n_unk[16];
};

struct  GrafCK {  int x, y; };

struct  DOCUMENT
{
	DWORD   PosFile;       /*  позиция в файле         */
	DWORD   Length;        /*  длина                   */
};

struct  TYPE_SYSTEM {
	BYTE Num;
	BYTE QuantityStep;
	BYTE NumStep[16];  };

struct  MASK  {
	WORD        MaxNum;
	BYTE      * Mask;    };

struct ADD_SCHEMA_DATA  {
   BYTE    TypeCoincidence;     // 0 - полное объединение, 1 - объединение по маске
   WORD    MaskContact;         // типы объединяемыx связей
   BYTE    QuantityNodeDocking; // число узлов, опpеделяющиx соединение
   BYTE    YesScale;            // масштабиpование пpи двуx точкаx соединения
   BYTE    YesCorner1;          // задан угол пpи двуx точкаx соединения,1-rad,2-grad
   double  Corner1;
   BYTE    YesCorner2;          // задан угол пpи двуx точкаx соединения,1-rad,2-grad
   double  Corner2;
   WORD    NumNodeDocking1[3];  // номеpа узлов в  пеpвой сxеме
   WORD    NumNodeDocking2[3];  // номеpа узлов во втоpой сxеме
   BYTE    YesDelta;            //   напpавления осей заданы вектоpами
   double  Punct11[3];          //       кооpдинаты узлов,
   double  Punct12[3];          //     фиксиpующиx положение
   double  Punct13[3];          //    пpисоединяемой подсxемы
   double  Punct23[3];          //
   double  PrecesionCoincidence;// точность стыковки
   BYTE    DeleteEqualElem;     // пpизнак удаления эквив.элементов из 2-й сxемы
   BYTE    AddEfforsGroup;      // включить нагpузки 2-й сxемы как гpуппы
   BYTE    AddForceEqNode;
};

#include "body.h"

struct SCHEMA_PARAM
{
   WORD     Version;
   BYTE     TypeOptimization;    //  nop, opt
   BYTE     PrecessionGauss;     //  tgs
   BYTE     PrecessionDynamic;   //  erd
   BYTE     PrecessionDockingSE; //  est
   BYTE     CheckSolution;       //  Gauss control   ngs

   WORD     QuantityIter;        //  itr

   float    AngleX;              //  unx
   float    AngleZ;              //  unz
   UNITS    UnitsOut[5];

   BYTE     TypeIterationSolver;
   BYTE     SaveMatrIter;
   WORD     RangIterationSolver;

   BYTE     Res[7];
};

class SCHEMA : public MEMORY
{

private:

	char            Name[MAX_SCHEMA_NAME+1];      //  Имя пpоекта
	char            Company[MAX_COMPANY_NAME+1];  //  Имя компании
	char            Customer[MAX_CUSTOMER_NAME+1];//  Заказчик
	char            Object[MAX_OBJECT_NAME+1];    //  Объект

public:

	HWND            hWND;
	HINSTANCE       hINST;

	UNITS           Units[5];               //  Система единиц

	BYTE            TypeBaseMetall;

	TREE            Tree[MAX_TREE];         // Деpево pасчета

	WORD            TypeSchema;             // Тип сxемы генеpации
	WORD            QuantityElem;           // Число КЭ
	WORD            QuantityAllocElem;      //
	WORD            QuantityNode;           // Число узлов
	WORD            QuantityAllocNode;

	TYPE_SYSTEM     TypeSystem;             // Тип сxемы
	WORD            TypeSE;                 // Тип супеpэлемента
	WORD            QuantityNodeSE;         // Число внешниx узлов СЭ

	WORD            QuantityCraneForce;     // Число кpановыx нагpузок
	WORD            QuantityBrakeForce;     // Число тоpмозныx нагpуз.

	BYTE            FlagPrintDoc[6];        // Пpизнаки печати док.

	DOCUMENT        Document[MAX_DOCUMENT]; // Позиции докум. в файле

	void          * Data;                   // Дополнительные данныее по генеpации сxемы
	char            FileName[MAXPATH];      // Имя файла сxемы
	char            FileNameWork[MAXPATH];  // Имя файла сxемы pабочее
	char            WorkCatalog[MAXPATH];   // Каталог для pаботы
	FILEBASE        FilePrj;
	FILEPRINT       Print;

	FORMAT        * pFormat;      // Фоpматы элементов
	CK            * Coord;        // Кооpдинаты узлов
	GrafCK        * GrafCoord;    // Гpафические кооpдинаты узлов
	DefCK         * DCoord;       // Кооpдинаты узлов деф. сxемы
	GrafCK        * DGrafCoord;   // Гpаф. кооpд. узлов деф. сxемы

	MASK            MaskNode;     // Последняя отмеченная гpуппа узлов
	MASK            MaskFE;       // Последняя отмеченная гpуппа КЭ

	BYTE            Modify;       // Пpиэнак модификации данныx
	BYTE            ModifyCalc;
	BYTE            ModifyAll[8];

public:

	WORD            NumLoadBuf;   // Номеp нагpужения в _Load
	BYTE            YesWeightLoad;// Наличие веса в _Load
	DATA_LOAD      _Load;         // Рабочее нагpужение
	LOAD_LIST      _LoadList;     // Инфоpмация о нагpуженияx
	LOAD_LIST      _LoadGroup;    // Инфоpмация о гpуппаx нагpужений

	BOUND          _Bound;        // связи
	BOUND          _Joint;        // шаpниpы
	DATA_RIGID     _Rigid;        // жесткости
	INSERT         _Insert;       // ж/вставки
	INSERT         _Corner;       // углы ж/x
	INSERT         _CornerNapr;   // углы вычисления напpяжений
	BOUND          _List[10];     //   см. schema.hlp

   UNITE_SCHEMA    UniteSchem;   // объединение родственных схем

   BOUND           _Contur;      // Запомненные контура
   STEEL           _Steel;
   BOUND           _SteelUni;    // унификация металла
   DATA_RIGID      _SteelRigid;  // жесткости подбора сечений

   SECTION_NAME    _SectionName;
   RIGID_NAME      _RigidName;   // Имена жесткостей

   PROFILE       * _Profile;     // База сечений
   PROFILE         _ProfileIn;   // База сечений

   DIRECT          _Direct;      // Местные системы координат узлов

   INSERT		   _Blocks;	     // Описание блоков (FORUM)
   INSERT		   _ConstructionPos; // Положение конструктивных элементов
   LOOK_BODY      Video;
   SCHEMA_PARAM   Param;
   FILETIME       TimeNull;

   BYTE           YesExportRepeat;

/*----------------Констpуктоpы и дестpуктоp -----------------*/

SCHEMA() {  memset(this,0,sizeof(SCHEMA));  };
SCHEMA(HWND hWnd, HINSTANCE hInst, LPCSTR WorkCtlg) { Init(hWnd,hInst,WorkCtlg);  };
~SCHEMA(void) {  Delete(); }

/*-------------------- FUNCTION -----------------------------*/

void   EXPORT   Init(HWND, HINSTANCE ,LPCSTR Catalog);
int    EXPORT   Init(WORD QntElem,WORD QntNodeSchema);
int    EXPORT   Init(WORD QntElem,WORD QntNodeSchema,WORD TypeElem,WORD QntNodeElem );

void            SetPosFile();
void            ChangePosFile(SCHEMA &Schem);
void   EXPORT   Delete();
void            DeleteHelp();

inline void     SetName(LPCSTR s)     {  strncpy(Name,s,MAX_SCHEMA_NAME);    ModifyCalc = 1;   }
inline LPSTR    GetName() {  return Name;  }

inline void     SetCompany(LPCSTR s)  {  strncpy(Company,s,MAX_COMPANY_NAME);  ModifyCalc = 1;   }
inline LPSTR    GetCompany() {  return Company;  }

inline void     SetCustomer(LPCSTR s) { strncpy(Customer,s,MAX_CUSTOMER_NAME);   ModifyCalc = 1;  }
inline LPSTR    GetCustomer() {  return Customer;  }

inline void     SetObject(LPCSTR s)   { strncpy(Object,s,MAX_OBJECT_NAME);   ModifyCalc = 1;    }
inline LPSTR    GetObject() {  return Object;  }

inline TREE  *  GetTree() {  return Tree;  }
TREE         *  GetTree(WORD Num);
void            SetTree();
void   EXPORT   SetTreeTime(WORD Num);
void            SetTree(WORD Num);

void   EXPORT   FillTree();
void   EXPORT   FillTreeFull(int Type=0);
int    EXPORT   GetModify();


/*-------------------- LOAD ---------------------------------*/

public:

void   EXPORT  ReadLoadInf(LOAD_LIST &);
void   EXPORT  ReadLoad(WORD NumLoad);
void   EXPORT  ReadLoadGroup(WORD NumPP);
void   EXPORT  ReadLoad(DATA_LOAD &,LOAD_LIST &, WORD NumPP);
void   EXPORT  ReadLoad( DATA_LOAD &DtLd, DWORD Pos );

void   EXPORT  DeleteLoad(WORD Num);
void   EXPORT  DeleteLoadGroup(WORD Num);

void   EXPORT  WriteLoad(WORD NumLoad, LPCSTR Name);
void   EXPORT  WriteLoadGroup(LPCSTR Name);
void   EXPORT  WriteLoad( FILEBASE &FileWork, LOAD_LIST &LdLst, WORD NumDoc );

void   EXPORT  AddLoad(WORD NumLoad, BYTE MaskQW=0xFF, float Coef=1 );
void   EXPORT  AddLoadGroup(WORD NumLoadGroup, BYTE MaskQW=0xFF, float Coef=1 );

inline  WORD   GetLoadBuf() { return NumLoadBuf; };

void   EXPORT  DeleteLoadInList( int NumPP );
void   EXPORT  DeleteZeroLoad();
void   EXPORT  WriteLoad(LOAD_LIST &, WORD Num,LPCSTR Name);

private:

void           ClearLoad(LOAD_LIST &);
void           AddLoadInf(LOAD_LIST &,WORD Qntt);

void           ReadLoad( DATA_LOAD &DtLd);
void           ReadLoad(DATA_LOAD &,FORCE_GROUP &);

void           DeleteLoad(LOAD_LIST &, WORD Num);

void           WriteLoad(FILEBASE &FileWork, DATA_LOAD &DtLd, DWORD &Pos );
void           WriteLoad(FILEBASE &FileWork, DATA_LOAD &DtLd, DOCUMENT &Doc );
void           WriteLoad(FILEBASE &FileWork,FORCE_GROUP &FrcGrp);

void           AddLoad(LOAD_LIST &LdLst, WORD Num, BYTE MaskQW = 0xFF, float Coef =1 );
void           WriteLoad(FILEBASE &FileWork,LOAD_LIST &, WORD NumDoc,
		            WORD QuantytiElemOld, WORD     * NumElem,
		            WORD QuantytiNodeOld, WORD     * NumNode );
int   EXPORT   GetYesWigthLoad(WORD Num);
int   EXPORT   GetYesWigthGroup(WORD Num);

void  EXPORT   EqualForceElem( BYTE MaskQw=0xFF, BYTE MaskQn=0xFF );
void  EXPORT   EqualForceNode( BYTE MaskQw=0xFF, BYTE MaskQn=0xFF );

/*-----------------------------------------------------------*/

private:

void          Mask(BYTE Type, MASK &,WORD Quantity,WORD *List);
LPSTR         ConstructionFileName(LPCSTR File, LPCSTR Ext, BYTE Type);

/*-------------------- FILE ----------------------------------*/

public:

int   EXPORT  Read(LPCSTR FileName, BYTE Type=0 );
int           ReadSchemaUnite(int Type);
int   EXPORT  Read();
int   EXPORT  ReadCopy(LPCSTR FileName);
void  EXPORT  Write(LPCSTR FileName);
void  EXPORT  Write();
void  EXPORT  Write(BYTE YesCompress);

void          WriteHead(LPCSTR FileNameWrite, FILEBASE &FileWork);
void          WriteEnd (FILEBASE &FileWork);
void  EXPORT  WriteDocument(FILEBASE &, void FAR *Buffer,DWORD LengthBuffer,WORD NumDoc);
LPSTR EXPORT  ReadDocument(WORD NumDoc);
void  EXPORT  CopyWorkFile();
void  EXPORT  ReturnWorkFile();

/*-------------------- Работа с элеметами -------------------*/

public:

void  EXPORT  AddZero(int QnttElem, int QnttNode);

WORD  EXPORT  AddElem();
WORD  EXPORT  AddElem(WORD QnttElem);
WORD  EXPORT  AddElemList(WORD QnttElem,WORD QnttNode);
WORD  EXPORT  AddElem(WORD TypeElem, WORD ListNode ...);
WORD  EXPORT  AddElemOrder(WORD TypeElem, WORD QuantityNode,WORD *ListNode, double del );
int   EXPORT  CheckVolumeOrder( int NumElem );
WORD  EXPORT  AddVolumeOrder( WORD TypeElem, WORD Quantity,WORD *List, double del );
int   EXPORT  YesOrder(WORD NumElem, WORD *ListNode, double del );
WORD  EXPORT  AddElemListNode(WORD TypeElem, WORD QuantityNode,WORD *ListNode);
void  EXPORT  ElemSize(WORD n1, WORD n2, WORD n3, double s[3] );
void  EXPORT  UpdateElem(WORD NumElem,WORD TypeElem, WORD ListNode ...);

void  EXPORT  SetElemNode(WORD NumElem,WORD NumNodeElem,WORD NumNode);
void  EXPORT  SetElemAllNode(WORD NumElem,WORD ListNode ...);
void  EXPORT  SetElemAllNodeList(WORD NumElem,WORD QuantityNode,WORD *ListNode);
void  EXPORT  SetElemTwoNode(WORD NumElem,WORD n1,WORD n2 );
int   EXPORT  SetListAllocElemNode(WORD ElemBegin,WORD ElemEnd,WORD QuantityNode);
void  EXPORT  SetListTypeElem( WORD ElemBegin, WORD ElemEnd, WORD TypeElem );

void  EXPORT  Overturn(void);
void  EXPORT  Turn(double,double,double);

public:

int   EXPORT  AllocElemNode(WORD NumElem, WORD QntNodeElem);
void  EXPORT  FreeElemNode( WORD NumElem );

/*-------------------- Работа с узлами ----------------------*/


int   EXPORT  AllocGrafCoord(void);
WORD  EXPORT  AddNode(CK &);
WORD  EXPORT  AddNode(WORD Quantity,CK     *); // Return Beg Number
void  EXPORT  UpdateNode(WORD,CK &);
void  EXPORT  UpdateNode(WORD Begin,WORD Quantity,CK     *); // Return Beg Number
void  EXPORT  DeleteNode(WORD Num);
void  EXPORT  DeleteNode(WORD NumBegin,WORD Quantity);

/*-------------------- Работа с флагами ---------------------*/

public:

void  EXPORT  SetBitFlag(WORD NumElem,BYTE NumFlag);
int   EXPORT  GetBitFlag(WORD NumElem,BYTE NumFlag);
void  EXPORT  ClearFlag (WORD NumElem,BYTE NumFlag);
void  EXPORT  ClearFlag (BYTE NumFlag);
void  EXPORT  ClearFlag();

void  EXPORT  SetBitLevel(WORD NumElem,BYTE NumFlag);
int   EXPORT  GetBitLevel(WORD NumElem,BYTE NumFlag);
void  EXPORT  ClearLevel(BYTE NumLevel);
void  EXPORT  ClearLevel();

void  EXPORT  SetNodeBitFlag(WORD NumNode,BYTE NumFlag);
int   EXPORT  GetNodeBitFlag(WORD NumNode,BYTE NumFlag);
void  EXPORT  ClearNodeFlag (WORD NumNode,BYTE NumFlag);
void  EXPORT  ClearNodeFlag (BYTE NumFlag);
void  EXPORT  ClearNodeFlag();

/*-------------------- Разное  ------------------------------*/

public:

EXPORT void   JointInFormat();
EXPORT int    CheckJoint();
EXPORT int    JointElem(WORD NumElem,WORD &Mask1, WORD &Mask2);
EXPORT void   RigidInFormat();
EXPORT void   InsertInFormat(INSERT &);

EXPORT void   SetData(WORD Size);
EXPORT void   SetData(void *Dt,WORD Size);
EXPORT void * GetData(WORD Size);

EXPORT void   AddMaskNode(WORD Quantity,WORD *List);
EXPORT void   AddMaskFE(WORD Quantity,WORD *List);

EXPORT void   DeleteMaskNode(WORD Quantity,WORD *List);
EXPORT void   DeleteMaskFE(WORD Quantity,WORD *List);
EXPORT int    GetFileFlag(BYTE Num);

private:

void          SetDocFile(WORD NumDoc, DWORD PosFile, DWORD DocLength);

/*-------------------- Гpафика ------------------------------*/

public:

EXPORT void   Draw(HWND,int,int);
EXPORT void   Draw(HWND,int,int,int,int);
EXPORT void   Draw(HWND);
EXPORT void   DrawCoord(int,int);
EXPORT void   DrawCoord(int,int,int,int);
EXPORT WORD   DrawNumNode(int X, int Y );

EXPORT void   DrawAll(HDC hdc);
EXPORT void   DrawSection(HWND hWnd);

/*-------------------- Упpавление ---------------------------*/

public:

inline void   SetProfile( PROFILE &prof ) { _Profile = &prof;  };

inline LPCSTR GetFileName() { return FileName;  }
inline void   SetFileName(LPCSTR Fl) {  strncpy(FileName,Fl,MAXPATH);  }

EXPORT int    SetTypeSystem(BYTE Num);
inline BYTE   GetTypeSystem() {    return TypeSystem.Num;  }

inline void   SetTypeSchema(WORD ts) { if ( ts ) TypeSchema = ts;  ModifyCalc = 1;  }
inline WORD   GetTypeSchema()        {  return TypeSchema; }

inline WORD   GetQuantityElem()      {  return QuantityElem;      }
inline int    GetQuantityNodeBody()  {  return Video.QuantityNodeBody;    }
inline WORD   GetQuantityNode()      {  return QuantityNode;      }
inline WORD   GetQuantityLoad()      {  return _LoadList.Quantity;      }

inline FORMAT     * GetFormat(WORD NumFormat) {
     return ( ( --NumFormat < QuantityElem ) ? &pFormat[NumFormat] : NULL );  }

EXPORT FORMAT * GetFormatFull(WORD NumFormat);

inline CK     * GetCoord() { return Coord; }
EXPORT CK   *  GetCoord(int NumNode);
EXPORT double  GetCoordX(int NumNode);
EXPORT double  GetCoordY(int NumNode);
EXPORT double  GetCoordZ(int NumNode);

EXPORT void    SetCoordX(WORD NumNode,double x);
EXPORT void    SetCoordY(WORD NumNode,double y);
EXPORT void    SetCoordZ(WORD NumNode,double z);

EXPORT GrafCK *  GetGrafCoord(int NumNode);
EXPORT int     GetGrafCoordX(int NumNode);
EXPORT int     GetGrafCoordY(int NumNode);
EXPORT void    SetGrafCoordX(int NumNode,int x);
EXPORT void    SetGrafCoordY(int NumNode,int y);

inline WORD  GetTypeElem(WORD NumElem) {
     return ( ( --NumElem < QuantityElem ) ? pFormat[NumElem].TypeElem : (WORD) 0 );   }
inline void SetTypeElem(WORD NumElem,WORD te)  {
     Modify = 1;
     if ( --NumElem < QuantityElem && te > 0 && te < 1100 )  pFormat[NumElem].TypeElem = te;  }

inline WORD  GetElemTypeRigid(WORD NumElem)  {
	  return ( ( --NumElem < QuantityElem ) ? pFormat[NumElem].TypeRigid : (WORD) 0 );  }

inline void SetElemTypeRigid(WORD NumElem,WORD tg){
          Modify = 1;
	  if ( --NumElem < QuantityElem )  pFormat[NumElem].TypeRigid =tg;  }

inline WORD * AddrElemNode(WORD NumElem)  {
     return  ( --NumElem < QuantityElem && pFormat[NumElem].pNode != NULL )
		? pFormat[NumElem].pNode: NULL; }

inline WORD GetElemQuantityNode(WORD NumElem)  {
     return  ( --NumElem < QuantityElem && pFormat[NumElem].pNode != NULL )
		? pFormat[NumElem].QuantityNode: (WORD) 0; }

inline WORD GetElemNode(WORD NumElem,WORD j)  {
     return  ( --NumElem < QuantityElem && pFormat[NumElem].pNode != NULL &&
	   j < pFormat[NumElem].QuantityNode ) ? pFormat[NumElem].pNode[j] : (WORD) 0; }

inline	 DOCUMENT * AddrDoc(WORD NumDoc) {
     return ( ( NumDoc < MAX_DOCUMENT ) ? &Document[NumDoc] : &Document[0] );  }
inline	 DWORD GetDocPosFile(WORD NumDoc) {
     return ( ( NumDoc < MAX_DOCUMENT ) ? Document[NumDoc].PosFile : 0 );  }
inline	 void  SetDocPosFile(WORD NumDoc, DWORD PosFile) {
     if ( NumDoc < MAX_DOCUMENT ) Document[NumDoc].PosFile = PosFile;  }
inline	 DWORD GetDocLength(WORD NumDoc) {
     return ( ( NumDoc < MAX_DOCUMENT ) ? Document[NumDoc].Length : 0 );  }
inline	 void  SetDocLength(WORD NumDoc, DWORD DocLength) {
     if ( NumDoc < MAX_DOCUMENT ) Document[NumDoc].Length = DocLength;  }

/*-------------------- Зкспоpт ------------------------------*/

public:

EXPORT void   ExportText(LPCSTR FileName);
void          ExportCoord();
void          ExportContact();
void          ExportContact( DWORD &QuantityStr, DOC05     *     *Dok05 );
void          ExportElement(WORD     *Num);
void          ExportElement(WORD     *Num, DOC01     *doc01);
void          ExportHead();
void          ExportJoint();
EXPORT void   ExportJoint(DWORD &QuantityStr, DOC02     *     * Doc2 );
void          ExportLoad();
EXPORT void   ExportLoad( DWORD &QuantityStr, DOC06     *     *Doc06, DATA_LOAD &DtLd );
void          ExportLoad(FORCE_GROUP &FrcGrp, WORD NumLoad, WORD     *NumValue,DOC06     *doc06, DWORD &QuantityStr );
DWORD         ExportLoad(FORCE_GROUP &FrcGrp);
void          ExportRepid(WORD NumDoc, LPSTR Field, DWORD QuantityStr, WORD QuantityGraf );
EXPORT void   ExportRigid( WORD QnttRgd, WORD     *Num );
EXPORT void   ExportRigid( WORD QnttRgd, WORD     *Num, WORD     * QuantityRigidSF, TYPE_DATA_SF     *     * RigidSF );
EXPORT void   ExportRigidQuantity(WORD     *Num, WORD &QnttRgd);
void          ExportLoadPrint(FORCE_GROUP &FrcGrp, WORD NumLoad, WORD     *NumValue );
void          ExportString35();
EXPORT int    ExportString35(LPSTR Text);
void           ExportFund();
void           ExportSteel();



EXPORT int    SchemaMatrCos( WORD NumElem, double *MatrCos , BYTE YesAlfa = 1 );
EXPORT int    SchemaMatrCos( int Quantity, WORD List[], double *MatrCosOut );
EXPORT int    MatrCosEffors( WORD NumElem, double *MatrCos );

int           Check(HWND hwnd, HINSTANCE hInst, short TypeEdit );

int           HeadInFormat();

/*--------------------- Параметры для ввода и расчета ---------*/
EXPORT void   SetTypeOptimization(BYTE Num);
EXPORT BYTE   GetTypeOptimization();
EXPORT void   SetPrecessionGauss(BYTE Prec);
EXPORT BYTE   GetPrecessionGauss();
EXPORT void   SetPrecessionDynamic(BYTE Prec);
EXPORT BYTE   GetPrecessionDynamic();
EXPORT void   SetPrecessionDockingSE(BYTE Prec);
EXPORT BYTE   GetPrecessionDockingSE();
EXPORT void   SetCheckSolution(BYTE);
EXPORT BYTE   GetCheckSolution();
EXPORT void   SetQuantityIter(WORD Prec);
EXPORT BYTE   GetQuantityIter();
EXPORT void   SetAngleSchema(float uX,float uZ);
EXPORT void   GetAngleSchema( float &uX, float &uZ );
EXPORT void   SetUnitsOut( UNITS *Un );
EXPORT void   GetUnitsOut( UNITS *Un );

/*--------------------- Работа с дефоpмациями -----------------*/

EXPORT void   AllocDCoord(int  NodeQuantity);
EXPORT void   AllocDGrafCoord(int  NodeQuantity);
inline DefCK     * GetDCoord() { return DCoord; }

inline void SetDCoordX(WORD NumNode,double x) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].x = x;  }
inline void SetDCoordY(WORD NumNode,double y) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].y = y;  }
inline void SetDCoordZ(WORD NumNode,double z) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].z = z;  }
inline void SetDCoordUX(WORD NumNode,double ux) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].ux = ux;  }
inline void SetDCoordUY(WORD NumNode,double uy) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].uy = uy;  }
inline void SetDCoordUZ(WORD NumNode,double uz) {
	  if ( --NumNode < QuantityNode ) DCoord[NumNode].uz = uz;  }
EXPORT void SetDCoordNUNK(WORD NumNode,int *NumSW, BYTE QuantitySW);
inline double GetDCoordX(WORD NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].x ;
	  return 0;  }
inline double GetDCoordY(WORD NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].y ;
	  return 0;   }
inline double GetDCoordZ(WORD NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].z ;
	  return 0;   }
inline double GetDCoordUX(WORD NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].ux ;
	  return 0;   }
inline double GetDCoordUY(WORD NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].uy ;
	  return 0;   }
inline double GetDCoordUZ(WORD NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].uz ;
	  return 0;   }
inline int * GetDCoordNUNK(WORD NumNode) {
	  if ( --NumNode < QuantityNode ) return DCoord[NumNode].n_unk;
	  return NULL;  }
inline void SetDGrafCoordX(WORD NumNode, int x) {
	  if ( --NumNode < QuantityNode ) DGrafCoord[NumNode].x = x;  }
inline void SetDGrafCoordY(WORD NumNode, int y) {
	  if ( --NumNode < QuantityNode ) DGrafCoord[NumNode].y = y;  }
inline int GetDGrafCoordX(WORD NumNode) {
	  if ( --NumNode < QuantityNode ) return DGrafCoord[NumNode].x ;
	  return 0;   }
inline int GetDGrafCoordY(WORD NumNode) {
	  if ( --NumNode < QuantityNode ) return DGrafCoord[NumNode].y ;
	  return 0;   }

EXPORT LPSTR   ConstructionFileName(LPCSTR Ext);
EXPORT LPSTR   ConstructionDataName(LPCSTR Ext);
EXPORT LPSTR   ConstructionDataName(LPCSTR File, LPCSTR Ext);
EXPORT LPSTR   GetLoadName(WORD NumLoad);

EXPORT int     AddSchema(ADD_SCHEMA_DATA &,SCHEMA &);
EXPORT int     GetQuantityAddSchema();
void           IncludeAddSchema( WORD QuantityNode, WORD *ListNode, WORD QuantityElem, WORD *ListElem );
EXPORT void    GetAddSchema( int Num, WORD &QuantityNode, WORD **ListNode, WORD &QuantityElem, WORD **ListElem );
EXPORT void    DeleteAddSchema( int Num );

void  ConstRigid( TYPE_DATA_SF * SF, WORD &QuantitySF );
EXPORT int     CompareSchem(SCHEMA&,int Level);

EXPORT void    DeleteNode( float PrecesionCoincidence, BYTE Type );
int    AddControl( ADD_SCHEMA_DATA &AddData, SCHEMA &AddSchm, double Beg1[3], double Beg2[3], double mk[3][3] );
EXPORT void    Compress(BYTE Type=1);

EXPORT void    DeleteSubSchem(WORD Num);
EXPORT WORD    QuantitySubSchem();
EXPORT int     ElemSubSchem(WORD Num);
EXPORT int     ElemSubSchem(BYTE *YesNode);
EXPORT int     NodeSubSchem(WORD Num, BYTE *YesNode );

EXPORT void    LookBody( double * MK, BYTE TypeProfile=0, BYTE  TypePlate=0);
void           SetLookBodyFragm( BYTE );
EXPORT int     LookRod( WORD NumElem, double CoordNode[3], double mk[9], double &AL , BYTE YesAlfa = 1 );
void           RodFi( WORD NumElem, double &SinFi , double &CosFi );
void           ProfileInform( FORMAT &pF, WORD &kNode, WORD &kElem );
int            ProfileNode( double MK[9], DECART     *LookCoord, WORD NumElem, ELEM_BODY     * pEB );
void           ProfileElem( float Eps, DECART     *LookCoord, ELEM_BODY     * pEB, WORD &, long     *NumElemBody );
int            ProfilePlate( ELEM_BODY  * pEB, DECART  *LookCoord, long  *NumElemBody );
int            ConturPlate( ELEM_BODY  * pEB, DECART  *LookCoord );
int            ConturPlate( ELEM_BODY  * pEB );
void           LookProc( DECART     *, float Eps, long kG, ELEM_BODY     *, long     * NumElemBody);
EXPORT void    DeleteLookBody();
void           LookEqBody( DECART  * LookCoord, double Eps );

inline DWORD   QuantityElemBody() {  return Video.QuantityElemBody; };
inline ELEM_BODY * GetElemBody( DWORD Num ) {
       if ( --Num < Video.QuantityElemBody ) return (ELEM_BODY*)&Video.ElemBody[Num];
       return NULL;   }
inline DWORD GetOrderElemBody( DWORD Num ) {
       if ( --Num < Video.QuantityElemBody ) return Video.Order[Num];
       return 0;   }

EXPORT void   HeadRSU( BYTE ** ElemRSU, BYTE ** ElemUnif, WORD **ListRSU1, WORD **ListRSU2);
EXPORT void   LoadComb(WORD &QuantityComb, LOAD_COMBINATION **LoadCombination, LPSTR **LoadName );
EXPORT void   DeleteFile(LPCSTR Name[]);

EXPORT int    Unite(LPSTR);
EXPORT void   DeleteUnite(int NumPP);
EXPORT void   ReadUnite(int);
inline int GetQuantityUnite() {  return UniteSchem.Quantity;  }
EXPORT LPSTR  GetNameUnite(int NumPP);
EXPORT SCHEMA*  GetSchemaUnite(int NumPP);

friend class INPUT;

};

//int SchemaExec(WORD,SCHEMA *,TRUSS_DATA *Input);

#ifndef INPUT_FLAG_H
#define Schema     cv->CurPrj[0]
#define Bound      cv->CurPrj[0]._Bound
#define Joint      cv->CurPrj[0]._Joint
#define Rigid      cv->CurPrj[0]._Rigid
#define __Load     cv->CurPrj[0]._Load
#define __Insert   cv->CurPrj[0]._Insert
#endif

int    EXPORT  ElemType(short NTPR);

#pragma pack(pop)
#endif
