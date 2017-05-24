#ifndef FILE_SCAD_H
#define FILE_SCAD_H

#pragma pack(push, 1)
include <filework.h>

class FILESCAD: public FILEWORK
{
      BYTE NumFile;
      void *Calc;

public:

void Open(void *S,int,LPCSTR);

int  Check();

void Fixed();

};

#pragma pack(pop)
#endif
