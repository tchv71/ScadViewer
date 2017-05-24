#ifndef FILEWORK_FLAG_H
#define FILEWORK_FLAG_H
#pragma pack(push, 1)

#include <filebase.h>

struct FILE_MARK
{
      SYSTEMTIME SystemTime;
      LONGLONG   Length;
      char Text[32-sizeof(SYSTEMTIME)-sizeof(LONGLONG)];
};

class FILEWORK: FILEBASE
{
      FILE_MARK Mark;

public:

void    Init() {  if ( this ) memset(this,0,sizeof(FILEWORK));  };

EXPORT   FILEWORK() {	Init();   };
EXPORT  ~FILEWORK() {   Close();  };

EXPORT void     Open( LPCSTR Name, LPCSTR Atribut );
int    inline   Open( LPCSTR Name, DWORD ReadWrite, DWORD SchareMode, DWORD CreateOpen )
   {  return FILEBASE::Open(Name,ReadWrite,SchareMode,CreateOpen);  };

EXPORT void     Close();
EXPORT void     Delete();

EXPORT void     Read (void *, DWORD );
EXPORT void     Read (void *, DWORD, LONGLONG );
EXPORT void     Write(void *, DWORD );
EXPORT void     Write(void *, DWORD, LONGLONG );
EXPORT void     Put(void *, DWORD, DWORD * =NULL);  // запись по положению
EXPORT void     Add(DWORD, DWORD * =NULL);          // добавить в конец чистое поле

EXPORT void     Put(void *, DWORD, LONGLONG *);  // запись по положению
EXPORT void     Add(DWORD, LONGLONG *);          // добавить в конец чистое поле

EXPORT void     Seek(LONGLONG);
EXPORT void     SeekRead(LONGLONG);
EXPORT void     SeekToEnd();
EXPORT void     SeekToBegin();

EXPORT void     SetLength(LONGLONG Size);

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

EXPORT SYSTEMTIME *    GetTime() {  return &Mark.SystemTime;  };
EXPORT FILE_MARK  *    GetMark() {  return &Mark;  };
EXPORT void            SetMark();

int  inline  FILEWORK::Check(FILE_MARK &Mrk) {
     return memcmp(&Mark,&Mrk,sizeof(FILE_MARK)); };

	friend class FILEBASE;

};
#pragma pack(pop)

#endif

