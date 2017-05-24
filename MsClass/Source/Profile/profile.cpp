#include <stdafx.h>
#include "profile.h"

EXPORT void PROFILE::Init()
{
	if ( this == NULL ) return;
	memset(this,0,sizeof(PROFILE));
}

EXPORT int  PROFILE::Init(LPCSTR NmFile, int Language ) {

        int i;
        i =  Init(NmFile);
        SetLanguage(Language);
        return i;
}

EXPORT int  PROFILE::Init(LPCSTR NmFile )
{
	FILEBASE Inp;
	WORD i, j, k;
        BYTE Len;
	char Buf[512];
	char drive[MAXDRIVE];
	char dir[MAXDIR];
	char file[MAXFILE];
	char ext[MAXEXT];

        DWORD Size;
        SECTION *pSC;
        LPSTR pS;

        if ( this == NULL ) return 1;

        if ( strcmpup(NameFile,NmFile) == 0 ) return 0;
        Delete();

        strcpy(NameFile,NmFile);
        Inp.Open(NameFile,"rs");

        fnsplit(NameFile,drive,dir,file,ext);
        strncpy(NameBase,file,8);

        Inp.Read(Buf,8);
        if ( strncmp(Buf,"**PRFL**",8) ) return 1;
        Inp.Read(&QuantityLanguage,20,8);

        Name = (LPSTR*)Memory(QuantityLanguage+1,sizeof(LPSTR));

        for ( i=0; i<QuantityLanguage; i++ ) {
           Inp.StringRead(Buf,Len);
           Name[i] = (LPSTR)Memory(Len+1);
           strncpy(Name[i],Buf,Len);
           }

        UnitGraf = (UNITS*)Memory(QuantityTypeGraf+1,sizeof(UNITS));
        Inp.Read(&UnitGraf[1],QuantityTypeGraf*sizeof(UNITS));
        for ( i=0; i<QuantityTypeGraf; i++ )
           if ( UnitGraf[i].coef == 0 ) UnitGraf[i].coef = 1;

        Section = (SECTION*)Memory(QuantityTypeSection+1,sizeof(SECTION));

        for ( i=0; i<QuantityTypeSection; i++ ) {

            pSC = &Section[i];
            Inp.Read(pSC,16);
            pSC->Name = (LPSTR*)Memory(QuantityLanguage+1,sizeof(LPSTR));

            for ( j=0; j<QuantityLanguage; j++ ) {
               Inp.StringRead(Buf,Len);
               pSC->Name[j] = (LPSTR)Memory(Len+1);
               strncpy(pSC->Name[j],Buf,Len);
               }

            pSC->TypeGraf = (BYTE*)Memory(pSC->QuantityGraf+1);
            Inp.Read(pSC->TypeGraf,pSC->QuantityGraf);

            pSC->NameGraf = (LPSTR*)Memory(pSC->QuantityGraf+1,sizeof(LPSTR));
            pSC->NameGraf[0] = (LPSTR)Memory(pSC->LengthNamePrint+1);
            Inp.Read(pSC->NameGraf[0],pSC->LengthNamePrint);

            for ( j=1,k=0; j<pSC->LengthNamePrint && k<pSC->QuantityGraf; j++ )
               if ( pSC->NameGraf[0][j] == 0 ) {
                  pSC->NameGraf[++k] = &pSC->NameGraf[0][j+1];
                  }
            for ( j=k+1; j<pSC->QuantityGraf; j++ )
               pSC->NameGraf[j] = pSC->NameGraf[k];

            pSC->GrafPrint = (BYTE*)Memory(pSC->QuantityGraf+1);
            Inp.Read(pSC->GrafPrint,pSC->QuantityGraf);

            Size = ( pSC->QuantityString ) *
                   ( ( pSC->QuantityGraf - 1 ) * sizeof(float) + MAX_STRING_NAME + 1 );
            pS = pSC->Graf = (LPSTR)Memory(Size);

            for ( j=0; j<pSC->QuantityString; j++ ) {
               Inp.StringRead(pS);
               pS += MAX_STRING_NAME + 1;
               Inp.Read(pS,(pSC->QuantityGraf-1)*sizeof(float));
               pS += ( pSC->QuantityGraf - 1 ) * sizeof(float);
               }

            }

        Inp.Close();
        InitMask();
        SetMask(0);
        return 0;

}

EXPORT void PROFILE::Delete()
{
       int i, j;
       SECTION *Sect;
       int Lang;
       UNITS M, T, S;

       if ( this == NULL ) return;

       memcpy(&M,&UnitOutM,sizeof(UNITS));
       memcpy(&T,&UnitOutT,sizeof(UNITS));
       memcpy(&S,&UnitOutS,sizeof(UNITS));
       Lang = NumLanguage;

       if ( Name ) {
	       for ( i=0; i<QuantityLanguage; i++ )
	          if ( Name[i] ) MemoryFree(Name[i]);
	       MemoryFree(Name);  }
       if ( UnitGraf ) MemoryFree(UnitGraf);

       if ( Section ) {
	       for ( i=0; i<QuantityTypeSection; i++ ) {
	          Sect = &Section[i];
	          if ( Sect->Name  ) {
	             for ( j=0; j<QuantityLanguage; j++ )
	                if ( Sect->Name[j] ) MemoryFree(Sect->Name[j]);
                MemoryFree(Sect->Name);  }
	          if ( Sect->TypeGraf  ) MemoryFree(Sect->TypeGraf);
	          if ( Sect->GrafPrint ) MemoryFree(Sect->GrafPrint);
	          if ( Sect->NameGraf  ) {
                 MemoryFree(Sect->NameGraf[0]);
                 MemoryFree(Sect->NameGraf);    }
	          if ( Sect->Graf  ) MemoryFree(Sect->Graf);
	      }
	   MemoryFree(Section);	   }

      ClearString();

        if ( PosMask )  MemoryFree(PosMask);
        if ( MaskData ) MemoryFree(MaskData);
        if ( BufMask )  MemoryFree(BufMask);  
		
	     Init();

        memcpy(&UnitOutM,&M,sizeof(UNITS));
        memcpy(&UnitOutT,&T,sizeof(UNITS));
        memcpy(&UnitOutS,&S,sizeof(UNITS));
        NumLanguage = Lang;

};

