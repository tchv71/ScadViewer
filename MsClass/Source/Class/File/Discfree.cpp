#include <stdafx.h>
#include <classwin.h>
#include <stdio.h>

typedef BOOL (WINAPI *MyFunc)(LPCSTR RootName, PULARGE_INTEGER pulA, PULARGE_INTEGER pulB, PULARGE_INTEGER pulFreeBytes);

EXPORT long GetFreeDiskSpaceInKB(LPCSTR FileName)
{
      DWORD dwFreeClusters, dwBytesPerSector, dwSectorsPerCluster, dwClusters;
	  ULARGE_INTEGER ulA, ulB, ulFreeBytes;
      char Drive[MAXPATH];
      LPSTR  pS;
      LPSTR  pQ;
      LONGLONG l = -1;
      int n = 0;

      strcpy(Drive,FileName);
_10:  pS = strchr(Drive,':' );
      if ( pS ) pS[1] = 0;
      else if ( !strstr(Drive,"\\\\") ) {
         if ( n ) return -1;
         strcpy(Drive,GetPath(FileName));
         n = 1;   goto _10;  }
      else {
         pS = strchr(Drive,'\\');
         while ( 1 ) {
            pQ = strchr(pS+1,'\\');
            if ( pQ ) pS = pQ;
            else break;   }
         pS[1] = 0;  }

      HINSTANCE h = LoadLibraryA("kernel32.dll");

      if ( h ) {
		   MyFunc pfnGetDiskFreeSpaceEx = (MyFunc)GetProcAddress(h,"GetDiskFreeSpaceExA");
		   if ( pfnGetDiskFreeSpaceEx ) {
 			   if (!pfnGetDiskFreeSpaceEx(Drive, &ulA, &ulB, &ulFreeBytes)) goto _20;
 			   if (!pfnGetDiskFreeSpaceEx(Drive, &ulA, &ulB, &ulFreeBytes)) goto _20;
      	   l = ulFreeBytes.u.LowPart + ulFreeBytes.u.HighPart * (LONGLONG)0x100000000;
      	   l = l / 1024;
            goto _20;  }
         }

	   if ( GetDiskFreeSpace(Drive, &dwSectorsPerCluster, &dwBytesPerSector,
									&dwFreeClusters, &dwClusters))
      l = ( dwSectorsPerCluster * (LONGLONG)dwBytesPerSector * dwFreeClusters ) / 1024;

_20:  if ( h ) FreeLibrary(h);
      return l;

}