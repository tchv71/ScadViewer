#include <stdafx.h>
#include "schema.h"

EXPORT void SCHEMA::Init(HWND hWnd, HINSTANCE hInst, LPCSTR Catalog)
{
	int i, n, m=0;
        static short  TreeRegime[] = {
		 0, 1, 2, 3, 4, 5, 6,
		 25, 26, 27, 28, 29, 30, 31,
		 50, -51, -52, -53, -54, -55, -56, -57, -58,
		 100, -101, -102, -103,
		 150, -151, -152, 0xFF };
	static BYTE  TreeRegimeNo[] = {  26, 27, 28, 30, 31, 0 };
	char WrkCtlg[MAXPATH];
	PROFILE *Prof;
   static UNITS ud[] = {  "M", 1,  "CM", 100, "T" , 1,  "C",  1 };

	strncpy(WrkCtlg,WorkCatalog,MAXPATH);
	memcpy(Units,ud,sizeof(ud));
        Prof = _Profile;

        if ( QuantityNode ) m = 1;
	Delete();
        if ( m ) Modify = 1;

	if ( Catalog )  {
		strcpy(WorkCatalog,Catalog);
		if ( WorkCatalog[strlen(WorkCatalog)-1] != '\\' ) strcat(WorkCatalog,"\\");
		}
	else strncpy(WorkCatalog,WrkCtlg,MAXPATH);

	for ( i=0; TreeRegime[i] != 0xFF; i++ ) {
           n = TreeRegime[i];
           if ( n == 0xFF ) break;
           if ( n >= 0 ) Tree[n].Regime = 2;
           else  Tree[-n].Regime = 3;
           }
	for ( i=0; TreeRegimeNo[i]; i++ ) Tree[TreeRegimeNo[i]].Regime = 1;

	SetPosFile();
	SetTypeSystem(5);

	SetTypeSystem(5);
	QuantityCraneForce = 2;
	QuantityBrakeForce = 1;
	Video.FragmParam   = 1;

	for ( i=0; i<=30; i++ ) BitOn(FlagPrintDoc,i);

	hWND = hWnd;  hINST = hInst;

   Param.Version = 7;
	Param.TypeOptimization = 0xFF;
	Param.CheckSolution    = 0xFF;

   _Profile = Prof;
    if ( Prof == NULL ) _Profile = &_ProfileIn;
}

void SCHEMA::SetPosFile()
{
	 WORD i;

	_Joint.File        = &FilePrj;
	_Joint.PosFile     = &Document[2].PosFile;
	_Bound.File        = &FilePrj;
	_Bound.PosFile     = &Document[5].PosFile;

	_Rigid.File        = &FilePrj;
	_Rigid.PosFile     = &Document[3].PosFile;
	_Insert.File       = &FilePrj;
	_Insert.PosFile    = &Document[31].PosFile;
	_Corner.File       = &FilePrj;
	_Corner.PosFile    = &Document[32].PosFile;
	_CornerNapr.File       = &FilePrj;
	_CornerNapr.PosFile    = &Document[33].PosFile;

	for ( i=0; i<10; i++ ) {
	   _List[i].File    = &FilePrj;
	   _List[i].PosFile = &Document[41+i].PosFile;  }

	_LoadList.PosFile  = &Document[6].PosFile;
	_LoadGroup.PosFile = &Document[7].PosFile;

	_Direct.File    = &FilePrj;
	_Direct.PosFile = &Document[17].PosFile;

	_SectionName.File    = &FilePrj;
	_SectionName.PosFile = &Document[19].PosFile;

	_RigidName.File    = &FilePrj;
	_RigidName.PosFile = &Document[20].PosFile;

	_Contur.File       = &FilePrj;
	_Contur.PosFile    = &Document[27].PosFile;

	_Steel.File     = &FilePrj;
	_Steel.PosFile  = &Document[28].PosFile;

	_SteelUni.File     = &FilePrj;
	_SteelUni.PosFile  = &Document[29].PosFile;

	_SteelRigid.File     = &FilePrj;
	_SteelRigid.PosFile  = &Document[30].PosFile;

	this->_Blocks.File     = &FilePrj;
	this->_Blocks.PosFile  = &Document[12].PosFile;

	this->_ConstructionPos.File     = &FilePrj;
	this->_ConstructionPos.PosFile  = &Document[11].PosFile;
}

void SCHEMA::ChangePosFile(SCHEMA &Schem)
{
   _Joint.Delete();
	_Joint.File        = &Schem.FilePrj;
	_Joint.PosFile     = &Schem.Document[2].PosFile;

   _Bound.Delete();
	_Bound.File        = &Schem.FilePrj;
	_Bound.PosFile     = &Schem.Document[5].PosFile;

   _Rigid.Delete();
	_Rigid.File        = &Schem.FilePrj;
	_Rigid.PosFile     = &Schem.Document[3].PosFile;

   _Insert.Delete();
	_Insert.File       = &Schem.FilePrj;
	_Insert.PosFile    = &Schem.Document[31].PosFile;

   _Corner.Delete();
	_Corner.File       = &Schem.FilePrj;
	_Corner.PosFile    = &Schem.Document[32].PosFile;
   _CornerNapr.Delete();
	_CornerNapr.File       = &Schem.FilePrj;
	_CornerNapr.PosFile    = &Schem.Document[33].PosFile;

   _SectionName.Delete();
	_SectionName.File    = &Schem.FilePrj;
	_SectionName.PosFile = &Schem.Document[19].PosFile;

   _RigidName.Delete();
	_RigidName.File    = &Schem.FilePrj;
	_RigidName.PosFile = &Schem.Document[20].PosFile;

}


EXPORT int  SCHEMA::Init( WORD QntElem, WORD QntNodeSchema )
{
	Init(hWND,hINST,NULL);

	if ( QntNodeSchema == 0 ) return 1;
	QuantityElem = QuantityAllocElem = QntElem;
	QuantityNode = QuantityAllocNode = QntNodeSchema;
	if ( QntElem ) pFormat = (FORMAT*) Memory(QuantityElem,sizeof(FORMAT));
	Coord       = (CK*)Memory(QntNodeSchema,sizeof(CK ));

	return 0;

}

EXPORT int  SCHEMA::Init( WORD QntElem,  WORD QntNodeSchema,
		  WORD TypeElem, WORD QntNodeElem  )
{
	if ( Init(QntElem,QntNodeSchema) ) return 1;
	SetListTypeElem(1,QntElem,TypeElem);
	if ( SetListAllocElemNode(1,QntElem,QntNodeElem) ) return 1;
	return 0;
}