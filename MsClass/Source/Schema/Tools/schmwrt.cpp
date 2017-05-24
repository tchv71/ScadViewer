#include <stdafx.h>
#include "schema.h"
#include "fund.h"
#include "ForumForce.hpp"

EXPORT void SCHEMA::Write()
{
	  if ( GetModify() == 0 ) return;
	  Write((BYTE)0);
	  FilePrj.Open(FileNameWork,"+rws");
}

EXPORT void SCHEMA::Compress(BYTE Type)
{
	  DeleteLookBody();
          Modify = 1;
	  Write(Type);
	  FilePrj.Open(FileNameWork,"+rws");
}

EXPORT void SCHEMA::Write(BYTE YesCompress)
{
	char FileNameWrite[MAXPATH];
	FILEBASE FileWork;
	LPSTR pS;
	HPSTR pQ;
	BYTE *pB;
	WORD i, j, k, n, QnttEl, QnttNd;
        WORD *NumElem=NULL, *NumNode=NULL;
	FORMAT *pF;
	QnttEl = 0;QnttNd = 0;
    if ( FileNameWork[0] == 0 ) {
           pS = ConstructionFileName("$02");
           if ( strstr(pS,WorkCatalog) )
              pS = ConstructionFileName("$03");
           strcpy(FileNameWork,pS);   }

	pS = ConstructionFileName("tmp");
	strncpy(FileNameWrite,pS,MAXPATH);

	if ( YesCompress && UniteSchem.Quantity == 0 ) {

	   NumElem = (WORD*)Memory(QuantityElem+1,sizeof(WORD));
	   NumNode = (WORD*)Memory(QuantityNode+1,sizeof(WORD));

	   for ( i=0,QnttEl=0; i<QuantityElem; i++ ) {
	      pF = (FORMAT*)&pFormat[i];
	      if ( BitRead((BYTE*)&pF->Flags,7) || pF->TypeElem == 200 ) {
		      MemoryFree(pF->pNode);
		      continue;  }
      if ( YesCompress == 1 )
	      for ( j=0; j<pF->QuantityNode; j++ ) NumNode[pF->pNode[j]] = 1;
	      if ( i > QnttEl ) memcpy(&pFormat[QnttEl],pF,sizeof(FORMAT));
	      NumElem[i+1] = ++QnttEl;  }
	   for ( i=QnttEl; i<QuantityElem; i++ )
	      memset(&pFormat[i],0,sizeof(FORMAT));

	   for ( i=0,QnttNd=0; i<QuantityNode; i++ ) {
	      if ( BitRead((BYTE*)&Coord[i].Flag,7) ) continue;
         if ( NumNode[i+1] || YesCompress == 2 ) {
	         if ( i > QnttNd ) memcpy(&Coord[QnttNd],&Coord[i],sizeof(CK));
	         NumNode[i+1] = ++QnttNd;  }
         }
	   for ( i=QnttNd; i<QuantityNode; i++ )
	      memset(&Coord[i],0,sizeof(CK));

	   for ( i=0; i<QnttEl; i++ ) {
	      pF = (FORMAT*)&pFormat[i];
	      for ( j=0; j<pF->QuantityNode; j++ ) if ( pF->pNode[j] )
		      pF->pNode[j] = NumNode[pF->pNode[j]];
	      }

	   if ( QuantityElem == QnttEl && QuantityNode == QnttNd ) {
	      MemoryFree(NumElem);    MemoryFree(NumNode);
	      NumElem = NumNode = NULL;
	      YesCompress = 0; }

     _Load.Compress(0,0,NULL,QuantityNode,QnttNd,NumNode,_LoadList.Quantity);
     _Load.Modify = 1;

     if ( QuantityElem != QnttEl || QuantityNode != QnttNd ) Modify = 1;
	   n = QuantityElem;  QuantityElem = QnttEl;  QnttEl = n;
	   n = QuantityNode;  QuantityNode = QnttNd;  QnttNd = n;
	   }

       WriteHead(FileNameWrite,FileWork);
	    if ( UniteSchem.Quantity  ) goto _10;
	
       _Joint.Write(FileWork,QnttEl,QuantityElem,NumElem);
       _Bound.Write(FileWork,QnttNd,QuantityNode,NumNode,1);

       _Rigid.Compress(QnttEl,QuantityElem,NumElem);
       _Rigid.Compress(_SectionName);
       _Rigid.Compress(_RigidName);
       _SectionName.Write(FileWork);
       _RigidName.Write(FileWork);
       _Rigid.Write(FileWork,QnttEl,0,NULL);

       _Insert.Write(FileWork,QnttEl,QuantityElem,NumElem);
       _Corner.Write(FileWork,QnttEl,QuantityElem,NumElem);
       _CornerNapr.Write(FileWork,QnttEl,QuantityElem,NumElem);
       _Contur.Write(FileWork,QnttNd,QuantityNode,NumNode);;
       _Blocks.Write(FileWork,QnttEl,QuantityElem,NumElem);
		_ConstructionPos.Write(FileWork,QnttEl,QuantityElem,NumElem);

_10:   _Steel.Write(FileWork,QnttEl,QuantityElem,NumElem);;
       _SteelUni.Write(FileWork,QnttEl,QuantityElem,NumElem);;

        if ( _SteelRigid.GetQuantityRigid() )
          _SteelRigid.Write(FileWork,QnttEl,QuantityElem,NumElem);
        else SpaceSet(&Document[30],sizeof(DOCUMENT));

	for ( i=0; i<10; i++ ) {
      if ( UniteSchem.Quantity && ( i == 0 || i == 4 || i > 7 ) ) continue;
	   if ( i == 4 || i == 7 || i == 8 )
	      _List[i].Write(FileWork,QnttNd,QuantityNode,NumNode);
	   else
	      _List[i].Write(FileWork,QnttEl,QuantityElem,NumElem);
	   }

	if ( UniteSchem.Quantity  == 0 ) {

	   if ( _Load.YesForce() && _Load.GetModify() ) {
	      WriteLoad(FileWork,_Load,Document[26]);
	      FileWork.Write(&NumLoadBuf,sizeof(WORD));
	      Document[26].Length += sizeof(WORD);
	      }
      else memset(&Document[26],0,sizeof(DOCUMENT));

	   WriteLoad(FileWork,_LoadList,6,QnttEl,NumElem,QnttNd,NumNode);
	   WriteLoad(FileWork,_LoadGroup,7,QnttEl,NumElem,QnttNd,NumNode);

      }

   if ( Document[39].Length ) {
      FUND Fund;
      Fund.Init(FilePrj,Document[39]);
      Fund.Write(FileWork,QnttEl,NumElem,QuantityNode,QnttNd,NumNode);
      Fund.Delete();  }

   if(Document[56].PosFile)
   {
	   FORUM_FORCE fF;
	   int *iNumElem;
	   fF.Init();
	   fF.Read(FilePrj,Document[56]);
       if ( NumElem ) {
		   iNumElem = (int *)Memory(QnttEl+1+QuantityElem,sizeof(int));
       	   for(i = 0; i <= QnttEl; i++) iNumElem[i] = NumElem[i];
		   fF.Compress(QnttEl,iNumElem);  
		   MemoryFree(iNumElem);
	   }
	   fF.Write(FileWork,Document[56]);
	   fF.Destroy();
   }
   
    if ( NumElem ) MemoryFree(NumElem);
	if ( NumNode ) MemoryFree(NumNode);

	if ( Data )
	   WriteDocument(FileWork,Data,*(WORD*)Data+sizeof(WORD),40);

	static BYTE NumDocWrite[] = { 8, 15, 16, 21, 22, 34, 35, 36, 37, 38, 0 };
	for ( k=0; ;k++ ) {
      i = NumDocWrite[k];
      if ( i == 0 ) break;
      if ( Document[i].Length == 0 ) continue;
	   pQ = (HPSTR)ReadDocument(i);
	   WriteDocument(FileWork,pQ,Document[i].Length,i);
	   MemoryFree(pQ);  }

   if ( UniteSchem.Quantity ) {
      FileWork.Put(&UniteSchem.Quantity,sizeof(WORD),&Document[14].PosFile);
      for ( i=0; i<UniteSchem.Quantity; i++ ) {
	      char drive[MAXDRIVE];
	      char dir[MAXDIR];
	      char file[MAXFILE];
	      char ext[MAXEXT];
	      fnsplit(((SCHEMA*)UniteSchem.Inf[i].Schem)->GetFileName(),drive,dir,file,ext);
         FileWork.StringWrite(file);
         FileWork.Write(&UniteSchem.Inf[i].Mark,sizeof(FILE));
         }
      Document[14].Length = FileWork.GetLength() - Document[14].PosFile;
      goto _20;  }

	n = QuantityNode / 8 + 1;
	pB = (BYTE*)Memory(n);
	for ( i=0,k=0; i<QuantityNode; i++ )
	   if ( BitRead((BYTE*)&Coord[i].Flag,7) ) {  BitOn(pB,i);  k = 1;  }
	if ( k ) WriteDocument(FileWork,pB,n,23);
	else memset(&Document[23],0,sizeof(DOCUMENT));
	MemoryFree(pB);

	n = QuantityElem / 8 + 1;
	pB = (BYTE*)Memory(n);
	for ( i=0,k=0; i<QuantityElem; i++ )
	   if ( BitRead((BYTE*)&pFormat[i].Flags,7) ) {  BitOn(pB,i);  k = 1;  }
	if ( k ) WriteDocument(FileWork,pB,n,24);
	else memset(&Document[24],0,sizeof(DOCUMENT));
	MemoryFree(pB);

_20:	WriteEnd(FileWork);

	FilePrj.Close();
	FileWork.Close();
	if ( access(FileNameWork,0) == 0 ) remove(FileNameWork);
	rename(FileNameWrite,FileNameWork);
}

