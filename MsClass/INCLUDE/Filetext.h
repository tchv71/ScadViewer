#ifndef FILETEXT_FLAG_H
#define FILETEXT_FLAG_H
#pragma pack(push, 1)
#include <fileBASE.h>
#include <stdio.h>

#define LENGTH_BUFFER  1024

class FILETEXT : public FILEBASE {

public :

	    BYTE  Buffer[LENGTH_BUFFER];
	    int   LengthBuffer;
	    int   PosInBuffer;


EXPORT   FILETEXT() {   memset(this,0,sizeof(FILETEXT));  };
EXPORT  ~FILETEXT() {   Close();  };

EXPORT  void     Open( LPCSTR TextFileName, LPCSTR Mode );
EXPORT  void     Close();

EXPORT LPSTR     GetString( LPSTR Buf, int &LenBuf, int MaxLen=LENGTH_BUFFER );
EXPORT void      PutString( LPSTR );

EXPORT int       ReadString( LPSTR Buf, int &LenBuf, int MaxLen=LENGTH_BUFFER );
EXPORT int       ReadWord( LPCSTR Separate, LPSTR Buf, int &LenBuf, int MAXLENBUF=LENGTH_BUFFER );
EXPORT int       ReadWord( LPSTR Buf, int &LenBuf, int MAXLENBUF=LENGTH_BUFFER );

EXPORT int       GetChar();
EXPORT void      PutChar(int);

};
#pragma pack(pop)

#endif
