#ifndef RESURCE_TEXT_FLAG_H
#define RESURCE_TEXT_FLAG_H
#pragma pack(push,1)

struct RESURCE_INFORM {
	     WORD  Length;              //   длина сообщени
	     BYTE  QuantityString;      //   число стpок сообщени
	     BYTE  Type;                //   тип   сообщени
	     LPSTR Text;                //   стpоки сообщени
};

class RESURCE_TEXT
{

private:

        HINSTANCE      hString;
        char           Text[4096];
        RESURCE_INFORM RI;

     void  CLASS_EXPORT   Init();

public:

 CLASS_EXPORT      RESURCE_TEXT() { Init(); };
 CLASS_EXPORT      RESURCE_TEXT(LPCSTR FileName) { Init(FileName); };
 CLASS_EXPORT      ~RESURCE_TEXT() {   Delete();  };

void  CLASS_EXPORT     Init(LPCSTR FileName );
void  CLASS_EXPORT     Delete();

LPCSTR  CLASS_EXPORT    GetText(int Num, int &LengthText, BYTE Type=1 );
LPCSTR  CLASS_EXPORT    GetString(int Num, int &LengthText );
CLASS_EXPORT  RESURCE_INFORM * GetMsg( int Num );
CLASS_EXPORT  RESURCE_INFORM * Load( int Num );
CLASS_EXPORT  RESURCE_INFORM * LoadAll( int Num );

};

#pragma pack(pop)
#endif
