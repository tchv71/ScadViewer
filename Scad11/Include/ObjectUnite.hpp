#ifndef OBJECT_UNITE_FLAG_H
#define OBJECT_UNITE_FLAG_H
#pragma pack(push,1)

#include "classwin.hpp"

struct UNITE_STR
{
     LPSTR       Text;
     void      * Schem;
     int         NumLoadBegin;
	 int         NumLoadCalcBegin;
     int         NumElemBegin;
};

class UNITE_SCHEMA : public SCAD_BASE_CLASS
{
public:

     int         MaxNode;
     int         MaxElem;
     int         NumSchemaLoad;
     void      * Schem;
	 
 	UNITE_SCHEMA()      {  Init();    }
  ~UNITE_SCHEMA(void)   {  Destroy();  }

void           Init()  {  SCAD_BASE_CLASS::Init(0,0,sizeof(UNITE_STR)-sizeof(LPSTR),0,0,10);
                          MaxNode = MaxElem = NumSchemaLoad = 0; 						  
						  Schem = NULL;   }

inline void SetSchema( void *Sch )  {  Schem = Sch; }
void  SCHEMA_EXPORT   Delete();
void  SCHEMA_EXPORT   Delete( int Num );

void  SCHEMA_EXPORT   Destroy();
SCHEMA_EXPORT  UNITE_STR *  Get( int Num ) {  return (UNITE_STR*)GetObject(Num);  }

SCHEMA_EXPORT  int   Read( FILEBASE &Input, DOCUMENT & , int Type );

SCHEMA_EXPORT  int   SetInf();

SCHEMA_EXPORT  int   Add( LPSTR Name, int TypeRead=0, int Type=1 );
SCHEMA_EXPORT  void  Include( LPSTR Sent, DWORD Len, BYTE &Control );
SCHEMA_EXPORT  void  Print( void *Inp );

};

#pragma pack(pop)
#endif

