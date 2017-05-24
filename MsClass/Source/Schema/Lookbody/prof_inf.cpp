#include <stdafx.h>
#include <schema.h>

/*
201 - двутавpы
202 - тавpы
203 - швеллеpа
204 - уголки с pавными полками
205 - уголки с неpавными полками
206 - уголки pавнoполочные спаpенные
207 - уголки неpавнoполочные спаpенные длинными полками
208 - уголки неpавнoполочные спаpенные коpоткими полками
209 - уголки pавнoполочные спаpенные углами
210 - спаpенные двутавpы
*/

void SCHEMA::ProfileInform( FORMAT &pF, WORD &kNode, WORD &kElem )
{
       BYTE Tp, Control;
       TYPE_DATA_SF *pTDS;
       WORD  * Lst;
       WORD Qnt, i, n;
       STRING_PROFILE *pSP;

       kNode = kElem = 0;

       if ( ElemType(pF.TypeElem) != 1 || pF.TypeRigid == 0 ) return;

       _Rigid.GetRigidType(pF.TypeRigid,Tp,Qnt,&pTDS,i,&Lst);
       if ( Qnt == 0 ) return;
	   Control = 0;	
       pSP = _Profile->GetInform(pTDS,Qnt,Control);
       if ( pSP == NULL || Control == 2 ) return;
       if ( pSP->Group == 99 ) {
          for ( i=0; pTDS[i].b == 0;  i++ );
          pSP = _Profile->GetInform(&pTDS[i],Qnt-i,Control);
          if ( pSP == NULL || Control == 2 ) return;
          }
       n = pSP->Group;

       switch ( pSP->Group ) {

	  case   0:  kNode =  8;  kElem =  4;  break;
	  case   1:
	  case   2:  kNode = 16;  kElem =  8;  break;
	  case   3:  kNode = 24;  kElem = 12;  break;
	  case   4:  kNode = 16;  kElem =  8;  break;
          case   5:  kNode =  8;  kElem =  4;  break;
	  case   6:  kNode = 32;  kElem = 16;  break;
	  case   7:  kNode = 24;  kElem = 12;  break;
	  case   8:  kNode = 2 * pSP->QuantityGeom; kElem = pSP->QuantityGeom;
		     break;
	  case 201:  kNode = 12;  kElem = 3;   break;
	  case 202:  kNode =  8;  kElem = 2;   break;
	  case 203:  kNode =  8;  kElem = 3;   break;
	  case 204:
	  case 205:
	  case 218:
          case 217:  kNode =  6;  kElem = 2;   break;
	  case 206:
	  case 207:
	  case 208:
	  case 209:  kNode = 12;   kElem = 4;  break;
	  case 216:  kNode = 32;   kElem = 16; break;
     case 219:
     case 220:  kNode =  8;  kElem = 4;   break;
	  default: return;
	  }

       pF.Check = n + 1;

       return;
}