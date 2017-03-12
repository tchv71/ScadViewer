#ifndef SCAD_HISTORY__FLAG_H
#define SCAD_HISTORY__FLAG_H

#pragma pack(push,1)

#include <BaseClass.hpp>

struct SCAD_HISTORY_STR {
       LPSTR Text;
       BASE_DATA    BaseData[1];
       SYSTEMTIME   Time;
};

class  SCAD_HISTORY : public SCAD_BASE_CLASS
{

public:

 	SCAD_HISTORY()      {  Init();  }
  ~SCAD_HISTORY(void)  {  SCAD_BASE_CLASS::Destroy();  }

void                 Init()  {  SCAD_BASE_CLASS::Init(0,0,sizeof(SYSTEMTIME),sizeof(SYSTEMTIME),1,20);  }

int          SCHEMA_EXPORT  Add( void *Schem, LPSTR Text );
int          SCHEMA_EXPORT  Restor( int Num, void *Schem );

void         SCHEMA_EXPORT  Read( void *Schem );
void         SCHEMA_EXPORT  Write( void *Schem );

SCHEMA_EXPORT  SYSTEMTIME * GetTime( int Num );
int          SCHEMA_EXPORT  YesSave( int Num );
void         SCHEMA_EXPORT  DeleteSave( int Num );

};

#pragma pack(pop)
#endif

