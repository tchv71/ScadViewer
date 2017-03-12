#ifndef MESSAGE_LIB_FLAG_H
#define MESSAGE_LIB_FLAG_H
#pragma pack(push,1)

#include "inform.h"
#include "fileprnt.h"

class MESSAGE_LIB : MEMORY

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

void    CLASS_EXPORT   Init();

public:

 CLASS_EXPORT       MESSAGE_LIB()  {  Init(); };
 CLASS_EXPORT      ~MESSAGE_LIB() {  Delete(); };
void  CLASS_EXPORT Init( LPCSTR NameFileMessage, LPCSTR NameFilePrint, LPCSTR Mode,
					WORD PageH,WORD PageW, WORD NumMsgError );
void  CLASS_EXPORT Delete();

	 inline int  GetQuantityError()   { return QuantityError;  }
	 inline int  GetQuantityWarning() { return QuantityWarning;  }
	 inline void SetEdit(short Type)  { Print.SetEdit(1);  }
	 inline void SetOutputBin(BYTE Out)  {  OutputBin = Out;  }

void  CLASS_EXPORT Put(int Num ...);
void  CLASS_EXPORT PutList( int Begin, int End,BYTE FAR *Inf,WORD NumInform );
void  CLASS_EXPORT PutList( int Begin, int End,BYTE FAR *Inf,WORD NumInform, WORD Num );
void  CLASS_EXPORT PutList( int Begin, int End,BYTE FAR *Inf,WORD NumInform, LPCSTR Text);

void  CLASS_EXPORT Error(int);

};

#pragma pack(pop)
#endif
