#ifndef STEP_DATA__H
#define STEP_DATA__H
#pragma pack(push,1)

struct STEP_GROUP
{
	   WORD         NumLoad;
       WORD         QuantityDelta;
       BYTE         YesSave;
	   BYTE         Res[3]; 
       double       Delta;
};

struct STEP_STR {
	   LPSTR        Text;
	   int          QuantityGroup;
	   STEP_GROUP * Group;
	   BYTE         Method;
	   BYTE         ClearBegin;
	   WORD         MaxIter;
	   WORD         NumLoadDyn;
	   BYTE         YesStabil;
	   BYTE         Res;
};

struct STEP_DOC_WORK
{
	   LPSTR        Text;
	   int          QuantityGroup;
	   STEP_GROUP   Group[10000];
	   BYTE         Method;
	   BYTE         ClearBegin;
	   WORD         MaxIter;
	   WORD         NumLoadDyn;
	   BYTE         YesStabil;
	   BYTE         Res;
};

struct STEP_GROUP_OLD
{
	short NumLoad;
	short QuantityDelta;
	float Delta;
	BYTE  YesSave;
};

struct STEP_DOC_OLD
{
	short          Method;
	short          MaxIter;
	short          ClearBegin;
	short          QuantityGroup;
	STEP_GROUP_OLD Group[100];
};

class SCAD_STEP: public SCAD_BASE_CLASS
{
	
public:
	
	SCAD_STEP()      {  Init();  }
   ~SCAD_STEP(void)  {  Destroy();  }
	
void                 Init()  {  SCAD_BASE_CLASS::Init(0,0,8,8,1,20);  LenData[0] = sizeof(STEP_GROUP);  }

STEP_STR *           Get( int Num ) { return (STEP_STR *)GetObject(Num);  }     

int   SCHEMA_EXPORT  Add( STEP_DOC_OLD & );  
int   SCHEMA_EXPORT  Add( STEP_DOC_WORK & );  
void  SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, LPSTR Buf, BYTE & Control );

void  SCHEMA_EXPORT  Export( FILEPRINT &Work );
void  SCHEMA_EXPORT  Print( void *Inp );

};

struct STEP_LOAD
{
	BYTE         Clear;
	BYTE         YesSave;
	BYTE         Method;
	BYTE         Res;
	WORD         MaxIter;
	WORD         NumLoadStep;
	WORD         NumStep;
	WORD         NumLoadForce;
	double       Delta;
};

#pragma pack(pop)
#endif