EXPORT LPSTR  PROFILE::GetNameSection( int NumPP )
{
	 if ( NumPP < 1 || NumPP > QuantityTypeSection ) return NULL;
	 return Section[NumPP-1].Name[NumLanguage];
}

EXPORT LPSTR  PROFILE::GetName( int NumLanguage )
{
	 if ( NumLanguage >= 0 && NumLanguage < QuantityLanguage )
       return Name[NumLanguage];
    return "";
}

EXPORT LPSTR  PROFILE::GetNameFileSection( LPCSTR name )
{
	 SECTION *Sect = GetSection(name,0);
	 if ( Sect == NULL ) return NULL;
	 return Sect->NameFile;
}

EXPORT LPSTR    PROFILE::GetNameSection(LPSTR NmFile )
{
	 for ( int i=0; i<QuantityTypeSection; i++ )
	    if ( strcmpup(Section[i].NameFile,NmFile) == 0 ) {
               return Section[i].Name[NumLanguage];   }
	 return NULL;
}

EXPORT SECTION  * PROFILE::GetSection( LPCSTR Name, BYTE Type )
{
	 int i = GetNumSection(Name,Type);
	 if ( i == 0 ) return NULL;
	 return &Section[i-1];
}

EXPORT int   PROFILE::GetNumSection(LPCSTR name, BYTE TypeName )
{
	 for ( int i=0; i<QuantityTypeSection; i++ )
            if ( TypeName == 0 ) {
	       if ( strncmpup(name,Section[i].Name[NumLanguage],MAX_SECTION_NAME-1) == 0 )
	          return i + 1;  }
            else if ( strcmpup(name,Section[i].NameFile) == 0 ) return i + 1;
	 return 0;
}

EXPORT BYTE   PROFILE::GetGroupSection( LPCSTR name, BYTE TypeName  )
{
	 int i = GetNumSection(name,TypeName);
	 if ( i ) return Section[i-1].Group;
	 return 0;
}

EXPORT BYTE   PROFILE::GetGroupSection( int NumPP )
{
	 if ( NumPP && NumPP <= QuantityTypeSection )
            return Section[NumPP-1].Group;
	 return 0;
}

EXPORT int    PROFILE::GetQuantityString( LPCSTR name, BYTE TypeName )
{
	 int i = GetNumSection(name,TypeName);
	 if ( i ) return Section[i-1].QuantityString;
	 return 0;
}

EXPORT int    PROFILE::GetQuantityString( int NumPP )
{
	 if ( NumPP && NumPP <= QuantityTypeSection )
            return Section[NumPP-1].QuantityString;
         return 0;
}

EXPORT LPCSTR  PROFILE::GetStringName( LPCSTR name, int NumString, BYTE TypeName )
{
       int i = GetNumSection(name,TypeName);
       return GetStringName(i,NumString);
}

EXPORT LPCSTR PROFILE::GetStringName( int NumPP, int NumString )
{
       SECTION *pSC;

       if ( NumPP && NumPP <= QuantityTypeSection )
          pSC = &Section[NumPP-1];
       else return NULL;
       if ( NumString && NumString <= pSC->QuantityString )
          return pSC->Graf + ( NumString - 1 ) *
             ( ( pSC->QuantityGraf - 1 ) * sizeof(float) + MAX_STRING_NAME + 1 );
       return NULL;;
}

EXPORT float   PROFILE::GetE()
{
        return E * UnitOutT.coef / UnitOutM.coef / UnitOutM.coef;
}

EXPORT float   PROFILE::GetRO()
{
        return ro * UnitOutT.coef
                    / UnitOutM.coef / UnitOutM.coef / UnitOutM.coef;;
}

EXPORT void    PROFILE::SetLanguage ( int Language )
{
       if ( Language < 0 || Language >= QuantityLanguage ) NumLanguage = 0;
       else NumLanguage = Language;
}


EXPORT void    PROFILE:: SetUnit( UNITS &M, UNITS &S, UNITS &T )
{
       memcpy(&UnitOutM,&M,sizeof(UNITS));
       memcpy(&UnitOutS,&S,sizeof(UNITS));
       memcpy(&UnitOutT,&T,sizeof(UNITS));
}

EXPORT void   PROFILE:: SetUnitAdd( UNITS &PL )
{
       memcpy(&UnitOutPL,&PL,sizeof(UNITS));
}

void  PROFILE:: ClearString()
{
       if ( FullInfo.PriviteData )
          MemoryFree(FullInfo.PriviteData);
       if ( FullInfo.Geom ) MemoryFree(FullInfo.Geom);
       memset(&FullInfo,0,sizeof(STRING_PROFILE));
}