#include <stdafx.h>
#include <rgd_name.h>
#include <data_rgd.h>

EXPORT int RIGID_NAME::Add( LPSTR Text ) {

     int i;
     LPSTR *pWork;

     if ( this == NULL ) return 0;
	  Read();

     for ( i=0; i<Quantity; i++ )
        if ( strcmp(Name[i],Text) == 0 )return i+1;

	  if ( Quantity == QuantityAlloc ) {
	     QuantityAlloc += 20;
        pWork = (LPSTR*)Memory(QuantityAlloc,sizeof(LPSTR));
        if ( Name ) {
	        SpaceCopy(pWork,Name,(DWORD)Quantity*sizeof(LPSTR));
	        MemoryFree(Name);  }
	     Name = pWork;   }

     Name[Quantity] = (LPSTR)Memory(strlen(Text)+1);
     strcpy(Name[Quantity],Text);
     return ++Quantity;

}

EXPORT int RIGID_NAME::Change( int Num, LPSTR Text )
{
     LPSTR pS;

     if ( this == NULL ) return 0;
	  Read();

     if ( Num && Num <= Quantity ) {
        pS = Name[Num-1];
        if ( pS ) MemoryFree(pS);
        Name[Num-1] = (LPSTR)Memory(strlen(Text)+1);
        strcpy(Name[Num-1],Text);
        return Num;   }

     return Add(Text);

}

LPSTR  EXPORT  RIGID_NAME::Get(int Num)
{
     if ( this == NULL ) return NULL;
     Read();
     if ( Num == 0 || Num > Quantity ) return NULL;
     return Name[Num-1];
}


void EXPORT RIGID_NAME::Delete() {

     int i;
	  FILEBASE *Fl;
	  DWORD    *Pos;

     if ( this == NULL ) return;

     if ( Name ) {
        for( i=0; i<Quantity; i++ )
           if ( Name[i] ) MemoryFree(Name[i]);
        MemoryFree(Name);   }

	  Pos = PosFile;  Fl = File;
	  Init();
	  PosFile = Pos;  File = Fl;
}

void EXPORT RIGID_NAME::Read()
{
     WORD n, i;
     char Buf[512];

     if ( this == NULL ) return;
	  if ( PosFile == NULL ) return;
	  if ( *PosFile == 0 || Name ) return;
 	  File->SeekRead(*PosFile);

     File->Read(&n,sizeof(WORD));

	  QuantityAlloc = Quantity = n;
     Name = (LPSTR*)Memory(sizeof(LPSTR),n+1);

	  for ( i=0; i<n; i++ ) {
        File->StringRead(Buf);
        Name[i] = (LPSTR)Memory(strlen(Buf)+1);
        strcpy(Name[i],Buf);
        }

}

void EXPORT RIGID_NAME::Write(FILEBASE &FileWork )
{
     if ( this == NULL ) return;
	  Read();
	  if ( Quantity < 1 ) {
        memset(PosFile,0,2*sizeof(DWORD));
	     return;  }

     PosFile[0] = FileWork.GetLength();
     FileWork.Write(&Quantity,sizeof(WORD));
	  for ( int i=0; i<Quantity; i++ )  {
        FileWork.StringWrite(Name[i]);
        }
     PosFile[1] = FileWork.GetLength() - PosFile[0];
     Delete();
}

void EXPORT DATA_RIGID::Compress( RIGID_NAME &RigidName )
{
     int *Num, i, j, n, k;
     RIGID_LIST *pRL;

     if ( this == NULL ) return;
     RigidName.Read();
	  if ( RigidName.Quantity < 1 ) return;
	  Read();

	  Num = (int*)Memory(RigidName.Quantity+1,sizeof(int));

	  for ( i=0; i<QuantityRigid; i++ ) {
        pRL = &pRigid[i];
        if (pRL->QuantityRgd == 0 ) continue;
        for ( j=0; j<pRL->QuantityRgd-1; j++ ) if ( strcmpup((char*)&pRL->pRgd[j].b,"NMRGD") == 0 ) {
           if ( pRL->pRgd[j+1].b == 0 ) {
              n = pRL->pRgd[j+1].d + 0.1;
              if ( n && n <= RigidName.Quantity ) Num[n] = 1;
              break;  }
           }
        }

	  for ( i=0,n=0; i<RigidName.Quantity; i++ ) {
        if ( Num[i+1] == 0 ) {
           if ( RigidName.Name[i] ) MemoryFree(RigidName.Name[i]);
           }
        else {
           RigidName.Name[n] = RigidName.Name[i];
           Num[i+1] = ++n;  }
        }
     if ( n < RigidName.Quantity ) SpaceSet(&RigidName.Name[n],(RigidName.Quantity-n)*sizeof(LPSTR));

	  for ( i=0; i<GetQuantityRigid(); i++ ) {
        pRL = &pRigid[i];
        if ( pRL->QuantityRgd == 0 ) continue;
        for ( j=0; j<pRL->QuantityRgd-1; j++ ) if ( strcmpup((char*)&pRL->pRgd[j].b,"NMRGD") == 0 ) {
           if ( pRL->pRgd[j+1].b == 0 ) {
              k = pRL->pRgd[j+1].d + 0.1;
              if ( k && k <= RigidName.Quantity ) pRL->pRgd[j+1].d = Num[k];
              break;  }
           }
        }
     RigidName.Quantity = n;

	  MemoryFree(Num);

}