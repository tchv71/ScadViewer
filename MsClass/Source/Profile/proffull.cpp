#include <stdafx.h>
#include "profile.h"

EXPORT STRING_PROFILE * PROFILE::GetString( LPCSTR name, int NumString, BYTE TypeName )
{
        int n, m = NumString;

         n = GetNumSection(name,TypeName);
         if ( n == 0 && name[0] == 'D' ) {
           n = GetNumSection("DIAMOLD",TypeName);
           if ( n ) {
              if ( strcmp(name,"DIAM2") == 0 ) m += 236;
              if ( strcmp(name,"DIAM3") == 0 ) m += 236 + 226;
              }  }
        return GetString(n,m);
}

EXPORT STRING_PROFILE * PROFILE::GetString( int NumPP, int NumString )
{
        SECTION *pSC;
        LPCSTR pS;
        int i, Group;
        float *f, r, q;
        float UnitsL, UnitsLL, UnitsLLL, UnitsLLLL;
        double sn, cn, xn, yn, a, ad;

        pS = GetStringName(NumPP,NumString);
        if ( pS == NULL ) return NULL;

        pSC = &Section[NumPP-1];
        Group = pSC->Group;
        ClearString();
        FullInfo.NumSection = NumPP;
        FullInfo.Mask = ((GRAF*)pS)->Mask;
        strncpy(FullInfo.NameSection,pSC->Name[NumLanguage],MAX_SECTION_NAME-1);
        strncpy(FullInfo.NameString,pS,MAX_STRING_NAME-1);

        if ( pSC->Group == 17 || pSC->Group == 18 )
           for ( i=0; i<QuantityTypeSection; i++ )
              if ( Section[i].Group == 4 && pSC->Group == 18 ||
                   Section[i].Group == 5 && pSC->Group == 17 ) {
                 pSC = &Section[i];
                 pS = GetStringName(i+1,NumString);
                 if ( pS == NULL ) return NULL;
                 goto _10;  }

_10:    f = (float*) ( pS + MAX_STRING_NAME + 1 );

        FullInfo.E = GetE();
        FullInfo.nu = nu;
        FullInfo.ro = GetRO();

        UnitsL    = UnitOutM.coef;
        UnitsLL   = UnitsL * UnitsL;
        UnitsLLL  = UnitsL * UnitsL * UnitsL;
        UnitsLLLL = UnitsL * UnitsL * UnitsL * UnitsL;

        for ( i=1; i<pSC->QuantityGraf; i ++ ) {

           r = f[i-1] / UnitGraf[pSC->TypeGraf[i]].coef;

           switch ( pSC->TypeGraf[i] ){

              case  1:  FullInfo.h = r * UnitsL;   break;
              case  2:  FullInfo.b = r * UnitsL;   break;
              case  3:  FullInfo.s = r * UnitsL;   break;
              case  4:  FullInfo.t = r * UnitsL;   break;
              case  5:  FullInfo.d = r * UnitsL;   break;
              case  7:  FullInfo.R = r * UnitsL;   break;
              case  8:  FullInfo.r = r * UnitsL;   break;
              case  9:  FullInfo.hs = r * UnitsL;  break;
              case 10:  FullInfo.Gamma = r;        break;

              case 11:  FullInfo.x0 = r * UnitsL;  break;
              case 12:  FullInfo.y0 = r * UnitsL;  break;
              case 13:  FullInfo.xm = r * UnitsL;  break;
              case 14:  FullInfo.Alfa = r;
                        FullInfo.TanAlfa = tan(FullInfo.Alfa * M_PI / 180);
                        break;
              case 15:  FullInfo.TanAlfa = r;
                        FullInfo.Alfa = atan(FullInfo.TanAlfa) * 180 / M_PI;
                        break;

              case 21:  FullInfo.Ix = r * UnitsLLLL;  break;
              case 22:  FullInfo.Wx = r * UnitsLLL;   break;
              case 23:  FullInfo.Sx = r * UnitsLLL;   break;
              case 24:  FullInfo.ix = r * UnitsL;     break;

              case 26:  FullInfo.Iy = r * UnitsLLLL;  break;
              case 27:  FullInfo.Wy = r * UnitsLLL;   break;
              case 28:  FullInfo.Sy = r * UnitsLLL;   break;
              case 29:  FullInfo.iy = r * UnitsL;     break;

              case 30:  FullInfo.Ixy = r * UnitsLLLL;  break;

              case 31:  FullInfo.Ix1 = r * UnitsLLLL; break;
              case 32:  FullInfo.Wx1 = r * UnitsLLL;  break;
              case 33:  FullInfo.Sx1 = r * UnitsLLL;  break;
              case 34:  FullInfo.ix1 = r * UnitsL;    break;

              case 36:  FullInfo.Iy1 = r * UnitsLLLL; break;
              case 37:  FullInfo.Wy1 = r * UnitsLLL;  break;
              case 38:  FullInfo.Sy1 = r * UnitsLLL;  break;
              case 39:  FullInfo.iy1 = r * UnitsL;    break;

              case 41:  FullInfo.A = r * UnitsLL;     break;
              case 42:  FullInfo.nA = r ;              break;
              case 43:  FullInfo.P = r * UnitOutT.coef / UnitsL;
                        break;
              case 44:  FullInfo.JX = r * UnitsLLLL;   break;
              case 45:  FullInfo.JY = r * UnitsLLLL;   break;
              case 46:  FullInfo.Ikr = r * UnitsLLLL;    break;
              case 47:  FullInfo.IFx = r * UnitsLL;    break;
              case 48:  FullInfo.IFy = r * UnitsLL;    break;
              case 49:  FullInfo.Iom = r * UnitsLL * UnitsLLLL;  break;

              case 51:  FullInfo.x1 = r * UnitsL;  break;
              case 52:  FullInfo.x2 = r * UnitsL;  break;
              case 53:  FullInfo.y1 = r * UnitsL;  break;
              case 54:  FullInfo.y2 = r * UnitsL;  break;

              case 56:  FullInfo.Wplx = r * UnitsLLL;  break;
              case 57:  FullInfo.Wply = r * UnitsLLL;  break;

              case 61:  FullInfo.Riska[0] = r * UnitsL;   break;
              case 62:  FullInfo.Riska[1] = r * UnitsL;   break;
              case 63:  FullInfo.Riska[2] = r * UnitsL;   break;
              case 64:  FullInfo.Riska[3] = r * UnitsL;   break;
              case 65:  FullInfo.Riska[4] = r * UnitsL;   break;
              case 66:  FullInfo.Riska[5] = r * UnitsL;   break;
              case 67:  FullInfo.Riska[6] = r * UnitsL;   break;
              case 68:  FullInfo.Riska[7] = r * UnitsL;   break;
              case 69:  FullInfo.Riska[8] = r * UnitsL;   break;
              case 70:  FullInfo.Riska[9] = r * UnitsL;   break;

              case 71:  FullInfo.BoltMaxDiam[0] = r * UnitsL;   break;
              case 72:  FullInfo.BoltMaxDiam[1] = r * UnitsL;   break;
              case 73:  FullInfo.BoltMaxDiam[2] = r * UnitsL;   break;
              case 74:  FullInfo.BoltMaxDiam[3] = r * UnitsL;   break;
              case 75:  FullInfo.BoltMaxDiam[4] = r * UnitsL;   break;
              case 76:  FullInfo.BoltMaxDiam[5] = r * UnitsL;   break;
              case 77:  FullInfo.BoltMaxDiam[6] = r * UnitsL;   break;
              case 78:  FullInfo.BoltMaxDiam[7] = r * UnitsL;   break;
              case 79:  FullInfo.BoltMaxDiam[8] = r * UnitsL;   break;
              case 80:  FullInfo.BoltMaxDiam[9] = r * UnitsL;   break;

              case 81:  FullInfo.PosBolt[0] = r * UnitsL;   break;
              case 82:  FullInfo.PosBolt[1] = r * UnitsL;   break;
              case 83:  FullInfo.PosBolt[2] = r * UnitsL;   break;
              case 84:  FullInfo.PosBolt[3] = r * UnitsL;   break;
              case 85:  FullInfo.PosBolt[4] = r * UnitsL;   break;
              case 86:  FullInfo.PosBolt[5] = r * UnitsL;   break;
              case 87:  FullInfo.PosBolt[6] = r * UnitsL;   break;
              case 88:  FullInfo.PosBolt[7] = r * UnitsL;   break;
              case 89:  FullInfo.PosBolt[8] = r * UnitsL;   break;
              case 90:  FullInfo.PosBolt[9] = r * UnitsL;   break;

              case 91:  FullInfo.n1         = r;   break;
              case 92:  FullInfo.n2         = r;   break;

              case 93:  FullInfo.WxMin      = r * UnitsLLL;  break;
              case 94:  FullInfo.WxMax      = r * UnitsLLL;  break;
              case 95:  FullInfo.WyMin      = r * UnitsLLL;  break;
              case 96:  FullInfo.WyMax      = r * UnitsLLL;  break;

              default : break;

              }

           }

       if ( pSC->Group == 19 ){
          FullInfo.h = FullInfo.b;
          }

       if ( pSC->Group == 16 ){
          FullInfo.h = FullInfo.b;
          if ( FullInfo.Iy == 0 ) {
             float d1, d;
             d = FullInfo.h;
             d1 = ( d - 2 * FullInfo.s ) / d;
             FullInfo.Ix = 0.05 * ( 1 - d1 * d1 * d1 * d1 ) * d * d * d * d;
             }
          FullInfo.Iy = FullInfo.Ix;
          FullInfo.Wy = FullInfo.Wx;
          FullInfo.iy = FullInfo.ix;
          }

       r = FullInfo.Ix + FullInfo.Iy;
       if ( FullInfo.Ix == 0 || FullInfo.Iy == 0 ) r *= 2;

       if ( FullInfo.Ix1 == 0 && FullInfo.Iy1 == 0 ) {
          FullInfo.JX = FullInfo.Ix;  FullInfo.JY = FullInfo.Iy;
          if ( FullInfo.Iy == 0 ) FullInfo.JY = FullInfo.Ix;
          if ( FullInfo.Ix == 0 ) FullInfo.JX = FullInfo.Iy;
          }
       else if ( FullInfo.Ix1 ) {
           FullInfo.JX = FullInfo.Ix1;
           if ( FullInfo.Iy1 ) FullInfo.JY = FullInfo.Iy1;
           else FullInfo.JY = r - FullInfo.Ix1;
           }
           else {
              FullInfo.JY = FullInfo.Iy1;
              FullInfo.JX = r - FullInfo.Iy1;   }

       if ( FullInfo.JX == 0 ) {
          if ( FullInfo.Ix1 == 0 && FullInfo.Iy1 == 0 ) FullInfo.JX = FullInfo.Ix1;
          else if ( FullInfo.Iy1 ) FullInfo.JX = FullInfo.Ix - FullInfo.Iy1;
               else FullInfo.JX = FullInfo.Ix;
          }

       if ( FullInfo.JY == 0 ) {
          if ( FullInfo.Iy1 ) FullInfo.JY = FullInfo.Iy1;
          else if ( FullInfo.Ix1 ) FullInfo.JY = FullInfo.Iy - FullInfo.Ix1;
               else FullInfo.JY = FullInfo.Iy;
          }

       q = FullInfo.JX / FullInfo.A;
       r = FullInfo.JY / FullInfo.A;

       if ( Group == 4 || Group == 18 ) {
          FullInfo.b = FullInfo.h ;
          if ( FullInfo.x0 == 0 ) FullInfo.x0 = FullInfo.y0;
          if ( FullInfo.y0 == 0 ) FullInfo.y0 = FullInfo.x0;
          FullInfo.Alfa = 45;
          FullInfo.TanAlfa = 1;     }

       cn = FullInfo.Alfa * M_PI / 180;
       if ( Group == 17 || Group == 18 ) {
          FullInfo.Alfa *= -1;
          FullInfo.TanAlfa *= -1;    }
       sn = sin(cn);   cn = cos(cn);

       switch ( Group ) {

          case  1:
             FullInfo.y1 = FullInfo.y2 = 2 * q / FullInfo.h;
             FullInfo.x1 = FullInfo.x2 = 2 * r / FullInfo.b;
             break;
          case  2:
             FullInfo.x1 = FullInfo.x2 = 2 * r / FullInfo.b;
             FullInfo.y1 = q / FullInfo.y0;
             FullInfo.y2 = q / ( FullInfo.h - FullInfo.y0 );
             break;
          case  3:
             if ( TypeBase == 0 ) {
                FullInfo.y1 = FullInfo.y2 = 2 * q / FullInfo.h;
                FullInfo.x2 = r / FullInfo.x0;
                FullInfo.x1 = r / ( FullInfo.b - FullInfo.x0 );   }
             else {
                FullInfo.x1 = FullInfo.x2 = 2 * q / FullInfo.h;
                FullInfo.y2 = r / FullInfo.x0;
                FullInfo.y1 = r / ( FullInfo.b - FullInfo.y0 );   }
             break;
          case  4:
          case  5:
          case  17:
          case  18:
             FullInfo.x2 = r / ( cn * FullInfo.y0 + FullInfo.x0 * sn );
             xn  =  cn * ( FullInfo.b - FullInfo.x0 ) - sn * FullInfo.y0;
             yn  = -sn * ( FullInfo.b - FullInfo.x0 ) - cn * FullInfo.y0;
             a   = fabs( -sn * xn + yn * cn );
             FullInfo.y2 = -q / yn;
             xn  =  sn * ( FullInfo.h - FullInfo.y0 ) - cn * FullInfo.x0;
             yn  =  cn * ( FullInfo.h - FullInfo.y0 ) + sn * FullInfo.x0;
             ad   = fabs( -sn * xn + yn * cn );
             FullInfo.y1 = q / yn;
             if ( ad > a ) a = ad;
             FullInfo.x1 = r / a;
             if ( Group == 17 ||  Group == 18 ) {
                FullInfo.x0 = -FullInfo.x0;
                r = FullInfo.x1;
                FullInfo.x1 = FullInfo.x2;
                FullInfo.x2 = r;   }
             break;
          case  16:
             FullInfo.y1 = FullInfo.y2 = 2 * q / FullInfo.b;
             FullInfo.x1 = FullInfo.x2 = 2 * r / FullInfo.h;
             break;

          }

       FullInfo.Group = Group + 200;

       AddElast(&FullInfo);

       return &FullInfo;

}