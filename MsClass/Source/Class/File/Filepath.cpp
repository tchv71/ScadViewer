#include <stdafx.h>
#include <defclass.h>


/*------------------------------------------------------------------------*/
/* Function return full path to the file using the path of the EXE file   */
/*------------------------------------------------------------------------*/
EXPORT void  CrashMessage( int NumError ... );

EXPORT char * searchpath( LPCSTR Name )
{
	static char FilePath[MAX_PATH];
	LPTSTR Component;
	if ( SearchPath(NULL, Name,	NULL, MAX_PATH, FilePath, &Component) == 0 )
	   return NULL;
	return &FilePath[0];
}

EXPORT void FilePath(LPCSTR Name,LPSTR Path)
{
	  LPSTR sear = searchpath(Name);
	  if ( sear == NULL ) CrashMessage(116,Name);
	  else strncpy(Path,sear,MAXPATH);
}


EXPORT void  FilePath(HINSTANCE hInst,LPCSTR Name,LPSTR Path)
{
	char   drive1[MAXDRIVE],dir1[MAXDIR],name1[MAXFILE],ext1[MAXEXT];
	char   name2[MAXFILE],ext2[MAXEXT];
	static char PathIn[MAXPATH] = { 0 };

	if ( PathIn[0] == 0 ) GetModuleFileName(hInst,PathIn,MAXPATH);
	fnsplit(Name,drive1,dir1,name2,ext2);
	fnsplit(PathIn,drive1,dir1,name1,ext1);
	fnmerge(Path,drive1,dir1,name2,ext2);
}

EXPORT LPCSTR  GetPath(HINSTANCE hInst,LPCSTR Name)
{
	static char Path[MAXPATH];
	FilePath(hInst,Name,Path);
	return Path;
}

EXPORT LPCSTR  GetPath(LPCSTR Name)
{
     return GetPath(NULL,Name);
}