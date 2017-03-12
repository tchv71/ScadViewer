#ifndef FILEWORK_FLAG_H
#define FILEWORK_FLAG_H
#pragma pack(push,1)

#include <filebase.h>

struct FILE_MARK
{
      SYSTEMTIME SystemTime;
      LONGLONG   Length;
      char Text[32-sizeof(SYSTEMTIME)-sizeof(LONGLONG)];
};

class FILEWORK: public FILEBASE
{
      FILE_MARK Mark;

public:

void    Init() {  memset(&Mark,0,sizeof(FILE_MARK)); FILEBASE::Init();   };

CLASS_EXPORT FILEWORK() { Init();   };
CLASS_EXPORT PASCAL ~FILEWORK() {   Close();  };

int   CLASS_EXPORT  Open( LPCSTR Name, LPCSTR Atribut );
int    inline   Open( LPCSTR Name, DWORD ReadWrite, DWORD SchareMode, DWORD CreateOpen )
   {  return FILEBASE::Open(Name,ReadWrite,SchareMode,CreateOpen);  };

void  CLASS_EXPORT  Close();
void  CLASS_EXPORT  Delete();

void  CLASS_EXPORT  Read (void *, DWORD );
void  CLASS_EXPORT  Read (void *, DWORD, LONGLONG );
void  CLASS_EXPORT  Write(void *, DWORD );
void  CLASS_EXPORT  Write(void *, DWORD, LONGLONG );
void  CLASS_EXPORT  Put(void *, DWORD, DWORD * =NULL); 
void  CLASS_EXPORT  Add(DWORD, DWORD * =NULL);          

void  CLASS_EXPORT  Put(void *, DWORD, LONGLONG *);  
void  CLASS_EXPORT  Add(DWORD, LONGLONG *);   
      

void  CLASS_EXPORT  Seek(LONGLONG);
void  CLASS_EXPORT  SeekRead(LONGLONG);
void  CLASS_EXPORT  SeekToEnd();
void  CLASS_EXPORT  SeekToBegin();

void  CLASS_EXPORT  SetLength(LONGLONG Size);
void  CLASS_EXPORT  AddFile( FILEWORK &, LONGLONG PosBegin=0, LONGLONG PosEnd =0 );          // добавить в конец данные из файла
void  CLASS_EXPORT  AddFile( LPCSTR Name ); // добавить в конец данные из файла

void inline     StringWrite(LPCSTR String) { FILEBASE::StringWrite(String);  };
void inline     StringWrite(LPCSTR String,WORD Length) { FILEBASE::StringWrite(String,Length);  };
void inline     StringRead(LPSTR String,BYTE &Len) { FILEBASE::StringRead(String,Len);  };
void inline     StringRead(LPSTR String) { FILEBASE::StringRead(String);  };
void inline     StringRead(LPSTR *String,MEMORY &Mem) { FILEBASE::StringRead(String,Mem);  };
void inline     StringRead(DWORD &Begin, LPSTR String, BYTE &LenString)
               { FILEBASE::StringRead(Begin,String,LenString);  };
void inline     StringRead(LONGLONG &Begin, LPSTR String, BYTE &LenString)
               { FILEBASE::StringRead(Begin,String,LenString);  };

void inline            Flush() {  FILEBASE::Flush();  };

inline  HANDLE         GetHandle()     {   return FILEBASE::GetHandle();    }
inline  LPCSTR         GetFileName()   {   return FILEBASE::GetFileName();  }

inline  LONGLONG       GetPosRead()  {   return FILEBASE::GetPosRead()-32;   }
inline  LONGLONG       GetPosition() {   return FILEBASE::GetPosition()-32;  };
inline  LONGLONG       GetLength()   {   return FILEBASE::GetLength()-32;    };

CLASS_EXPORT SYSTEMTIME *    GetTime() {  return &Mark.SystemTime;  };
CLASS_EXPORT FILE_MARK  *    GetMark() {  return &Mark;  };
CLASS_EXPORT void            SetMark();

int  inline  FILEWORK::Check(FILE_MARK &Mrk) {
     return memcmp(&Mark,&Mrk,sizeof(FILE_MARK)); };

	friend class FILEBASE;

};

#pragma pack(pop)
#endif


