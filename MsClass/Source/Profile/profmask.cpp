#include <stdafx.h>
#include "profile.h"

void PROFILE::InitMask()
{
        char Name[MAXPATH];
        DWORD Len, Pos;
        int i, n;
        FILEWORK  Mask;

        if ( this == NULL ) return;

        if ( NameBase[0] == 0 ) return;

        if ( PosMask )  MemoryFree(PosMask);   PosMask  = NULL;
        if ( MaskData ) MemoryFree(MaskData);  MaskData = NULL;
        if ( BufMask )  MemoryFree(BufMask);   BufMask  = NULL;
        LenMaskData = 0;

        sprintf(Name,"%s.prm",NameBase);

        for ( i=0, n=0; i<QuantityTypeSection; i++ )
           if ( Section[i].QuantityString > n ) n = Section[i].QuantityString;

		if ( access(GetPath(Name),0) ) return;
		   
		BufMask = (BYTE*)Memory(n);


        Mask.Open(GetPath(Name),"+rw");
        LenMaskData = Mask.GetLength();
        MaskData = (BYTE*)Memory(LenMaskData+1);
        Mask.Read(MaskData,LenMaskData,0);
        Mask.Close();

        QuantityMask = 0;  Pos = 0;
        while ( 1 ) {
           if ( Pos >= LenMaskData ) break;
           Len = ((WORD*)(MaskData+Pos))[0];
           if ( Len == 0 ) break;
           QuantityMask++;  Pos += Len;   }

        PosMask  = (DWORD*)Memory(QuantityMask+1,sizeof(DWORD));

        QuantityMask = 0;  Pos = 0;
        while ( 1 ) {
           PosMask[QuantityMask] = Pos;
           if ( Pos >= LenMaskData ) break;
           Len = ((WORD*)(MaskData+Pos))[0];
           if ( Len == 0 ) break;
           QuantityMask++;    Pos += Len;  }

}

LPSTR  EXPORT  PROFILE::GetNameMask( int NumPP )
{
        if ( NumPP == 0 || NumPP > QuantityMask ) return NULL;
        return (LPSTR)(MaskData + PosMask[NumPP-1] + sizeof(WORD) + 1 );
}

void   EXPORT  PROFILE::DeleteMask( int NumPP )
{
        int i;
        FILEWORK        Mask;
        char Name[MAXPATH];

        if ( NumPP == 0 || NumPP > QuantityMask ) return;

        sprintf(Name,"%s.prm",NameBase);
        Mask.Open(GetPath(Name),"rw");
        for ( i=0; i<QuantityMask; i++ ) {
           if ( i == NumPP - 1 ) continue;
           Mask.Write(MaskData+PosMask[i],PosMask[i+1] - PosMask[i]);
           }
        Mask.Close();
        InitMask();
}

void   EXPORT   PROFILE::SetMask( int NumPP )
{
        int i, j, k;
        SECTION *pSEC;
        GRAF *pG;
        WORD Qnt;
        char *pS;

        if ( NumPP == 0 || NumPP > QuantityMask ) {
           for ( i=0; i<QuantityTypeSection; i++ ) {
              pSEC = &Section[i];
              for ( j=0; j<pSEC->QuantityString; j++ ) {
                 pG = (GRAF*) ( pSEC->Graf
                    + j * ( ( pSEC->QuantityGraf - 1 ) * sizeof(float) + MAX_STRING_NAME + 1 ) );
                 pG->Mask = 1;  }  }
           return;  }

        pS = (LPSTR)(MaskData + PosMask[NumPP-1] + sizeof(WORD));
        pS += pS[0] + 2;

        for ( i=0; i<QuantityTypeSection; i++ ) {
           pSEC = GetSection(pS+1,1);  pS += pS[0] + 2;
           if ( pSEC == NULL ) break;
           k = Qnt = ((WORD*)pS)[0];  pS += sizeof(WORD);
           if ( Qnt > pSEC->QuantityString ) Qnt = pSEC->QuantityString;
           for ( j=0; j<Qnt; j++ ) {
              pG = (GRAF*) ( pSEC->Graf
                 + j * ( ( pSEC->QuantityGraf - 1 ) * sizeof(float) + MAX_STRING_NAME + 1 ) );
              pG->Mask = pS[j];   }
           pS += k;  }

}

