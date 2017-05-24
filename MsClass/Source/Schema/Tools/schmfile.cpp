#include <stdafx.h>
#include "schema.h"

void  SCHEMA::SetDocFile(WORD NumDoc, DWORD PosFile, DWORD DocLength)
{
     if ( NumDoc < MAX_DOCUMENT ) {
	     Document[NumDoc].PosFile = PosFile;
	     Document[NumDoc].Length  = DocLength;  }
}

EXPORT void  SCHEMA::CopyWorkFile()
{
		LPSTR pName;
		Write((BYTE)0);
		pName = ConstructionFileName("$$A");
		if ( !CopyFile(FileNameWork,pName,FALSE) )
         CrashMessage(120,FileNameWork);
		FilePrj.Open(FileNameWork,"+rws");
}

EXPORT void SCHEMA::ReturnWorkFile()
{
		char  FlNm[MAXPATH], ReturnFlNm[MAXPATH];

		strcpy(FlNm,FileName);
		strcpy(ReturnFlNm,ConstructionFileName("$$A"));
		Read(ReturnFlNm,0);
		remove(ReturnFlNm);
		strcpy(FileName,FlNm);
}

EXPORT void SCHEMA::WriteDocument(FILEBASE &Work, void FAR *Buffer,DWORD LengthBuffer,WORD NumDoc)
{
     DOCUMENT *StrDoc = &Document[NumDoc];

     StrDoc->PosFile = Work.GetLength();
     StrDoc->Length = LengthBuffer;
     Work.Write(Buffer,LengthBuffer);
}

EXPORT HPSTR SCHEMA::ReadDocument(WORD NumDoc)
{
     DOCUMENT *StrDoc = &Document[NumDoc];
     HPSTR Buffer = (HPSTR)Memory(StrDoc->Length+1);
     FilePrj.Read(Buffer,StrDoc->Length,StrDoc->PosFile);
     return Buffer;
}

LPSTR  SCHEMA::ConstructionFileName(LPCSTR File, LPCSTR Ext, BYTE Type )
{
	_declspec(thread) static char Name[MAXPATH];
	char drive[MAXDRIVE];
	char dir[MAXDIR];
	char file[MAXFILE];
	char ext[MAXEXT];

	fnsplit(FileName,drive,dir,file,ext);
	if ( Type ) {
	   strncpy(Name,WorkCatalog,MAXPATH);
	   strncat(Name,file,MAXPATH);
	   strncat(Name,ext,MAXPATH);
	   fnsplit(Name,drive,dir,file,ext);
	   }
	if ( File == NULL ) fnmerge(Name,drive,dir,file,Ext);
	else {
      if ( Ext ) fnmerge(Name,drive,dir,File,Ext);
      else fnmerge(Name,drive,dir,File,ext);
      }

	return Name;
}

EXPORT LPSTR   SCHEMA::ConstructionFileName(LPCSTR Ext)
{
       return ConstructionFileName(NULL,Ext,1);
}

EXPORT LPSTR   SCHEMA::ConstructionDataName(LPCSTR Ext)
{
       return ConstructionFileName(NULL,Ext,0);
}

EXPORT LPSTR  SCHEMA::ConstructionDataName(LPCSTR File, LPCSTR Ext)
{
       return ConstructionFileName(File,Ext,0);
}

EXPORT void  SCHEMA::DeleteFile( LPCSTR Name[] )
{
      LPSTR pS;
      for ( int i=0; Name[i][0]; i++ ) {
        pS = ConstructionFileName(Name[i]);
        if ( access(pS,0) == 0 )remove(pS);
        }
}