#include <stdafx.h>
#include "schema.h"
#include "fund.h"

EXPORT int SCHEMA::Read()
{
	   char s[MAXPATH];
	   if ( FileNameWork[0] == 0 ) return 1;
	   strcpy(s,FileNameWork);
      return  Read(s);
}

EXPORT int SCHEMA::Read(LPCSTR FlName, BYTE Type )
{
	   WORD  i, n, QnttBeg, k;
	   char s[513], *pS;
	   DWORD PosDoc;
	   BYTE *pB;
	   char Name[MAXPATH];
	   char drive[MAXDRIVE];
	   char dir[MAXDIR];
	   char file[MAXFILE];
	   char ext[MAXEXT];
	   static UNITS ud[] = {
		   "M", 1,
			   "CM", 100,
			   "T" , 1,
			   "øC",  1 };
		   FILETIME FT;
		   
		   if ( FlName == NULL ) return 1;
		   if ( access(FlName,0) ) return 1;
		   
		   Init(hWND, hINST, NULL);
		   strcpy(FileName,FlName);
		   pS = strstr(FileName,WorkCatalog);
		   
		   fnsplit(FileName,drive,dir,file,ext);
		   if ( strcmpup(ext,".vpr") == 0 && Type == 0 ) Type = 1;
		   
		   if ( Type < 10 ) {
			   for ( i=0; i<100; i++ ) {
				   if ( Type == 0 ) sprintf(s,"$%02hd",i);
				   else if ( Type < 5 ) sprintf(s,"@%02hd",i);
				   else sprintf(s,"#%02hd",i);
				   pB = (BYTE *)ConstructionFileName(s);
				   if ( strcmp(FlName,(char *)pB) == 0 ) continue;
				   remove((char *)pB);
				   if ( access((char *)pB,0) ) break;  }
		   }
		   else pB = (BYTE *)FileName;
		   strcpy(FileNameWork,(char *)pB);
		   if ( Type == 10 ) FilePrj.Open(FileNameWork,"rs");
		   else {
			   if ( !CopyFile(FlName,FileNameWork,FALSE) ) CrashMessage(120,FlName);
			   PosDoc = GetFileAttributes(FileNameWork);
			   if ( PosDoc & FILE_ATTRIBUTE_READONLY ) {
				   SetFileAttributes(FileNameWork,FILE_ATTRIBUTE_ARCHIVE);
				   CrashMessage(-151);   }
			   FilePrj.Open(FileNameWork,"+rws");    }
		   
		   if ( FilePrj.GetLength() == 0 ) return 1;
		   FilePrj.Read(s,8,0);
		   if ( strncmp(s,"*SCHEMA*",8) != 0 ) {
			   Printf("The File is't not SCAD",FlName);
			   return 1;   }
		   
		   FilePrj.Read(&PosDoc,sizeof(DWORD));
		   FilePrj.Read(&QnttBeg,sizeof(WORD));
		   
		   FilePrj.Read(&TypeSchema,QnttBeg);
		   QuantityAllocElem = QuantityAllocNode = 0;
		   
		   FilePrj.SeekRead(PosDoc);
		   while ( 1 ) {
			   FilePrj.Read(&i,sizeof(WORD));
			   if ( i == 0 ) break;
			   FilePrj.Read(&Document[i],sizeof(DOCUMENT));  }
		   
		   if ( Document[14].PosFile ) if ( ReadSchemaUnite(Type) ) return 1;
		   
		   if ( Document[25].PosFile ) {
			   FilePrj.SeekRead(Document[25].PosFile);
			   FilePrj.Read(&Param,Document[25].Length);
		   }
		   else {
			   Param.Version = 0;
		   }
		   if ( Param.Version < 2 ) Param.TypeOptimization = 0xFF;
		   if ( Param.Version < 7 ) memset(&Document[17],0,sizeof(DOCUMENT));
		   
		   FilePrj.SeekRead(8+sizeof(DWORD)+sizeof(WORD)+QnttBeg);
		   
		   FilePrj.StringRead(Name);
		   FilePrj.StringRead(Company);
		   FilePrj.StringRead(Customer);
		   FilePrj.StringRead(Object);
		   
		   FilePrj.StringRead(s);
		   FilePrj.StringRead(s);
		   
		   FilePrj.Read(Units,sizeof(Units));
           if ( Units[0].coef == 0 || Units[1].coef == 0 || Units[2].coef == 0 )
			   memcpy(Units,ud,sizeof(ud));
		   _Profile->SetUnit(Units[0],Units[1],Units[2]);
		   
		   SetTreeTime(171);
		   memcpy(&FT,&Tree[171].TimeModify,sizeof(FILETIME));
		   
		   for ( i=0; ; i++ ) {
			   FilePrj.Read(&n,sizeof(WORD));
			   if ( n == 0 ) break;
			   FilePrj.Read(&Tree[--n],sizeof(TREE));
			   if ( Param.Version < 5 ) SetTreeTime(n);
		   }
		   
		   for ( i=0; i<MAX_TREE; i++ ) {
			   if ( memcmp(&TimeNull,&Tree[i].TimeModify,sizeof(FILETIME)) == 0 )
				   continue;
			   if ( FileTimeCompare(&FT,&Tree[i].TimeModify) < 0  )
				   SetTreeTime(i);
		   }
		   
		   if ( Document[14].PosFile ) goto _20;
		   
		   FilePrj.SeekRead(Document[1].PosFile);
		   if ( QuantityElem ) {
			   QuantityAllocElem = QuantityElem;
			   pFormat = (FORMAT *)Memory(QuantityElem,sizeof(FORMAT));
			   for ( i=0; i<QuantityElem; i++ ) {
				   FilePrj.Read(&pFormat[i],2*sizeof(WORD));
				   pFormat[i].pNode = NULL;
				   k = pFormat[i].QuantityNode;
				   if ( k ) AllocElemNode(i+1,k);
				   FilePrj.Read(pFormat[i].pNode,
					   (DWORD)sizeof(WORD)*pFormat[i].QuantityNode);
		   }  }
		   
		   FilePrj.SeekRead(Document[4].PosFile);
		   Coord = (CK *)Memory(QuantityNode+1,sizeof(CK));
		   QuantityAllocNode = QuantityNode+1;
		   for ( i=0; i<QuantityNode; i++ )
			   FilePrj.Read(&Coord[i],3*sizeof(double));
		   
		   if ( Type < 10 ) {
			   
			   _Joint.Read();    JointInFormat();          _Joint.Delete();
			   _Bound.Read();
			   
			   RigidInFormat();	            _Rigid.Delete();
			   InsertInFormat(_Insert);      _Insert.Delete();
			   InsertInFormat(_Corner);      _Corner.Delete();
			   InsertInFormat(_CornerNapr);  _CornerNapr.Delete();
			   
			   ReadLoadInf(_LoadList);
			   ReadLoadInf(_LoadGroup);
			   
			   if ( Document[40].Length ) Data = ReadDocument(40);
			   
		   }
		   
		   if ( Document[23].Length ) {
			   pB = (BYTE*)ReadDocument(23);
			   for ( i=0; i<QuantityNode; i++ )
				   if ( BitRead(pB,i) ) BitOn((BYTE*)&Coord[i].Flag,7);
				   MemoryFree(pB);  }
		   
		   if ( Document[24].Length ) {
			   pB = (BYTE*)ReadDocument(24);
			   for ( i=0; i<QuantityElem; i++ )
				   if ( BitRead(pB,i) ) BitOn((BYTE*)&pFormat[i].Flags,7);
				   MemoryFree(pB);  }
		   
           _Load.Delete();
		   if ( Document[26].Length ) {
			   ReadLoad(_Load,Document[26].PosFile);
			   FilePrj.Read(&NumLoadBuf,sizeof(WORD));
		   }
		   
		   _Steel.Version = Param.Version;
		   if ( Param.Version < 7 && Type == 0 ) {
			   Modify = 1;
			   Write(FlName);   }
		   
_20:  Modify = 0;
	  
      return 0;
}

