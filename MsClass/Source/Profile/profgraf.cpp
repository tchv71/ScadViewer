#include <stdafx.h>
#include "profile.h"

EXPORT float * PROFILE::GetGraf( LPCSTR name, int NumString, BYTE TypeName, int NumGraf, LPSTR UnitsGraf )
{
        int  i, n=0;
        float *pF, cf[10];
        char TextL[10][40];
        STRING_PROFILE * pSP = GetString(name,NumString,TypeName);
        SECTION *pSC;
        static float q;

        pSC = &Section[FullInfo.NumSection-1];

        strcpy(TextL[0],UnitOutM.Name);  cf[0] = UnitOutS.coef /  UnitOutM.coef;
        for ( i=1; i<6; i++ ) {
           sprintf(TextL[i],"%s^%d",UnitOutS.Name,i+1);
           cf[i] = cf[i-1] * UnitOutS.coef /  UnitOutM.coef;
           }
        cf[0] = 1;

        if ( UnitOutPL.coef == 0 ) {
           sprintf(TextL[6],"%s/%s",UnitOutT.Name,UnitOutM.Name);
           cf[6] = 1;
           }
        else {
           sprintf(TextL[6],"%s/%s",UnitOutT.Name,UnitOutPL.Name);
           cf[6] = UnitOutM.coef / UnitOutPL.coef;
           }

        TextL[7][0] = 0;
        cf[7] = 1;

        if ( NumGraf == 0 || NumGraf > pSC->QuantityGraf ) return NULL;
        pF = &q;

        switch ( pSC->TypeGraf[NumGraf-1] ){

           case  1:  q = FullInfo.h;   break;
           case  2:  q = FullInfo.b;   break;
           case  3:  q = FullInfo.s;   break;
           case  4:  q = FullInfo.t;   break;
           case  5:  q = FullInfo.d;   break;
           case  7:  q = FullInfo.R;   break;
           case  8:  q = FullInfo.r;   break;
           case  9:  q = FullInfo.hs;   break;
           case 10:  q = FullInfo.Gamma;   n = 7;   break;

           case 11:  q = FullInfo.x0;  break;
           case 12:  q = FullInfo.y0;  break;
           case 13:  q = FullInfo.xm;  break;
           case 14:  q = FullInfo.Alfa;     n = 7;   break;
           case 15:  q = FullInfo.TanAlfa;  n = 7;   break;

           case 21:  q = FullInfo.Ix;  n = 3;  break;
           case 22:  q = FullInfo.Wx;  n = 2;  break;
           case 23:  q = FullInfo.Sx;  n = 2;  break;
           case 24:  q = FullInfo.ix;          break;

           case 26:  q = FullInfo.Iy;  n = 3;  break;
           case 27:  q = FullInfo.Wy;  n = 2;  break;
           case 28:  q = FullInfo.Sy;  n = 2;  break;
           case 29:  q = FullInfo.iy;          break;

           case 30:  q = FullInfo.Ixy; n = 3;  break;

           case 31:  q = FullInfo.Ix1; n = 3;  break;
           case 32:  q = FullInfo.Wx1; n = 2;  break;
           case 33:  q = FullInfo.Sx1; n = 2;  break;
           case 34:  q = FullInfo.ix1;         break;

           case 36:  q = FullInfo.Iy1; n = 3;  break;
           case 37:  q = FullInfo.Wy1; n = 2;  break;
           case 38:  q = FullInfo.Sy1; n = 2;  break;
           case 39:  q = FullInfo.iy1;         break;

           case 41:  q = FullInfo.A;   n = 1;  break;
           case 42:  q = FullInfo.nA;  n = 7;  break;
           case 43:  q = FullInfo.P;   n = 6;  break;
           case 44:  q = FullInfo.JX;  n = 3;  break;
           case 45:  q = FullInfo.JY;  n = 3;  break;
           case 46:  q = FullInfo.Ikr; n = 3;  break;
           case 47:  q = FullInfo.IFx; n = 1;  break;
           case 48:  q = FullInfo.IFy; n = 1;  break;
           case 49:  q = FullInfo.Iom; n = 5;  break;

           case 51:  q = FullInfo.x1;          break;
           case 52:  q = FullInfo.x2;          break;
           case 53:  q = FullInfo.y1;          break;
           case 54:  q = FullInfo.y2;          break;

           case 56:  q = FullInfo.Wplx; n = 2; break;
           case 57:  q = FullInfo.Wply; n = 2; break;

           case 61:  q = FullInfo.Riska[0];    break;
           case 62:  q = FullInfo.Riska[1];    break;
           case 63:  q = FullInfo.Riska[2];    break;
           case 64:  q = FullInfo.Riska[3];    break;
           case 65:  q = FullInfo.Riska[4];    break;
           case 66:  q = FullInfo.Riska[5];    break;
           case 67:  q = FullInfo.Riska[6];    break;
           case 68:  q = FullInfo.Riska[7];    break;
           case 69:  q = FullInfo.Riska[8];    break;
           case 70:  q = FullInfo.Riska[9];    break;

           case 71:  q = FullInfo.BoltMaxDiam[0];      break;
           case 72:  q = FullInfo.BoltMaxDiam[1];      break;
           case 73:  q = FullInfo.BoltMaxDiam[2];      break;
           case 74:  q = FullInfo.BoltMaxDiam[3];      break;
           case 75:  q = FullInfo.BoltMaxDiam[4];      break;
           case 76:  q = FullInfo.BoltMaxDiam[5];      break;
           case 77:  q = FullInfo.BoltMaxDiam[6];      break;
           case 78:  q = FullInfo.BoltMaxDiam[7];      break;
           case 79:  q = FullInfo.BoltMaxDiam[8];      break;
           case 80:  q = FullInfo.BoltMaxDiam[9];      break;

           case 81:  q = FullInfo.PosBolt[0];          break;
           case 82:  q = FullInfo.PosBolt[1];          break;
           case 83:  q = FullInfo.PosBolt[2];          break;
           case 84:  q = FullInfo.PosBolt[3];          break;
           case 85:  q = FullInfo.PosBolt[4];          break;
           case 86:  q = FullInfo.PosBolt[5];          break;
           case 87:  q = FullInfo.PosBolt[6];          break;
           case 88:  q = FullInfo.PosBolt[7];          break;
           case 89:  q = FullInfo.PosBolt[8];          break;
           case 90:  q = FullInfo.PosBolt[9];          break;

           case 91:  q = FullInfo.n1;     n = 7;       break;
           case 92:  q = FullInfo.n2;     n = 7;       break;

           case 93:  q = FullInfo.WxMin;  n = 2;       break;
           case 94:  q = FullInfo.WxMax;  n = 2;       break;
           case 95:  q = FullInfo.WyMin;  n = 2;       break;
           case 96:  q = FullInfo.WyMax;  n = 2;       break;


           default : pF = NULL;                        break;

           }

        if ( pF ) *pF *= cf[n];
        strcpy(UnitsGraf,TextL[n]);

        return pF;

}