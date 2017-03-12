#ifndef FILETEXT_FLAG_H
#define FILETEXT_FLAG_H
#pragma pack(push,1)

#include <filebase.h>
#include <stdio.h>

#define LENGTH_BUFFER  1024

class FILETEXT : public FILEBASE {

public :

	    BYTE  Buffer[LENGTH_BUFFER];
	    int   LengthBuffer;
	    int   PosInBuffer;


CLASS_EXPORT   FILETEXT() {   memset(this,0,sizeof(FILETEXT));  };
CLASS_EXPORT  ~FILETEXT() {   Close();  };

int   CLASS_EXPORT    Open( LPCSTR TextFileName, LPCSTR Mode );
void  CLASS_EXPORT    Close();

LPSTR CLASS_EXPORT    GetString( LPSTR Buf, int &LenBuf, int MaxLen=LENGTH_BUFFER );
void  CLASS_EXPORT    PutString( LPSTR );

int   CLASS_EXPORT    ReadString( LPSTR Buf, int &LenBuf, int MaxLen=LENGTH_BUFFER );
int   CLASS_EXPORT    ReadWord( LPCSTR Separate, LPSTR Buf, int &LenBuf, int MAXLENBUF=LENGTH_BUFFER );
int   CLASS_EXPORT    ReadWord( LPSTR Buf, int &LenBuf, int MAXLENBUF=LENGTH_BUFFER );

int   CLASS_EXPORT    GetChar();
void  CLASS_EXPORT    PutChar(int);

};

#pragma pack(pop)
#endif