void SCHEMA::WriteHead(LPCSTR FileNameWrite, FILEBASE &FileWork)
{
		WORD  i, j;
		DWORD Len, la, lb;

		FileWork.Open(FileNameWrite,"rws");

		FileWork.Write("*SCHEMA*",8,0);
		FileWork.Write(&Len,sizeof(DWORD)) ;

		i = (LPSTR)&Document - (LPSTR)&TypeSchema;
		FileWork.Write(&i,sizeof(WORD));
		FileWork.Write(&TypeSchema,i);

		FileWork.StringWrite(Name);
		FileWork.StringWrite(Company);
		FileWork.StringWrite(Customer);
		FileWork.StringWrite(Object);
		FileWork.StringWrite("");  // устарело PROFILE b LOCALBASE
		FileWork.StringWrite("");
		FileWork.Write(Units,sizeof(Units));

      GetModify();

		for ( i=0; i<MAX_TREE; i++ ) if ( memcmp(&Tree[i].TimeModify,&TimeNull,sizeof(FILETIME)) ) {
			j = i + 1;
			FileWork.Write(&j,sizeof(WORD));
			FileWork.Write(&Tree[i],sizeof(TREE));
			}
		FileWork.Write(&(i=0),sizeof(WORD));

      if ( UniteSchem.Quantity ) return;

		la = FileWork.GetLength();
		for ( i=0; i<QuantityElem; i++ ) {
			FileWork.Write(&pFormat[i],2*sizeof(WORD));
			FileWork.Write(pFormat[i].pNode,(DWORD)sizeof(WORD)*pFormat[i].QuantityNode);
			}
		SetDocFile(1,la,FileWork.GetLength()-la);

		la = FileWork.GetLength();
		lb = 3l * sizeof(double);
		for ( i=0; i<QuantityNode; i++ ) FileWork.Write(&Coord[i],lb);
		SetDocFile(4,la,lb*QuantityNode);

}

