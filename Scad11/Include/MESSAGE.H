#ifndef MESSAGE_FLAG_H
#define MESSAGE_FLAG_H
#pragma pack(push,1)

#include "fileprnt.h"
#include "rc_text.h"

class MESSAGE : MEMORY
{

private:
	 WORD      QuantityWarning;
	 WORD      QuantityError;
    WORD      NumMessageError;
	 BYTE      OutputBin;

public:
	 RESURCE_TEXT  * Inform;
	 RESURCE_TEXT    InformIn;

	 FILEPRINT Print;

CLASS_EXPORT void   Init();

public:

CLASS_EXPORT   MESSAGE()  {  Init(); };
CLASS_EXPORT     ~MESSAGE() {  Delete(); };
void  CLASS_EXPORT Init( LPCSTR NameFileMessage, LPCSTR NameFilePrint,
               int PageH, int PageW, BYTE ListYes, int NumMsgError  );

void  CLASS_EXPORT Init( RESURCE_TEXT  * , LPCSTR NameFilePrint,
               int PageH, int PageW, BYTE ListYes, int NumMsgError  );

void  CLASS_EXPORT Delete();

	 inline int  GetQuantityError()   { return QuantityError;  }
	 inline int  GetQuantityWarning() { return QuantityWarning;  }
	 inline void SetEdit(short Type)  { Print.SetEdit(1);  }
	 inline void SetOutputBin(BYTE Out)  {  OutputBin = Out;  }

void  CLASS_EXPORT Put(int Num ...);
void  CLASS_EXPORT PutList( int Begin, int End,BYTE FAR *Inf, WORD NumInform);
void  CLASS_EXPORT PutList( int Begin, int End,BYTE FAR *Inf, WORD NumInform, int  );
void  CLASS_EXPORT PutList( int Begin, int End,BYTE FAR *Inf, WORD NumInform, char * );

void  CLASS_EXPORT Error(int);

};

#pragma pack(pop)
#endif
