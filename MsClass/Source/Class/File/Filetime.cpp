#include <stdafx.h>
#include <classwin.h>

EXPORT int  FileTime( HANDLE pH,
           FILETIME *TimeCreate, FILETIME *TimeAccess, FILETIME *TimeLastWrite )
{
      FILETIME CreationTime;	// address of creation time
      FILETIME LastAccessTime;	// address of last access time
      FILETIME LastWriteTime;

      if ( pH == NULL ) return 1;

      if ( TimeAccess ) memset(TimeAccess,0,sizeof(FILETIME));
      if ( TimeCreate ) memset(TimeCreate,0,sizeof(FILETIME));
      if ( TimeLastWrite ) memset(TimeLastWrite,0,sizeof(FILETIME));

      if ( GetFileTime(pH,&CreationTime,&LastAccessTime,&LastWriteTime) == 0 )
         return 1;

      if ( TimeAccess ) {
         FileTimeToLocalFileTime(&LastAccessTime,TimeAccess);
//         memcpy(TimeAccess,&LastAccessTime,sizeof(FILETIME));
         }
      if ( TimeCreate ) {
         FileTimeToLocalFileTime(&CreationTime,TimeCreate);
//         memcpy(TimeCreate,&CreationTime,sizeof(FILETIME));
         }
      if ( TimeLastWrite )
         FileTimeToLocalFileTime(&LastWriteTime,TimeLastWrite);
//      memcpy(TimeLastWrite,&LastWriteTime,sizeof(FILETIME));
      return 0;
}

EXPORT int  FileTime( LPCSTR Name,
           FILETIME *TimeCreate, FILETIME *TimeAccess, FILETIME *TimeLastWrite )
{
      FILEWORK Work;
      int ret;

      if ( access(Name,0) ) return 1;
      Work.Open(Name,"r");

      ret = FileTime(Work.GetHandle(),TimeCreate,TimeAccess,TimeLastWrite ) ;
      Work.Close();
      return ret;
}

EXPORT long  FileTimeCompare( FILETIME *T1, FILETIME *T2 )
{
      SYSTEMTIME ST1, ST2;
      long l;

      FileTimeToSystemTime(T1,&ST1);
      FileTimeToSystemTime(T2,&ST2);

      l =           ST1.wSecond - (int)ST2.wSecond   +
            60  * ( ST1.wMinute - (int)ST2.wMinute   +
            60  * ( ST1.wHour   - (int)ST2.wHour     +
            24  * ( ST1.wDay    - (int)ST2.wDay      +
            31  * ( ST1.wMonth  - (int)ST2.wMonth    +
           372  * ( ST1.wYear   - (int)ST2.wYear ) ) ) ) );
      return l;
}

EXPORT void FileTimePrint( LPCSTR Text, FILETIME *T )
{
      SYSTEMTIME ST;
      FileTimeToSystemTime(T,&ST);
//      dPrintf("\n%s= %d %d %d %d %d %d",Text,(int)ST.wSecond,(int)ST.wMinute,(int)ST.wHour,
//            (int)ST.wDay, (int)ST.wMonth,(int)ST.wYear);
}