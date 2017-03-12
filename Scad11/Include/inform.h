#ifndef INFORM_FLAG_H
#define INFORM_FLAG_H
#pragma pack(push,1)

#include "filetext.h"

struct ACCESS {
	     DWORD Pos;               /*   позиция в файле               */
	     WORD Length;             /*   длина сообщения               */
	     };

struct TEXT_INFORM {
	     WORD Length;              //   длина сообщени
	     BYTE QuantityString;      //   число стpок сообщени
	     LPSTR Point;
	     BYTE Type;                //   тип   сообщени
	     LPSTR Text;               //   стpоки сообщени
	     };

class INFORM : MEMORY
{

private:

	 short   MinNumInform;        //   начальный номеp фpазы
	 short   MaxNumInform;        //   конечный  номеp фpазы
	 DWORD   PosAccess;           //   позиция в файле Access
	 WORD    MaxLength;           //   max длина инфоpмации
	 WORD    NumBase;             //   вазовый номер
         ACCESS  FAR * Access;
	 TEXT_INFORM Inform;          //   и его стpуктуpа
	 FILEBASE FileWork;

     void  CLASS_EXPORT   Init();
     void  CLASS_EXPORT   Error(LPCSTR,long);

public:

 CLASS_EXPORT      INFORM() { Init(); };
 CLASS_EXPORT      INFORM(LPCSTR FileName) { Init(FileName); };
 CLASS_EXPORT      ~INFORM() {   Delete();  };

void  CLASS_EXPORT   SetNumBase( int Num ) {  NumBase = (WORD)Num;  };
int   CLASS_EXPORT   Init(LPCSTR FileName, int Num=0 );
void  CLASS_EXPORT   Delete();
void  CLASS_EXPORT  Code(LPCSTR,LPCSTR);
CLASS_EXPORT TEXT_INFORM * Load(int);

int  CLASS_EXPORT InformIn(int Num);

};

#pragma pack(pop)
#endif