int     EXPORT   PROFILE::YesModifyMask( int NumPP )
{
        int i, j, k;
        SECTION *pSEC;
        GRAF *pG;
        WORD Qnt;
        char *pS;

        if ( NumPP == 0 || NumPP > QuantityMask ) {
           for ( i=0; i<QuantityTypeSection; i++ ) {
              pSEC = &Section[i];
              for ( j=0; j<pSEC->QuantityString; j++ ) {
                 pG = (GRAF*) ( pSEC->Graf
                    + j * ( ( pSEC->QuantityGraf - 1 ) * sizeof(float) + MAX_STRING_NAME + 1 ) );
                 if ( pG->Mask == 0 ) return 1;
                 }  }
           return 0;  }

        pS = (LPSTR)(MaskData + PosMask[NumPP-1] + sizeof(WORD));
        pS += pS[0] + 2;

        for ( i=0; i<QuantityTypeSection; i++ ) {
           pSEC = GetSection(pS+1,1);  pS += pS[0] + 2;
           if ( pSEC == NULL ) break;
           k = Qnt = ((WORD*)pS)[0];  pS += sizeof(WORD);
           if ( Qnt > pSEC->QuantityString ) Qnt = pSEC->QuantityString;
           for ( j=0; j<Qnt; j++ ) {
              pG = (GRAF*) ( pSEC->Graf
                 + j * ( ( pSEC->QuantityGraf - 1 ) * sizeof(float) + MAX_STRING_NAME + 1 ) );
              if ( pG->Mask != pS[j] ) return 1;
              }
           pS += k;  }

        return 0;

}

int    EXPORT  PROFILE::AddMask( LPSTR Name, int Reg )
{
        int i, j;
        WORD Len;
        DWORD Pos;
        SECTION *pSEC;
        GRAF *pG;
        FILEWORK        Mask;
        char Text[MAXPATH];
        static BYTE b=0;

        sprintf(Text,"%s.prm",NameBase);
        Mask.Open(GetPath(Text),"rw");
        Mask.Write(MaskData,LenMaskData);

        Pos = Mask.GetPosition();
        Mask.Write(&Len,sizeof(WORD));
        Mask.StringWrite(Name);
        Mask.Write(&b,1);

        for ( i=0; i<QuantityTypeSection; i++ ) {
           pSEC = &Section[i];
           Mask.StringWrite(pSEC->NameFile);
           Mask.Write(&b,1);
           Mask.Write(&pSEC->QuantityString,sizeof(WORD));
           for ( j=0; j<pSEC->QuantityString; j++ ) {
              pG = (GRAF*) ( pSEC->Graf
                 + j * ( ( pSEC->QuantityGraf - 1 ) * sizeof(float) + MAX_STRING_NAME  + 1 ) );
              BufMask[j] = pG->Mask;
              }
           Mask.Write(BufMask,pSEC->QuantityString);   }

        Len = Mask.GetPosition() - Pos;
        Mask.Write(&Len,sizeof(WORD),Pos);
        Mask.Close();

        if ( Reg ) InitMask();

        return QuantityMask;
}

void  EXPORT  PROFILE::ChangeMask( int Num, LPSTR Name )
{
        int i, n;
        char NameFile[MAX_PATH];

        AddMask(Name);

        sprintf(NameFile,"%s.prm",NameBase);
        DeleteFile(GetPath(NameFile));

        for ( i=1; i<=QuantityMask; i++ ) {
           n = i;
           if ( i == Num ) n = QuantityMask;
           SetMask(n);
           if ( i == QuantityMask && Num && Num < QuantityMask ) break;
           AddMask(GetNameMask(n),0);    }

        InitMask();
        SetMask(Num);

}