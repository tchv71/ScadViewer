#ifndef	_SCADAPIX_SCHEMA_hxx_FLAG_
#define	_SCADAPIX_SCHEMA_hxx_FLAG_

#pragma pack(push,1)

APICode     SCAD_WINAPI  ApiSetLanguage ( ScadAPI lpAPI, int Lang );
APICode     SCAD_WINAPI  ApiClear( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiSetUnits( ScadAPI lpAPI, const UnitsAPI *Un );
LPCUnitsAPI SCAD_WINAPI  ApiGetUnits( ScadAPI lpAPI );

APICode     SCAD_WINAPI  ApiReadProject( ScadAPI lpAPI, LPCSTR Name );
APICode     SCAD_WINAPI  ApiWriteProject( ScadAPI lpAPI, LPCSTR Name );

APICode     SCAD_WINAPI  ApiSetName(  ScadAPI lpAPI, LPCSTR Name );
LPCSTR      SCAD_WINAPI  ApiGetName (  ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiSetWorkCatalog( ScadAPI lpAPI, LPCSTR Txt );
UINT        SCAD_WINAPI  ApiGetTypeSchema( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiSetTypeSchema( ScadAPI lpAPI, BYTE Type );

LPCSTR      SCAD_WINAPI  ApiGetProjectNameFile( ScadAPI lpAPI );

UINT        SCAD_WINAPI  ApiGetTypeSystem( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiSetTypeSystem( ScadAPI lpAPI, UINT Num );

UINT        SCAD_WINAPI  ApiGetQuantityNode( ScadAPI lpAPI );
LPCNodeApi  SCAD_WINAPI  ApiGetNode( ScadAPI lpAPI, UINT NumNode=1 );
UINT        SCAD_WINAPI  ApiNodeAddSize( ScadAPI lpAPI, UINT Qnt );
UINT        SCAD_WINAPI  ApiNodeAdd( ScadAPI lpAPI, UINT Qnt, const CNodeApi *ck );
UINT        SCAD_WINAPI  ApiNodeAddOne( ScadAPI lpAPI, double x, double y, double z );
APICode     SCAD_WINAPI  ApiNodeUpdate( ScadAPI lpAPI, UINT  NumNode, double x, double y, double z );
APICode     SCAD_WINAPI  ApiNodeSetName( ScadAPI lpAPI, UINT Num, LPCSTR Text );
LPCSTR      SCAD_WINAPI  ApiNodeGetName( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiDeleteNode( ScadAPI lpAPI, UINT Num, BOOL YesDeleteElem );
APICode     SCAD_WINAPI  ApiDeleteNodeList( ScadAPI lpAPI, UINT Qnt, const UINT * List, BOOL YesDeleteElem );
APICode     SCAD_WINAPI  ApiUnDeleteNode( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiUnDeleteNodeList( ScadAPI lpAPI, UINT Qnt, const UINT * List );
UINT        SCAD_WINAPI  ApiIsNodeDeleted( ScadAPI lpAPI, UINT NumNode );

UINT        SCAD_WINAPI  ApiGetElemQuantity( ScadAPI lpAPI );
UINT        SCAD_WINAPI  ApiElemAdd( ScadAPI lpAPI, UINT Qnt );
APICode     SCAD_WINAPI  ApiElemGetData( ScadAPI lpAPI, UINT Num, UINT * Type, UINT * NumRgd, UINT * QntNd, const UINT ** ListNode );
APICode     SCAD_WINAPI  ApiElemGetInf( ScadAPI lpAPI, UINT Num, CElemInfApi * ElemInf );
UINT        SCAD_WINAPI  ApiElemAddData( ScadAPI lpAPI, UINT Type, UINT QuantityNode, const UINT * ListNode );
APICode     SCAD_WINAPI  ApiElemUpdate( ScadAPI lpAPI, UINT Num, UINT Type, UINT QuantityNode, const UINT * ListNode );
APICode     SCAD_WINAPI  ApiElemSetName( ScadAPI lpAPI, UINT Num, LPCSTR Text );
LPCSTR      SCAD_WINAPI  ApiElemGetName( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiElemSetType( ScadAPI lpAPI, UINT Type, UINT ElemBegin, UINT ElemEnd=0 );

APICode     SCAD_WINAPI  ApiDeleteElem( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiDeleteElemList( ScadAPI lpAPI, UINT Qnt, const UINT * List );
APICode     SCAD_WINAPI  ApiUnDeleteElem( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiUnDeleteElemList( ScadAPI lpAPI, UINT Qnt, const UINT * List );
UINT        SCAD_WINAPI  ApiIsElemDeleted( ScadAPI lpAPI, UINT NumElem );

UINT        SCAD_WINAPI  ApiElemGetQuantityHole( ScadAPI lpAPI, UINT NumElem );
APICode     SCAD_WINAPI  ApiElemGetHole( ScadAPI lpAPI, UINT NumElem, UINT NumContur, UINT *QuantityNode, const UINT ** ListNode );
APICode     SCAD_WINAPI  ApiElemSetHole( ScadAPI lpAPI, UINT NumElem, UINT QuantityHole, const UINT * ListHole );

UINT        SCAD_WINAPI  ApiGetQuantityGroupElem( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiGetGroupElem( ScadAPI lpAPI, UINT Num, UINT *Type, UINT *Qnt, const UINT **ListElem, LPCSTR * Text );
UINT        SCAD_WINAPI  ApiSetGroupElem( ScadAPI lpAPI, LPCSTR Text, BYTE Type, UINT Qnt, const UINT *ListElem );
APICode     SCAD_WINAPI  ApiSetNameGroupElem( ScadAPI lpAPI, UINT Num, LPCSTR Name );
LPCSTR      SCAD_WINAPI  ApiGetNameGroupElem( ScadAPI lpAPI, UINT Num );

UINT        SCAD_WINAPI  ApiGetQuantityGroupNode( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiGetGroupNode( ScadAPI lpAPI, UINT Num, UINT *Qnt, const UINT **ListNode, LPCSTR * Text );
UINT        SCAD_WINAPI  ApiSetGroupNode( ScadAPI lpAPI, LPCSTR Text, UINT Qnt, const UINT *ListNode );
APICode     SCAD_WINAPI  ApiSetNameGroupNode( ScadAPI lpAPI, UINT Num, LPCSTR Name );
LPCSTR      SCAD_WINAPI  ApiGetNameGroupNode( ScadAPI lpAPI, UINT Num ); 

UINT        SCAD_WINAPI  ApiGetQuantityBlock( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiGetBlock( ScadAPI lpAPI, UINT Num, UINT *Qnt, const UINT **ListElem, LPCSTR * Text, COLORREF *Col );
UINT        SCAD_WINAPI  ApiSetBlock( ScadAPI lpAPI, LPCSTR Text, COLORREF Col, UINT Qnt, const UINT *ListElem );
APICode     SCAD_WINAPI  ApiSetNameBlock( ScadAPI lpAPI, UINT Num, LPCSTR Name );
LPCSTR      SCAD_WINAPI  ApiGetNameBlock( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiDeleteBlock( ScadAPI lpAPI, UINT Num );

// связи
UINT        SCAD_WINAPI  ApiGetBound( ScadAPI lpAPI, UINT NumNode );
APICode     SCAD_WINAPI  ApiSetBound( ScadAPI lpAPI, WORD Mask, UINT QntNode, const UINT * ListNode, BOOL YesClear=TRUE );

UINT        SCAD_WINAPI  ApiGetQuantityBoundUnite( ScadAPI lpAPI );
LPCSTR      SCAD_WINAPI  ApiGetBoundUniteName( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiSetBoundUniteName( ScadAPI lpAPI, UINT Num, LPCSTR Name );
APICode     SCAD_WINAPI  ApiGetBoundUnite( ScadAPI lpAPI, UINT NumGroup, WORD *Mask, UINT *QntNode, const UINT **ListNode );
UINT        SCAD_WINAPI  ApiSetBoundUnite( ScadAPI lpAPI, WORD Mask, UINT QntNode, const UINT * ListNode  );
APICode     SCAD_WINAPI  ApiDeleteBoundUnite( ScadAPI lpAPI, UINT Num );

// жесткие вставки
UINT        SCAD_WINAPI  ApiGetQuantityInsert( ScadAPI lpAPI );
BOOL        SCAD_WINAPI  ApiGetNumInsert( ScadAPI lpAPI, UINT Num, BYTE *Type, UINT *QntSize, const double ** Size, UINT *QntEl, const UINT ** ListEl );
BOOL        SCAD_WINAPI  ApiGetInsert( ScadAPI lpAPI, UINT NumElem, BYTE *Type, UINT *QntSize, double * Size );
BOOL        SCAD_WINAPI  ApiGetInsertNode( ScadAPI lpAPI, UINT NumElem, UINT NumNodeElem, BYTE *Type, double * Size );
UINT        SCAD_WINAPI  ApiSetInsert( ScadAPI lpAPI, UINT Group, BYTE Type, UINT QntSize, const double * Size, UINT QntElem, const UINT * ListElem );
APICode     SCAD_WINAPI  ApiClearInsert( ScadAPI lpAPI, UINT QntElem, const UINT * ListElem );

// коэффициенты постели
UINT        SCAD_WINAPI  ApiGetQuantityBed( ScadAPI lpAPI );
BOOL        SCAD_WINAPI  ApiGetBedElem( ScadAPI lpAPI, UINT NumElem, BYTE *Type, UINT *QntSize, double * Size );
BOOL        SCAD_WINAPI  ApiGetBed( ScadAPI lpAPI, UINT Num, BYTE *Type, UINT *QntSize, const double ** Size, UINT * QntList, const UINT ** ListElem );	
UINT        SCAD_WINAPI  ApiSetBed( ScadAPI lpAPI, BYTE Group, BYTE Type, UINT QntSize, const double * Size, UINT QntElem, const UINT * ListElem );  // Номер в группе
APICode     SCAD_WINAPI  ApiClearBed( ScadAPI lpAPI, UINT QntElem, const UINT * ListElem );

// системы координат элементов
UINT        SCAD_WINAPI  ApiGetQuantitySystemCoordElem( ScadAPI lpAPI );
BOOL        SCAD_WINAPI  ApiGetSystemCoordElemOne( ScadAPI lpAPI, UINT NumElem, BYTE *Type, UINT *QntSize, double * Size );
BOOL        SCAD_WINAPI  ApiGetSystemCoordElem( ScadAPI lpAPI, UINT Num, BYTE *Type, UINT *QntSize, const double ** Size, UINT * QntList, const UINT ** ListElem );
UINT        SCAD_WINAPI  ApiSetSystemCoordElem( ScadAPI lpAPI, BYTE Group, BYTE Type, UINT QntSize, const double * Size, UINT QntElem, const UINT * ListElem );
APICode     SCAD_WINAPI  ApiClearSystemCoordElem( ScadAPI lpAPI, UINT QntElem, const UINT * ListElem );

UINT        SCAD_WINAPI  ApiGetQuantitySystemCoordEffors( ScadAPI lpAPI );
BOOL        SCAD_WINAPI  ApiGetSystemCoordEfforsOne( ScadAPI lpAPI, UINT NumElem, BYTE *Type, UINT *QntSize, double * Size );
BOOL        SCAD_WINAPI  ApiGetSystemCoordEffors( ScadAPI lpAPI, UINT Num, BYTE *Type, UINT *QntSize, const double ** Size, UINT * QntList, const UINT ** ListElem );
UINT        SCAD_WINAPI  ApiSetSystemCoordEffors( ScadAPI lpAPI, BYTE Group, BYTE Type, UINT QntSize, const double * Size, UINT QntElem, const UINT * ListElem );
APICode     SCAD_WINAPI  ApiClearSystemCoordEffors( ScadAPI lpAPI, UINT QntElem, const UINT * ListElem );

UINT        SCAD_WINAPI  ApiGetJoint( ScadAPI lpAPI, UINT NumElem, UINT NumNodeElem, BYTE * Place );
APICode     SCAD_WINAPI  ApiSetJoint( ScadAPI lpAPI, WORD Mask, UINT NumElem, UINT NumNodeElem, BYTE Place );
APICode     SCAD_WINAPI  ApiDeleteJoint( ScadAPI lpAPI, UINT NumElem, UINT NumNodeElem );
APICode     SCAD_WINAPI  ApiGetRodJoint( ScadAPI lpAPI, UINT NumElem, WORD *JointElastic, WORD * JointInsert );

UINT        SCAD_WINAPI  ApiGetQuantityRigid( ScadAPI lpAPI );
UINT        SCAD_WINAPI  ApiSetRigid( ScadAPI lpAPI, LPCSTR Text );
UINT        SCAD_WINAPI  ApiChangeRigid( ScadAPI lpAPI, UINT Num, LPCSTR Text );

LPCSTR      SCAD_WINAPI  ApiGetRigidName( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiSetRigidName( ScadAPI lpAPI, UINT Num, LPCSTR Name );
APICode     SCAD_WINAPI  ApiSetRigidElem( ScadAPI lpAPI, UINT Num, UINT Qnt, const UINT * ListElem );

UINT        SCAD_WINAPI  ApiGetQuantityLoad( ScadAPI lpAPI );
UINT        SCAD_WINAPI  ApiGetQuantityLoadDyn( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiSetLoadName( ScadAPI lpAPI, UINT Num, LPCSTR Text );    
LPCSTR      SCAD_WINAPI  ApiGetLoadName( ScadAPI lpAPI, UINT Num );    

APICode     SCAD_WINAPI  ApiSetLoadDescription( ScadAPI lpAPI, UINT Num, LPCSTR Text );

APICode     SCAD_WINAPI  ApiSetLoadMass( ScadAPI lpAPI, UINT Num, UINT Qnt, const double * Coef );
APICode     SCAD_WINAPI  ApiSetWeight( ScadAPI lpAPI, UINT Num, UINT Qnt, const UINT * ListElem, double W, BOOL One, BOOL IsInsert);
APICode     SCAD_WINAPI  ApiAppendForce(  ScadAPI lpAPI, UINT Num, BYTE Qw, BYTE Qn, UINT QntData, const double * Data, UINT QntList, const UINT * List );

APICode     SCAD_WINAPI  ApiDeleteForceNode( ScadAPI lpAPI, UINT Num, UINT QntList, const UINT * ListNode );
APICode     SCAD_WINAPI  ApiDeleteForceElem( ScadAPI lpAPI, UINT Num, UINT QntList, const UINT * ListElem );
APICode     SCAD_WINAPI  ApiDeleteLoad( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiClearLoading( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiClearLoad( ScadAPI lpAPI );
UINT        SCAD_WINAPI  ApiGetQuantityForceNode( ScadAPI lpAPI, UINT Num );
UINT        SCAD_WINAPI  ApiGetQuantityForceElem( ScadAPI lpAPI, UINT Num );
APICode     SCAD_WINAPI  ApiGetForceNode( ScadAPI lpAPI, UINT Num, UINT NumPP, BYTE * Qw, BYTE * Qn, UINT * QntData, const double ** Data, UINT * QntList, const UINT ** List );
APICode     SCAD_WINAPI  ApiGetForceElem( ScadAPI lpAPI, UINT Num, UINT NumPP, BYTE * Qw, BYTE * Qn, UINT * QntData, const double ** Data, UINT * QntList, const UINT ** List );

UINT        SCAD_WINAPI  ApiGetQuantityComb( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiGetComb( ScadAPI lpAPI, UINT Num, UINT *QntData, const double **Data );
UINT        SCAD_WINAPI  ApiSetComb( ScadAPI lpAPI, UINT QntData, const double *Data );
APICode     SCAD_WINAPI  ApiChangeComb( ScadAPI lpAPI, UINT Num, UINT QntD, const double *Data );
APICode     SCAD_WINAPI  ApiDeleteRsn( ScadAPI lpAPI );

APICode     SCAD_WINAPI  ApiSetRsu( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiDeleteRsu( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiSetNoCombRsu( ScadAPI lpAPI, BYTE Yes );
BOOL        SCAD_WINAPI  ApiGetNoCombRsu( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiSetListAddRsu( ScadAPI lpAPI, UINT Num, UINT Qnt, const ApiRSU_ADD * List );
APICode     SCAD_WINAPI  ApiSetListExclusionRsu( ScadAPI lpAPI, UINT Num, UINT Qnt, const UINT * List );
APICode     SCAD_WINAPI  ApiSetListFatherRsu( ScadAPI lpAPI, UINT Num, UINT Qnt, const UINT * List );
APICode     SCAD_WINAPI  ApiSetRsuStr( ScadAPI lpAPI, UINT NumStr, APIRsuNew * Rsu );
APICode     SCAD_WINAPI  ApiGetRsuStr( ScadAPI lpAPI, UINT NumStr, APIRsuNew * Rsu );

UINT        SCAD_WINAPI  ApiGetQuantityUnificationRsu( ScadAPI lpAPI );
UINT        SCAD_WINAPI  ApiSetUnificationRsu( ScadAPI lpAPI, WORD Mask, UINT QntElem, const UINT * ListElem );
APICode     SCAD_WINAPI  ApiGetUnificationRsu( ScadAPI lpAPI, UINT NumStr, WORD *Mask, UINT *QntElem, const UINT ** ListElem );

UINT        SCAD_WINAPI  ApiGetQuantityArmElemRod( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiGetArmElemRod( ScadAPI lpAPI, UINT NumStr, const ApiArmRod ** ArmRod );
UINT        SCAD_WINAPI  ApiArmRodAppend( ScadAPI lpAPI, LPCSTR Text, UINT QntStr, const ApiArmElemRod * Data, UINT Qnt, const UINT * Lst );
APICode     SCAD_WINAPI  ApiArmRodReplace( ScadAPI lpAPI, UINT Num, LPCSTR Text, UINT QntStr, const ApiArmElemRod * Data, UINT Qnt, const UINT * Lst );

UINT        SCAD_WINAPI  ApiGetQuantityArmElemPlate( ScadAPI lpAPI );
APICode     SCAD_WINAPI  ApiGetArmElemPlate( ScadAPI lpAPI, UINT NumStr, const ApiArmPlate ** ArmPlate );
UINT        SCAD_WINAPI  ApiArmPlateAppend( ScadAPI lpAPI, LPCSTR Text, const ApiArmElemPlate * Data, UINT Qnt, const UINT * Lst );
APICode     SCAD_WINAPI  ApiArmPlateReplace( ScadAPI lpAPI, UINT Num, LPCSTR Text, const ApiArmPlate * Data, UINT Qnt, const UINT * Lst );

#pragma pack(pop)

#endif
