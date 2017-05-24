#ifndef RESURCE_TEXT_FLAG_H
#define RESURCE_TEXT_FLAG_H
#pragma pack(push, 1)

#include <defclass.h>

class RESURCE_TEXT
{

private:

         HINSTANCE hString;
         char      Text[1024];

EXPORT 	 void  Init();

public:

EXPORT        RESURCE_TEXT() { Init(); };
EXPORT        RESURCE_TEXT(LPCSTR FileName) { Init(FileName); };
EXPORT       ~RESURCE_TEXT() {   Delete();  };

EXPORT void   Init(LPCSTR FileName );
EXPORT void   Delete();

EXPORT LPCSTR   GetText(int Num, int &LengthText, BYTE Type=1 );
EXPORT LPCSTR   GetString(int Num, int &LengthText );

};

#pragma pack(pop)
#endif