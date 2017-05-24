#include <stdafx.h>
#include <classwin.h>
#include <inp_rgd.h>
#include <stdio.h>

EXPORT void RigidType( WORD QuantitySF, TYPE_DATA_SF * SF,
		INFRGD *infrgd, WORD &QuantitySymbol, BYTE &Type )
{
      WORD i;
      static char *s_rgd[] = { "PSE", "GE", "PL", "OB", "VL", "MG", "OSD", "SPB", "" };
      LPSTR pS;
      char s[32];

      QuantitySymbol = 0;  Type = 0;
      if ( QuantitySF == 0 ) return;

      for ( i=0; i<QuantitySF; i++ ) {
	 pS = (char*)&SF[i].b;
	 if ( pS[0] || i == 0 && pS[0] == 0 ) {
	    ToupRus(pS);
	    memset(&infrgd[QuantitySymbol],0,sizeof(INFRGD));
	    K_RGD(QuantitySymbol)   = i;
	    F_RGD(QuantitySymbol++) = pS;
            if ( strcmp(pS,"NAME") == 0 && i < QuantitySF - 1 ) {
 	       pS = (char*)&SF[i+1].b;  if ( pS[0] ) continue;
               sprintf(s,"%lf",SF[i+1].d);  s[8] = 0;
               strcpy(pS,s);  }
	    }  }
      K_RGD(QuantitySymbol) = QuantitySF;
      for ( i=1; i<=QuantitySymbol; i++ ) K_RGD(i-1) = K_RGD(i) - K_RGD(i-1);

      if ( QuantitySymbol > 1 || SF[0].b ) {
	 Type = 1;
	 for ( i=0; s_rgd[i][0]; i++ )
	    if ( strncmp((char*)&SF[0].b,s_rgd[i],strlen(s_rgd[i])) == 0 ) {
	    if ( i == 0 ) Type = 5;
	    if ( i == 1 || i == 2 ) Type = 2;
	    if ( i == 3 || i == 4 ) Type = 3;
	    if ( i == 5 ) Type = 4;
	    if ( i == 6 ) Type = 6;
	    if ( i == 7 ) Type = 11;
	    break;  }
	 }
}

EXPORT int RigidIdentCompress( int QuantitySymbol, INFRGD *infrgd, TYPE_DATA_SF * SF )
{
          int i, j, k = 0;
          INFRGD *infrab;
          TYPE_DATA_SF *pTD;

          for ( i=0; i<QuantitySymbol; i++ ) {
             infrab = &infrgd[i];
             if ( RF_RGD == NULL ) continue;
             pTD = (TYPE_DATA_SF*)RF_RGD;
             for ( j=0; j<RK_RGD; j++ )
                memcpy(&SF[k++],&pTD[j],sizeof(TYPE_DATA_SF));
             }
          return k;
}