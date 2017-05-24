#ifndef FILEBASE_FLAG_H
#define FILEBASE_FLAG_H
#pragma pack(push, 1)
#include <windows.h>
#include <defclass.h>
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

void    Init() {  if ( this ) memset(this,0,sizeof(FILEBASE));  };

EXPORT  FILEBASE() {	 Init();  };
EXPORT ~FILEBASE() {   Close();  };

EXPORT void     Open( LPCSTR Name, LPCSTR Atribut );
EXPORT int      Open( LPCSTR Name, DWORD ReadWrite, DWORD SchareMode, DWORD CreateOpen );
EXPORT void     Close();
EXPORT void     Delete();

EXPORT void     Read (void *, DWORD );
EXPORT void     Read (void *, DWORD , LONGLONG );
EXPORT void     Write(void *, DWORD );               // за???? ? ?он??
EXPORT void     Write(void *, DWORD , LONGLONG );
EXPORT void     Put(void *, DWORD , LONGLONG * );  // за???? ?о ?олож?н??
EXPORT void     Add(DWORD, LONGLONG * );          // до?а???? ? ?он?? ????о? ?ол?

EXPORT void     Put(void *, DWORD  , DWORD * =NULL);  // за???? ?о ?олож?н??
EXPORT void     Add(DWORD , DWORD * =NULL);          // до?а???? ? ?он?? ????о? ?ол?

EXPORT void     Seek(LONGLONG);
EXPORT void     SeekRead(LONGLONG);
EXPORT void     SeekToEnd();
EXPORT void     SeekToBegin();

EXPORT void     SetLength(LONGLONG Size);
EXPORT void     Flush();

EXPORT void     StringWrite(LPCSTR String);
EXPORT void     StringWrite(LPCSTR String,WORD Length);
EXPORT void     StringRead(LPSTR String,BYTE &Len);
EXPORT void     StringRead(LPSTR String);
EXPORT void     StringRead(LPSTR *String,MEMORY &);
EXPORT void     StringRead(DWORD &Begin, LPSTR String, BYTE &LenString);
EXPORT void     StringRead(LONGLONG &Begin, LPSTR String, BYTE &LenString);
EXPORT void     StringReadLong(LPSTR String,WORD &Len);

inline HANDLE   GetHandle()     {   return Handle;        }
inline LPCSTR   GetFileName()   {   return FileName;      }

inline LONGLONG GetPosRead()    {   return PosByteRead;   }
inline LONGLONG GetPosition()   {   return PosSeek;       };
inline LONGLONG GetLength(void) {   return LengthFile;    };

inline void     SetFileError(void(*FileErr) (int ...)) {  OutMessage = FileErr;  }

	friend class FILETEXT;
	friend class FILEPRINT;
	friend class FILEMARK;

};
#pragma pack(pop)

#endif