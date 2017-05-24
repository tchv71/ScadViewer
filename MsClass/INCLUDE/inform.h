#ifndef INFORM_FLAG_H
#define INFORM_FLAG_H
#pragma pack(push, 1)

#include "filetext.h"
#include "crash.h"

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

EXPORT 	 void   Init();
EXPORT 	 void   Error(LPCSTR,long);

public:

EXPORT      INFORM() { Init(); };
EXPORT      INFORM(LPCSTR FileName) { Init(FileName); };
EXPORT      ~INFORM() {   Delete();  };

EXPORT void    SetNumBase( int Num ) {  NumBase = (WORD)Num;  };
EXPORT int     Init(LPCSTR FileName, int Num=0 );
EXPORT void    Delete();
EXPORT void    Code(LPCSTR,LPCSTR);
EXPORT TEXT_INFORM FAR * Load(int);

EXPORT int     InformIn(int Num);

};
#pragma pack(pop)

#endif