EXPORT int SCHEMA::ReadCopy(LPCSTR FlName)
{
		return Read(FlName,1);
}

int  SCHEMA::ReadSchemaUnite(int Type)
{
          int i, n, k;
          char s[256], *pS;
          SCHEMA *pSCHM;
          LOAD_INF *LI, *pLI;

          FilePrj.Read(&UniteSchem.Quantity,sizeof(WORD),Document[14].PosFile);
          UniteSchem.QuantityAlloc = UniteSchem.Quantity + 1;
          UniteSchem.Inf = (UNITE_SCHEMA_INF*)Memory(sizeof(UNITE_SCHEMA_INF),UniteSchem.Quantity+1);

          for ( i=0; i<UniteSchem.Quantity; i++ ) {
             FilePrj.StringRead(s);
             FilePrj.Read(&UniteSchem.Inf[i].Mark,sizeof(FILE));
             UniteSchem.Inf[i].Schem = Memory(sizeof(SCHEMA)+1);
             UniteSchem.Inf[i].NumLoadBegin = _LoadList.Quantity + 1;
             pSCHM = (SCHEMA*)(UniteSchem.Inf[i].Schem);
             pS = ConstructionFileName(s,"spr",0);
             strcpy(s,pS);
             if ( access(s,0) ) {
                Printf("Cannot open scheme:/n%s",s);
                Delete();  return 1;  }
             pSCHM->Init(hWND,hINST,WorkCatalog);
             pSCHM->Read(s,Type);
             if ( i == 0 ) memcpy(&TypeSystem,&pSCHM->TypeSystem,sizeof(TYPE_SYSTEM));
             if ( pSCHM->QuantityElem > UniteSchem.MaxElem )
                UniteSchem.MaxElem = pSCHM->QuantityElem;
             if ( pSCHM->QuantityNode > UniteSchem.MaxNode )
                UniteSchem.MaxNode = pSCHM->QuantityNode;
             _LoadList.Quantity += pSCHM->_LoadList.Quantity;
             }

          _LoadList.QuantityAlloc = _LoadList.Quantity;
          LI = _LoadList.Inf = (LOAD_INF*)Memory(_LoadList.Quantity+1,sizeof(LOAD_INF));

          for ( i=0,n=0; i<UniteSchem.Quantity; i++ ) {
             pSCHM = (SCHEMA*)(UniteSchem.Inf[i].Schem);
             pSCHM->AddZero(UniteSchem.MaxElem-pSCHM->QuantityElem,
                            UniteSchem.MaxNode-pSCHM->QuantityNode);
             pLI = &pSCHM->_LoadList.Inf[0];
             for ( k=0; k < pSCHM->_LoadList.Quantity; k++, n++ ) {
                LI->Load.Copy(pLI->Load);
                pLI->Load.Delete();
	             LI->TypeDynamic = pLI->TypeDynamic;
	             LI->YesWeight = pLI->YesWeight;
	             LI->NumUnite = i + 1;
	             LI->NumLoadUnite = k + 1;
                strcpy(s,LI->Load.Name);
                LI++;  pLI++;  }
             }

          ReadUnite(1);
          return 0;
}