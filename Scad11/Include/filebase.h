#ifndef FILEBASE_FLAG_H
#define FILEBASE_FLAG_H
#pragma pack(push,1)

#include <string.h>
#include <memclass.h>

class FILEBASE {
	
private:
	char       FileName[MAXPATH+1];
	HANDLE     Handle;
	BYTE       YesRead;
	BYTE       YesWrite;
	LONGLONG   LengthFile;
	LONGLONG   PosByteRead;
	LONGLONG   PosSeek;
	
public:
	
void    (*OutMessage)(int ...);
	
void    Init() {  FileName[0] = 0;  Handle = 0;
                  OutMessage = NULL;
                  YesRead = YesWrite = 0; LengthFile = 0;  PosByteRead = 0;  PosSeek = -1;  }
	
CLASS_EXPORT  FILEBASE()  {   Init();   };
CLASS_EXPORT ~FILEBASE()  {   Close();  };
	
int   CLASS_EXPORT   Open( LPCSTR Name, LPCSTR Atribut );
int   CLASS_EXPORT   Open( LPCSTR Name, DWORD ReadWrite, DWORD SchareMode, DWORD CreateOpen );
void  CLASS_EXPORT   Close();
void  CLASS_EXPORT   Delete();
	
void  CLASS_EXPORT   Read (void *, DWORD );
void  CLASS_EXPORT   Read (void *, DWORD , LONGLONG );
void  CLASS_EXPORT   Write(void *, DWORD );               // запись в конец
void  CLASS_EXPORT   Write(void *, DWORD , LONGLONG );
void  CLASS_EXPORT   Put(void *, DWORD , LONGLONG * );  // запись по положению
void  CLASS_EXPORT   Add(DWORD, LONGLONG * );          // добавить в конец чистое поле
	
void  CLASS_EXPORT   Put(void *, DWORD  , DWORD * =NULL);  // запись по положению
void  CLASS_EXPORT   Add(DWORD , DWORD * =NULL);          // добавить в конец чистое поле
void  CLASS_EXPORT   AddFile( FILEBASE &, LONGLONG PosBegin=0, LONGLONG PosEnd =0 );          // добавить в конец данные из файла
void  CLASS_EXPORT   AddFile( LPCSTR Name ); // добавить в конец данные из файла
	
void  CLASS_EXPORT   Seek(LONGLONG);
void  CLASS_EXPORT   SeekRead(LONGLONG);
void  CLASS_EXPORT   SeekToEnd();
void  CLASS_EXPORT   SeekToBegin();
	
void  CLASS_EXPORT   SetLength(LONGLONG Size);
void  CLASS_EXPORT   Flush();
	
void  CLASS_EXPORT   StringWrite(LPCSTR String);
void  CLASS_EXPORT   StringWrite(LPCSTR String,WORD Length);
void  CLASS_EXPORT   StringRead(LPSTR String,BYTE &Len);
void  CLASS_EXPORT   StringReadLong(LPSTR String,WORD &Len);
void  CLASS_EXPORT   StringRead(LPSTR String);
void  CLASS_EXPORT   StringRead(LPSTR *String,MEMORY &);
void  CLASS_EXPORT   StringRead(DWORD &Begin, LPSTR String, BYTE &LenString);
void  CLASS_EXPORT   StringRead(LONGLONG &Begin, LPSTR String, BYTE &LenString);
	
inline HANDLE        GetHandle()     {   return Handle;        }
inline LPCSTR        GetFileName()   {   return FileName;      }

inline LONGLONG      GetPosRead()    {   return PosByteRead;   }
inline LONGLONG      GetPosition()   {   return PosSeek;       };
inline LONGLONG      GetLength(void) {   return LengthFile;    };
inline void          SetFileError(void(*FileErr) (int ...)) {  OutMessage = FileErr;  }
inline int           AttributeRead()  {  return YesRead;   }
inline int           AttributeWrite() {  return YesWrite;  }
	
friend class FILETEXT;
friend class FILEPRINT;
friend class FILEMARK;
friend class FILEWORK;
	
};

#pragma pack(pop)
#endif
