#include <stdafx.h>
#include <schema.h>

void ElemBodyGeom ( DECART  * Coord, float Eps ,
			 ELEM_BODY &EB, ELEM_BODY_GEOM &EBG );
int   LookInto( long ki, long Num[], long &kGr,  long kGm,  ELEM_BODY  * ElemBody,
	         ELEM_BODY_GEOM  * EBG, DECART  * LookCoord, float Eps, long  *NumElemBody  );
BOOL   Progress(int);

void SCHEMA::LookProc( DECART  *LookCoord, float Eps,
		       long kG,  ELEM_BODY  *EB,
		       long  * NumElemBody)
{

       long i, j, n, kGr, kGm=0, *Num, ki;
       ELEM_BODY_GEOM  * EBG;
       ELEM_BODY_GEOM *pEBGI;
       float rMin, rMax;
       int LookCross;

       kGr = kG;
       EBG = (ELEM_BODY_GEOM*)Memory(kG+1,sizeof(ELEM_BODY_GEOM));

       for ( i=0; i<kG; i++ )
	       ElemBodyGeom(LookCoord,Eps,EB[i],EBG[i]);

//   time(&t);
//   fprintf(pFl,"\nBeg %s",ctime(&t));

       memset(NumElemBody,0,kG*sizeof(long));
       LookCross = GetPrivateProfileInt("SCHEMA","LookCross",0,GetPath(hINST,"scad.ini"));
       Num = (long*)Memory(kG+1,sizeof(long));

       while ( 1 && kG ) {

          if ( kGr <= kGm )  break;
//          if ( Progress(90*(kG-kGr)/kG+6) == TRUE ) {   DeleteLookBody();  return;    }

           for ( i=0,ki=0; i<kG; i++ )
              if ( NumElemBody[i] == 0 ) Num[ki++] = i;

           if ( LookInto(ki,Num,kGr,kGm,EB,EBG,LookCoord,Eps,NumElemBody) == 0  ) {
              if ( LookCross == 1 ) {
                 for ( i=0,j=0; i<kG; i++ )
                    if ( NumElemBody[i] < j ) j = NumElemBody[i];
                 for ( i=0; i<kG; i++ )
                    if ( NumElemBody[i] == j ) NumElemBody[i] = ++kGm;
                 }
              if ( LookCross == 2 ) {
                 for ( i=0,j=-kG; i<kG; i++ )
                    if ( NumElemBody[i] > j && NumElemBody[i] < 0 ) j = NumElemBody[i];
                 for ( i=0; i<kG; i++ )
                    if ( NumElemBody[i] == j ) NumElemBody[i] = kGr--;
                 }
              else {
                 rMin = 1e35;  rMax = 0;
                 for ( i=0; i<kG; i++ ) {
                    if ( NumElemBody[i] > 0 ) continue;
                    pEBGI = &EBG[i];
                    if ( rMin >= pEBGI->yMin )  {
                       if ( rMin == pEBGI->yMin && pEBGI->yMax >= rMax ) continue;
                       rMin = pEBGI->yMin; rMax = pEBGI->yMax;  n = i;   }
                       }
                 NumElemBody[n] = kGr--;  }
             }
          for ( n=0; n<ki; n++ ) {  i = Num[n];
             if ( NumElemBody[i] < 0 || NumElemBody[i] > kG ) NumElemBody[i] = 0;
             }

	       }

       MemoryFree(EBG);
       MemoryFree(Num);

}