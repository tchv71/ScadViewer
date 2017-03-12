#ifndef READ_MEMORY_FLAG_H
#define READ_MEMORY_FLAG_H

#pragma pack(push,1)

#include <string.h>
#include <memclass.h>

class READ_MEMORY : MEMORY
{

private:
	 LPSTR 	 Data;
     DWORD   LengthData;
	 DWORD   Pos;

public:

void    (*OutMessage)(int ...);

inline void    Init() {  memset(this,0,sizeof(READ_MEMORY));  };

CLASS_EXPORT  READ_MEMORY()  {  Init();   };
CLASS_EXPORT ~READ_MEMORY()  {  Delete(); };

inline void  Delete () {   if ( Data )  MemoryFree(Data); Data = NULL;   }
CLASS_EXPORT void  Init(void *, DWORD );

CLASS_EXPORT void  Read (void *, DWORD );
CLASS_EXPORT void  Read (void *, DWORD , DWORD );

inline void  Seek( DWORD PosIn )  {  Pos = PosIn;  } 
inline void  SeekToBegin()      {    Pos = 0;  } 

CLASS_EXPORT void  StringRead(LPSTR String,BYTE &Len);
CLASS_EXPORT void  StringRead(LPSTR String);
CLASS_EXPORT void  StringRead(LPSTR *String,MEMORY &);
CLASS_EXPORT void  StringReadLong( LPSTR String,WORD &Len);
CLASS_EXPORT void  StringRead(DWORD &Begin, LPSTR String, BYTE &LenString);

inline DWORD    GetPosition()   {   return Pos;           };
inline DWORD    GetLength(void) {   return LengthData;    };

inline void            SetFileError(void(*FileErr) (int ...)) {  OutMessage = FileErr;  }

LPSTR CLASS_EXPORT    GetString( LPSTR Buf, int &LenBuf, int MaxLen=LENGTH_BUFFER );

int   CLASS_EXPORT    ReadString( LPSTR Buf, int &LenBuf, int MaxLen=LENGTH_BUFFER );
int   CLASS_EXPORT    ReadWord( LPCSTR Separate, LPSTR Buf, int &LenBuf, int MAXLENBUF=LENGTH_BUFFER );
int   CLASS_EXPORT    ReadWord( LPSTR Buf, int &LenBuf, int MAXLENBUF=LENGTH_BUFFER );

int   CLASS_EXPORT    GetChar();

};

#endif
