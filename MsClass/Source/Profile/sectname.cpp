#include <stdafx.h>
#include <sectname.h>

EXPORT int SECTION_NAME::Add( LPSTR Text ) 
{

     int i, Len;
     FILEBASE Work;
     void * Buf;

     if ( this == NULL ) return 0;
      Read();

     if ( access(Text,0) ) return 0;
     Work.Open(Text,"r");
     Len = Work.GetLength();
     Buf = Memory(Len+1);
     Work.Read(Buf,Len,0);
     Work.Close();

     for ( i=0; i<Quantity; i++ ) {
        if ( Data[i].Length != Len ) continue;
        if ( strcmpup(Data[i].Name,Text) ) continue;
        if ( SpaceCompare(Data[i].Data,Buf,Len ) == 0 ) {
           MemoryFree(Buf);  return i + 1;   }
        }

      if ( Quantity == QuantityAlloc ) {
         QuantityAlloc += 20;
        DATA_IN *pWork = (DATA_IN*)Memory(QuantityAlloc,sizeof(DATA_IN));
        if ( Data ) {
            SpaceCopy(pWork,Data,(DWORD)Quantity*sizeof(DATA_IN));
            MemoryFree(Data);  }
         Data = pWork;   }

     Data[Quantity].Length = Len;
     Data[Quantity].Data   = Buf;
     Data[Quantity].Name   = (LPSTR)Memory(strlen(Text)+1);
     strcpy(Data[Quantity].Name,Text);
     return ++Quantity;

}

EXPORT int  SECTION_NAME::Add( DATA_IN &DI )
{
     int i;
     LPSTR pS;

     if ( this == NULL ) return 0;
      Read();

     for ( i=0; i<Quantity; i++ ) {
        if ( Data[i].Length != DI.Length ) continue;
        if ( SpaceCompare(Data[i].Data,DI.Data,DI.Length ) == 0 )  return i + 1;
        }

      if ( Quantity == QuantityAlloc ) {
         QuantityAlloc += 20;
        DATA_IN *pWork = (DATA_IN*)Memory(QuantityAlloc,sizeof(DATA_IN));
        if ( Data ) {
            SpaceCopy(pWork,Data,(DWORD)Quantity*sizeof(DATA_IN));
            MemoryFree(Data);  }
         Data = pWork;   }

     pS = (LPSTR)Memory(DI.Length);
     SpaceCopy(pS,DI.Data,DI.Length);
     Data[Quantity].Length = DI.Length;
     Data[Quantity].Data   = pS;
     Data[Quantity].Name   = (LPSTR)Memory(strlen(DI.Name)+1);
     strcpy(Data[Quantity].Name,DI.Name);
     return ++Quantity;

}


EXPORT int SECTION_NAME::Change( int Num, LPSTR Text )
{
     FILEBASE Work;
     void * Buf;
     DATA_IN *pDI;
     int Len;

     if ( this == NULL ) return 0;
      Read();

     if ( access(Text,0) ) return 0;
     Work.Open(Text,"r");
     Len = Work.GetLength();
     Buf = Memory(Len+1);
     Work.Read(Buf,Len,0);
     Work.Close();

     if ( Num && Num <= Quantity ) {
        pDI = &Data[Num-1];
        if ( pDI->Data ) MemoryFree(pDI->Data);
        if ( pDI->Name ) MemoryFree(pDI->Name);
        pDI->Length = Len;
        pDI->Data   = Buf;
        pDI->Name   = (LPSTR)Memory(strlen(Text)+1);
        strcpy(pDI->Name,Text);
        return Num;   }

     return Add(Text);

}

EXPORT DATA_IN *  SECTION_NAME::Get(int Num)
{
     if ( this == NULL ) return NULL;
     Read();
     if ( Num == 0 || Num > Quantity ) return NULL;
     return &Data[Num-1];
}


void EXPORT SECTION_NAME::Delete() {

     int i;
      FILEBASE *Fl;
      DWORD    *Pos;

     if ( this == NULL ) return;

     if ( Data ) {
        for( i=0; i<Quantity; i++ ) {
           if ( Data[i].Data ) MemoryFree(Data[i].Data);
           if ( Data[i].Name ) MemoryFree(Data[i].Name);
           }
        MemoryFree(Data);   }

      Pos = PosFile;  Fl = File;
      Init();
      PosFile = Pos;  File = Fl;
}

void EXPORT SECTION_NAME::Read()
{
	WORD n, i, l;
	BYTE m;
	char Buf[512];
	
	if ( this == NULL ) return;
	if ( PosFile == NULL ) return;
	if ( *PosFile == 0 || Data ) return;
	File->SeekRead(*PosFile);
	
	File->Read(&n,sizeof(WORD));
	
	QuantityAlloc = Quantity = n;
	Data = (DATA_IN*)Memory(sizeof(DATA_IN),n+1);
	
	for ( i=0; i<n; i++ ) {
        File->Read(&l,sizeof(WORD));
        Data[i].Length = l;
        Data[i].Data = Memory(l+1);
        File->Read(Data[i].Data,l);
        File->StringRead(Buf,m);
        Data[i].Name = (LPSTR)Memory(m+1);
        strcpy(Data[i].Name,Buf);
	}
	
}

void EXPORT SECTION_NAME::Write(FILEBASE &FileBase )
{
	if ( this == NULL ) return;
	Read();
	if ( Quantity < 1 ) {
        memset(PosFile,0,2*sizeof(DWORD));
		return;  }
	
	PosFile[0] = FileBase.GetLength();
	FileBase.Write(&Quantity,sizeof(WORD));
	for ( int i=0; i<Quantity; i++ )  {
		FileBase.Write(&Data[i].Length,sizeof(WORD));
        FileBase.Write(Data[i].Data,Data[i].Length);
        FileBase.StringWrite(Data[i].Name);
	}
	PosFile[1] = FileBase.GetLength() - PosFile[0];
	Delete();
}

