#ifndef  FILE_MEMORY_FLAG
#define  FILE_MEMORY_FLAG
#pragma pack(push, 1)
#include <filebase.h>

class FILE_MEMORY : public FILEBASE
{
	HANDLE hMapping;  // mapping handle
	LPSTR  Pointer;

EXPORT void Init(void);

public:

EXPORT 	FILE_MEMORY(void)  { Init();  };
EXPORT ~FILE_MEMORY(void) { Close(); };

EXPORT LPSTR   Open(LPCSTR TextFileName);
EXPORT void    Close(void);
EXPORT void    PASCAL Delete(void);

};

#pragma pack(pop)
#endif