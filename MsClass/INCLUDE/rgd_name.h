#ifndef RIGID_NAME_FLAG_H
#define RIGID_NAME_FLAG_H

#pragma pack(push, 1)
#include <classwin.h>

class RIGID_NAME : MEMORY
{

public:
  	     WORD             Quantity;
        WORD             QuantityAlloc;
        LPSTR          * Name;
        FILEBASE        *File;
	     DWORD           *PosFile;

	     RIGID_NAME() {  Init();  }
       ~RIGID_NAME(void) {  Delete();  }

inline void     Init() {  memset(this,0,sizeof(RIGID_NAME));	}

void       EXPORT   Delete();
LPSTR      EXPORT   Get(int Num);
int        EXPORT   Add(LPSTR);

void       EXPORT Write(FILEBASE &FileWork);
void       EXPORT Read();
int        EXPORT Change( int Num, LPSTR Text );

};

#pragma pack(pop)
#endif
