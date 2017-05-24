#ifndef MESSAGE_FLAG_H
#define MESSAGE_FLAG_H
#pragma pack(push, 1)
#include "inform.h"
#include "fileprnt.h"

class MESSAGE : MEMORY

{

private:
	 WORD      QuantityWarning;
	 WORD      QuantityError;
	 WORD      NumMessageError;
	 BYTE      OutputBin;

public:
	 INFORM    Inform;

private:
	 FILEPRINT Print;

EXPORT void    Init();

public:

EXPORT     MESSAGE()  {  Init(); };
EXPORT    ~MESSAGE() {  Delete(); };
EXPORT void  Init( LPCSTR NameFileMessage, LPCSTR NameFilePrint, LPCSTR Mode,
					HWND Hwnd, LPCSTR FontNm,	 BYTE FntSize,
					WORD PageH,WORD PageW,WORD TextH,WORD TextW,WORD Left,WORD Top,
					WORD NumMsgError );
EXPORT void  Init( LPCSTR NameFileMessage, LPCSTR NameFilePrint, LPCSTR Mode,
					WORD PageH,WORD PageW,WORD TextH,WORD TextW,WORD Left,WORD Top,
					WORD NumMsgError );
EXPORT void  Delete();

	 inline int  GetQuantityError()   { return QuantityError;  }
	 inline int  GetQuantityWarning() { return QuantityWarning;  }
	 inline void SetEdit(short Type)  { Print.SetEdit(1);  }
	 inline void SetOutputBin(BYTE Out)  {  OutputBin = Out;  }

EXPORT void  Put(int Num ...);
EXPORT void  PutList( int Begin, int End,BYTE FAR *Inf,WORD NumInform);
EXPORT void  PutList( int Begin, int End,BYTE FAR *Inf,WORD NumInform,WORD Num);
EXPORT void  PutList( int Begin, int End,BYTE FAR *Inf,WORD NumInform,LPCSTR Text);

EXPORT void  Error(int);

};

#pragma pack(pop)
#endif