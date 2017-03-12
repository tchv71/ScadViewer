#ifndef DATA_RIGID_ONESIDED_FLAG_H
#define DATA_RIGID_ONESIDED_FLAG_H
#pragma pack(push,1)

#include <schema.hpp>
#include <rgd_osd.hpp>

class DATA_RIGID_ONESIDED : MEMORY {

      SCHEMA        * Schem;
      DATA_RIGID    * SchemaRigid;
      IDENTIFICATOR   Ident;

public:

      char            Name[512];
      int             NumRgd;

      D3OSD           Osd;
	  double          End;
	  
   DATA_RIGID_ONESIDED()      {  Init();    }
  ~DATA_RIGID_ONESIDED(void)  {  Delete();  }

void  SCHEMA_EXPORT  Init();
void  SCHEMA_EXPORT  Delete();

void  SCHEMA_EXPORT  SetPointer( SCHEMA &, DATA_RIGID & );

void  SCHEMA_EXPORT  Get( int NumRgd );

int   SCHEMA_EXPORT  Set( int Num=0);

};

#pragma pack(pop)
#endif
