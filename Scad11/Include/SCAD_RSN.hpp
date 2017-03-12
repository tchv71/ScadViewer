#ifndef SCAD_RSN_FLAG_H
#define SCAD_RSN_FLAG_H
#pragma pack(push,1)

#include <classwin.hpp>
#include <BaseClass.hpp>

struct RSN_STR {
       LPSTR            Text;
       int              Quantity;
       double         * Data;
       LPSTR            FullName;
       double         * FullData;
};

class SCAD_RSN: public SCAD_BASE_CLASS
{

public:

	SCAD_RSN()      {  Init();  }
  ~SCAD_RSN(void)  {  Destroy();  }

void          Init()  {  SCAD_BASE_CLASS::Init(0,0,2*sizeof(void*),0,1,20);  LenData[0] = sizeof(double);  }

void  SCHEMA_EXPORT  Delete(int Num);
void  SCHEMA_EXPORT  Delete();
void  SCHEMA_EXPORT  Destroy();

void  SCHEMA_EXPORT  Read(  FILEBASE &Work, DOCUMENT &Out );
void  SCHEMA_EXPORT  Write( FILEBASE &Work, DOCUMENT &Out );

void  SCHEMA_EXPORT  SetInf();

void  SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, LPSTR Buf, BYTE & Control );

int   SCHEMA_EXPORT  Add( LPSTR Name, int QntD, double *DLst );

void  SCHEMA_EXPORT  Change( int Num, LPSTR Name, int QntD, double *DLst );

RSN_STR *  Get(int Num) {  return (RSN_STR *)SCAD_BASE_CLASS::GetObject(Num); }

void  SCHEMA_EXPORT  Export( FILEPRINT &Work );

void  SCHEMA_EXPORT  PrintRSN( void *Inp);

void  SCHEMA_EXPORT  Copy( SCAD_RSN *);
void  SCHEMA_EXPORT  CheckQuantityLoad( int QntLoad);

};

#pragma pack(pop)
#endif