void SCHEMA::WriteEnd(FILEBASE &FileWork)
{
		WORD i;
		DWORD la;

        Param.Version = 10;
		WriteDocument(FileWork,&Param,sizeof(SCHEMA_PARAM),25);

		FileWork.Write(&TypeSchema,(LPSTR)&Document - (LPSTR)&TypeSchema,8+sizeof(DWORD)+sizeof(WORD));

		la = FileWork.GetLength();
		FileWork.Write(&la,sizeof(DWORD),8);
		for ( i=1; i<MAX_DOCUMENT; i++ ) if ( Document[i].Length ) {
		   FileWork.Write(&i,sizeof(WORD));
		   FileWork.Write(&Document[i],sizeof(DOCUMENT));  }
		FileWork.Write(&(i=0),sizeof(WORD));

}

EXPORT void SCHEMA::Write(LPCSTR FlName)
{
    char Name[MAXPATH];

    strncpy(Name,FlName,MAXPATH);
    if ( GetModify() == 0 && strcmpup(FlName,FileName) == 0 ) return;

    strncpy(FileName,Name,MAXPATH);

    FillTreeFull(1);

    Write((BYTE)0);

		if ( strcmp(Name,FileNameWork) ) {
		   if ( access(Name,0) == 0 ) remove(Name);
	      if ( !CopyFile(FileNameWork,Name,FALSE) )
            CrashMessage(120,FileNameWork);
		   remove(FileNameWork);  }
		Read(Name);
}