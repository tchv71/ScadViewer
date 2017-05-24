#include <stdafx.h>
#include <schema.h>
#include <fund.h>

EXPORT FUND::~FUND(void) {  Delete();  }

EXPORT void FUND::Init(FILEBASE &FilePrj, DOCUMENT &Doc) {
       File = &FilePrj;   PosFile = (DWORD*)&Doc;
       Read();   }

EXPORT void FUND::Delete(void)
{
         if ( this == NULL ) return;
	 if ( NumElem ) MemoryFree(NumElem);
	 if ( Angle )   MemoryFree(Angle);
	 BOUND::Delete();
	 Init();
}

EXPORT void FUND::Delete(WORD Num) {
	  Read();
	  BOUND::Delete(Num);
          Modify = 1;
}

EXPORT void FUND::DeleteAllNode(void)
{
	 BOUND::Delete();
	 if ( Angle )   MemoryFree(Angle);
	 Angle = NULL;
	 Modify = 1;
}

EXPORT void FUND::SetListElem( WORD Qnt,WORD  *Lst )
{
	WORD *pW;
	Read();
	if ( Qnt > QuantityElem ) {
	   pW = (WORD*)Memory(Qnt,sizeof(WORD));
	   if ( NumElem ) MemoryFree(NumElem);
           NumElem = pW;  }
        SpaceCopy(NumElem,Lst,(long)Qnt*sizeof(WORD));
	QuantityElem = Qnt;
	Modify = 1;
}

void EXPORT  FUND::GetListElem( WORD &Qnt,WORD **Lst ){
	Qnt = QuantityElem;
	*Lst = NumElem;
}

EXPORT WORD FUND::GetQuantityListNode()
{
	 Read();
	 return QuantityBound;
}

EXPORT int FUND::Change(WORD Num, float Ang, WORD Qnt,WORD *Lst )
{
	  Read();
	  if ( BOUND::Change(Num,0,Num,Qnt,Lst) ) return 1;
	  Angle[Num-1] = Ang;
          Modify = 1;
	  return 0;
}

EXPORT void FUND::Include( float Ang, WORD Qnt,WORD *Lst )
{
    	  float *pF;
    	  Read();
    	  pF = (float*)Memory(QuantityBound+1,sizeof(float));
    	  if ( Angle ) {
             SpaceCopy(pF,Angle,QuantityBound*(long)sizeof(float));
	     MemoryFree(Angle);  }
          Angle = pF;
          Angle[QuantityBound] = Ang;
          BOUND::Include(0,QuantityBound+1,Qnt,Lst);
}

EXPORT void FUND::GetListNode(WORD Num,float &Ang, WORD &Qnt,WORD **Lst )
{
	  BYTE Tp;
	  WORD Msk;
	  GetBound(Num,Tp,Msk,Qnt,Lst);
	  Ang = Angle[Msk-1];
}

EXPORT BYTE FUND::GetModify() {
	  if ( Modify || BOUND::Modify ) return 1;
          return 0;
}

EXPORT void FUND::Compress(WORD QnttElem, WORD QuantityNode )
{
	  int i, k;
	  float *pF;

	  Read();
	  BOUND::Compress(QuantityNode);

	  pF = (float*)Memory(QuantityBound+1,sizeof(float));
	  for ( i=0; i<QuantityBound; i++ ) {
	     pF[i] = Angle[pBound[i].Mask-1];
	     pBound[i].Mask = i + 1;
	     }
          if ( Angle ) MemoryFree(Angle);
	  Angle = pF;

	  for ( i=0,k=0; i<QuantityElem; i++ )
             if ( NumElem[i] && NumElem[i] <= QnttElem )
	        NumElem[k++] = NumElem[i];

          QuantityElem = k;
          Modify = 1;

}

EXPORT void FUND::Write( FILEBASE &Work, WORD QnttElem, WORD QuantityNode )
{
	  Write(Work,QnttElem,NULL,0,QuantityNode,NULL);
}

EXPORT void FUND::Write( FILEBASE &Work, WORD QuantityOldElem, WORD NumNewElem[],
        WORD QuantityNode, WORD QuantityOldNode, WORD NumNode[] )
{
	     WORD i, n, m;
	     WORD *Num, *NumN;
        DWORD Pos;
        float *A;
        MEMORY MEM;

	     Read();

        if ( NumNewElem ) {
	        Num = (WORD*)Memory(QuantityElem+1,sizeof(WORD));
	        for ( i=0,n=0; i<QuantityElem; i++ ) {
              m = NumNewElem[NumElem[i]];
              if ( m ) Num[n++] = m;  }
           QuantityElem = n;
           MemoryFree(NumElem);
           NumElem = Num;  }

        n = QuantityBound;
        if ( n ) YesNode = 1;
        else YesNode = 0;

        if ( NumElem ) {
           NumN = (WORD*)MemAlloc(sizeof(WORD),QuantityElem);
           SpaceCopy(NumN,NumElem,(long)sizeof(WORD)*QuantityElem);
           MemoryFree(NumElem);
           NumElem = NULL;   }
	     if ( n ) {
           A = (FLOAT*)MemAlloc(sizeof(float),n);
           SpaceCopy(A,Angle,(long)sizeof(float)*n);
           MemoryFree(Angle);
           Angle = NULL;   }

        Pos = PosFile[0] = Work.GetLength();
        Work.Write(&CalcLoad,3);
        if ( YesNode ) {
           BOUND::Write(Work,QuantityOldNode,QuantityNode,NumNode);
           if ( PosFile[0] == 0 ) {
              i = 0;
              Work.Write(&i,sizeof(WORD));
              }
           PosFile[0] = Pos;  }

	     Work.Write(&QuantityElem,sizeof(WORD));
	     if ( QuantityElem ) Work.Write(NumN,(long)sizeof(WORD)*QuantityElem);
	     if ( n ) Work.Write(A,(long)sizeof(float)*n);
        MemFree(NumN);
        MemFree(A);

	     PosFile[1] = Work.GetLength() - *PosFile;

	     Delete();

}

EXPORT void FUND::Read()
{
   if ( NumElem || Angle ) return;
   if ( PosFile[1] == 0 ) return;
   File->Read(&CalcLoad,3,PosFile[0]);
   PosFile[0] += 3;
   if ( YesNode ) BOUND::Read();
   File->Read(&QuantityElem,sizeof(WORD));
   NumElem = (WORD*)Memory(QuantityElem+1,sizeof(WORD));
   File->Read(NumElem,(long)sizeof(WORD)*QuantityElem);
   Angle = (float*)Memory(QuantityBound+1,sizeof(float));
   File->Read(Angle,(long)sizeof(float)*QuantityBound);
   PosFile[0] -= 3;
}