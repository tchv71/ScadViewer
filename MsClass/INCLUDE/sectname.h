#ifndef SECTIONNAME_FLAG_H
#define SECTIONNAME_FLAG_H
#pragma pack(push, 1)

#include <classwin.h>

struct DATA_IN {
        WORD    Length;
        LPSTR   Name;
        void  * Data;  };

class SECTION_NAME : MEMORY
{

public:
  	     WORD             Quantity;
          WORD             QuantityAlloc;
          DATA_IN        * Data;

	     FILEBASE        *File;
	     DWORD           *PosFile;

	SECTION_NAME() {  Init();  }
  ~SECTION_NAME(void) {  Delete();  }

inline void     Init() {  memset(this,0,sizeof(SECTION_NAME));	}

EXPORT void      Delete();
EXPORT DATA_IN * Get(int Num);
EXPORT int       Add(LPSTR);
EXPORT int		 Add(DATA_IN &);

EXPORT void      Write(FILEBASE &FileWork);
EXPORT void      Read();
EXPORT int       Change( int Num, LPSTR Text );

};

#pragma pack(pop)
#endif

