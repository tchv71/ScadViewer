#ifndef  FILE_MEMORY_FLAG
#define  FILE_MEMORY_FLAG
#pragma pack(push,1)

#include <filebase.h>

class FILE_MEMORY : public FILEBASE
{
	HANDLE    hMapping;  // mapping handle
	LPSTR     Pointer;

void    CLASS_EXPORT Init(void);

public:

	FILE_MEMORY(void)  { Init();  };
       ~FILE_MEMORY(void) { Close(); };

LPSTR  CLASS_EXPORT Open(LPCSTR TextFileName);
void   CLASS_EXPORT Close(void);
void   CLASS_EXPORT Delete(void);

};

#pragma pack(pop)
#endif







