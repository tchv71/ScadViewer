#include "stdafx.h"
#include <ClassWin.h>
#include "BaseClass.hpp"
#include "ObjectList.hpp"
#include "ObjectString.hpp"

int   EXPORT  OBJECT_STRING::Add( LPSTR Sent, int LenSent, BYTE &Control )
{

      char Word[1024], Text[128];
      BYTE kn;
      int n;
      DWORD PosSent = 0;

      Control = 0;
      Separate(Sent,LenSent,PosSent,":",Word);
      Separate(Sent,LenSent,PosSent,":",Text);

      if ( Text[0] == ':' ) {
         n = CharLong(Word,kn);
         if ( kn || n < 1 ) {  Control = 1;  return 0;  }
         }
      else n = Quantity + 1;

      if ( n > Quantity ) AddObject(n-Quantity);
      SetText(n,Word);

      return n;

}

