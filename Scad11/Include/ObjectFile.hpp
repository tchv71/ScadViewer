#ifndef OBJECT_FILE_FLAG_H
#define OBJECT_FILE_FLAG_H

#pragma pack(push,1)
#include <BaseClass.hpp>

struct OBJECT_FILE_STR {
       LPSTR Text;
       BASE_DATA    BaseData[1];
};

class OBJECT_FILE : public SCAD_BASE_CLASS
{

public:

 	OBJECT_FILE()      {  Init();  }
  ~OBJECT_FILE(void)  {  Destroy();  }

void   Init()  {  SCAD_BASE_CLASS::Init(0,0,0,0,1,20);  }

void   Copy( OBJECT_FILE &LF ) {  SCAD_BASE_CLASS::Copy((SCAD_BASE_CLASS*)&LF);  }

int    Add( LPSTR NameFile, int &CodeReturn ) {  return SCAD_BASE_CLASS::AddFile(1,NameFile,CodeReturn);  }

int   CLASS_EXPORT  Add( LPSTR Sent, DWORD LenSent, int &Control );

void   Change( int Num, LPSTR NameFile, int &CodeReturn ) {  SCAD_BASE_CLASS::ChangeFile(Num,1,NameFile,CodeReturn);  }

OBJECT_FILE_STR * Get() { return (OBJECT_FILE_STR*)SCAD_BASE_CLASS::GetObject(1);  }

CLASS_EXPORT OBJECT_FILE_STR * Get(int Num, LPSTR BaseFile=NULL );

CLASS_EXPORT  void  Get( int Num, LPSTR *NameFile, int *Length, void **DataFile );
void   ModifyFile() {  SCAD_BASE_CLASS::ModifyFile(1);  }

CLASS_EXPORT  void  Export( int NumDoc, FILEPRINT &Work  );
CLASS_EXPORT  void  Export( int NumDoc, FILEPRINT &Work, char Begin, char EndStr, char End );

CLASS_EXPORT  void  Check( LPSTR FileBase, LPSTR Text );
CLASS_EXPORT  void  SetDisk( LPSTR FileBase, LPSTR Text );

};

#pragma pack(pop)
#endif

