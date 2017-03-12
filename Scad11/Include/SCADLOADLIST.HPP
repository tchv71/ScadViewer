#ifndef SCAD_LOAD_LIST_FLAG_H
#define SCAD_LOAD_LIST_FLAG_H
#pragma pack(push,1)

#include "classwin.hpp"
#include "ScadLoad.hpp"
#include "ObjectDouble.hpp"

struct LOAD_LIST_STR
{
       LPSTR          Name;
       SCAD_LOAD      Load;
};

struct MAP_FORCE_STR {  int NumLoad;  int NumStr;  };
struct MAP_FORCE
{
       int             Quantity;
       MAP_FORCE_STR * MapStr;
};

class SCAD_LOAD_LIST: public SCAD_BASE_CLASS
{
public:

   OBJECT_FILE   * ListFile;
   OBJECT_DOUBLE * Mass;

 	SCAD_LOAD_LIST()      {  Init();    }
  ~SCAD_LOAD_LIST(void)  {  Destroy();  }

SCHEMA_EXPORT void    Init();

SCHEMA_EXPORT void    SetClass( OBJECT_FILE *LF, OBJECT_DOUBLE *Ms );

SCHEMA_EXPORT void    Delete();
SCHEMA_EXPORT void    Delete( int Num );

SCHEMA_EXPORT void    Destroy();
SCHEMA_EXPORT LPSTR   GetName( int Num ) {  return GetText(Num);  }
SCHEMA_EXPORT void    SetName( int Num, LPSTR Text ) {  SetText(Num,Text);  }

SCHEMA_EXPORT int     Add( int Quantity );

SCHEMA_EXPORT void    Clear( int Num );

SCHEMA_EXPORT void    Read( FILEBASE &Input, DOCUMENT & );
SCHEMA_EXPORT void    Read( int NumLoad, SCAD_LOAD &LoadStrOut );

SCHEMA_EXPORT void    Write( FILEBASE &Output, DOCUMENT &Doc );
SCHEMA_EXPORT void    Write( int NumLoad, LPSTR Name, SCAD_LOAD &LoadStrInput );

SCHEMA_EXPORT SCAD_LOAD * Get( int Num, LPSTR *Name = NULL );

SCHEMA_EXPORT void    DeleteForce( int Type, int  Quantity, int List[] );
void           DeleteForceNode( int Num ) {  DeleteForce(0,1,&Num);  }
void           DeleteForceElem( int Num ) {  DeleteForce(1,1,&Num);  }
void           DeleteMass( int Num ) {  DeleteForce(2,1,&Num);  }
void           DeleteForceNode( int  Quantity, int List[]  ) {  DeleteForce(0,Quantity,List);  }
void           DeleteForceElem( int  Quantity, int List[]  ) {  DeleteForce(1,Quantity,List);  }
void           DeleteMass( int  Quantity, int List[]  ) {  DeleteForce(2,Quantity,List);  }

SCHEMA_EXPORT  void   Copy( SCAD_LOAD_LIST *SLL );

SCHEMA_EXPORT  void   MapForce( int Type, int MaxNumber, MAP_FORCE ** );
SCHEMA_EXPORT  void   MapForceDelete( int MaxNumber, MAP_FORCE *& );

void           Compress( int EqualName, int OldQuantityNode, int NumNode[], int OldQuantityElem, int NumElem[] );

SCAD_LOAD_LIST & operator = ( SCAD_LOAD_LIST &SLL ) {
	   Copy(&SLL);
	   return *this;	}

};

#pragma pack(pop)
#endif

