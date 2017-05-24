#include <stdafx.h>
#include <schema.h>

double SideLength( CK *Crd,WORD NumNode1, WORD NumNode2);

int  SCHEMA::AddControl( ADD_SCHEMA_DATA &AddData, SCHEMA &AddSchm, double Beg1[3], double Beg2[3], double mk[3][3] )
{
     WORD i, n;
     double r12, r13, r23, q12, q13, q23, r, s, c, Scale,
	    ck1[3][3], ck2[3][3],
	    mk1[3][3], mk2[3][3];
     WORD TypStep1, TypStep2, TypStep;

     memset(ck1,0,sizeof(ck1));
     memset(ck2,0,sizeof(ck2));
     Scale = 1;

     for ( i=0; i<AddData.QuantityNodeDocking; i++ ) {
	if ( AddData.NumNodeDocking1[i] == 0 ||
	     AddData.NumNodeDocking1[i] > QuantityNode ||
	     AddData.NumNodeDocking2[i] == 0 ||
	     AddData.NumNodeDocking2[i] > AddSchm.QuantityNode ) return 1;
	memcpy(&ck1[i][0],&Coord[AddData.NumNodeDocking1[i]-1],3*sizeof(double));
	memcpy(&ck2[i][0],&AddSchm.Coord[AddData.NumNodeDocking2[i]-1],3*sizeof(double));
	if ( i ) for ( n=0; n<3; n++ ) {
	   ck1[i][n] -= ck1[0][n];
	   ck2[i][n] -= ck2[0][n];  }
	}

     if ( AddData.QuantityNodeDocking > 1 ) {
	r12 = SideLength(Coord,AddData.NumNodeDocking1[0],AddData.NumNodeDocking1[1]);
	q12 = SideLength(AddSchm.Coord,AddData.NumNodeDocking2[0],AddData.NumNodeDocking2[1]);
	if ( fabs(r12) < AddData.PrecesionCoincidence ||
	     fabs(q12) < AddData.PrecesionCoincidence ) return 1;
	}
     if ( AddData.QuantityNodeDocking <= 1 ) {
         if ( AddData.QuantityNodeDocking == 0 )
	         memcpy(&ck1[0][0],AddData.Punct11,3*sizeof(double));
         if ( AddData.YesDelta ) {
            n = AddData.NumNodeDocking2[0];
            if ( n == 0 || n > AddSchm.GetQuantityNode() ) return 1;
	         memcpy(&ck2[0][0],&AddSchm.Coord[n-1],3*sizeof(double));
	         }
         memset(mk,0,9*sizeof(double));
         mk[0][0] = mk[1][1] = mk[2][2] = 1;
    	 r = AddData.Corner1;
	    if ( AddData.YesCorner1 == 2 ) r *= M_PI / 180;
	    s = sin(r);  c = cos(r);
	    if ( AddData.Punct12[0] ) {
	        mk[1][1] = c;   mk[1][2] = s;
	        mk[2][1] = -s;  mk[2][2] = c;  }
	    if ( AddData.Punct12[1] ) {
	        mk[0][0] = c;   mk[0][2] = s;
	        mk[2][0] = -s;  mk[2][2] = c;  }
	    if ( AddData.Punct12[2] ) {
	        mk[0][0] = c;   mk[0][1] = s;
	        mk[1][0] = -s;  mk[1][1] = c;  }
       goto _10;   }

     if ( AddData.QuantityNodeDocking == 2 ) {
	memcpy(&ck1[2][0],AddData.Punct13,3*sizeof(double));
	memcpy(&ck2[2][0],AddData.Punct23,3*sizeof(double));
	if ( AddData.YesDelta == 0 )	for ( i=0; i<3; i++ ) {
	   ck1[2][i] -= ck1[0][i];
	   ck2[2][i] -= ck2[0][i];  }
	}

     if ( AddData.QuantityNodeDocking >= 2 ) {
	if ( AddData.YesScale == 0 && fabs(r12-q12) > AddData.PrecesionCoincidence )
	   return 1;
	if ( AddData.YesScale ) Scale = r12 / q12;
	}

     if ( AddData.QuantityNodeDocking == 2 && AddData.YesCorner1 ) {
	r = AddData.Corner1;
	if ( AddData.YesCorner1 == 2 ) r *= M_PI / 180;
	s = sin(r);  c = cos(r);
	MatrCos(s,c,(double *)ck1,(double*)mk1);
	}
     else {
	n = MatrCos((double*)ck1,(double*)mk1);
	if ( n ) return 1;  }

     if ( AddData.QuantityNodeDocking == 2 && AddData.YesCorner2 ) {
	r = AddData.Corner2;
	if ( AddData.YesCorner2 == 2 ) r *= M_PI / 180;
	s = sin(r);  c = cos(r);
	MatrCos(s,c,(double *)ck2,(double*)mk2);
	}
     else {
	n = MatrCos((double*)ck2,(double*)mk2);
	if ( n ) return 1;  }

     if ( AddData.QuantityNodeDocking == 3 ) {
	 if ( AddData.YesScale == 0 ) {
	   r13 = SideLength(Coord,AddData.NumNodeDocking1[0],AddData.NumNodeDocking1[2]);
	   q13 = SideLength(AddSchm.Coord,AddData.NumNodeDocking2[0],AddData.NumNodeDocking2[2]);
	   r23 = SideLength(Coord,AddData.NumNodeDocking1[1],AddData.NumNodeDocking1[2]);
	   q23 = SideLength(AddSchm.Coord,AddData.NumNodeDocking2[1],AddData.NumNodeDocking2[2]);
	   if ( fabs(r13-q13) > AddData.PrecesionCoincidence ||
	        fabs(r23-q23) > AddData.PrecesionCoincidence ) return 1;
	   }
         else {
            r = 1;
            if ( fabs(mk1[0][2]*mk2[0][2]) + fabs(mk1[1][2]*mk2[1][2]) +
                 fabs(mk1[2][2]*mk2[2][2]) >= 1 - AddData.PrecesionCoincidence &&
                 mk1[0][2]*mk2[0][2] + mk1[1][2]*mk2[1][2] + mk1[2][2]*mk2[2][2] < 0 )
               r = -1;
            if ( AddData.YesCorner2 ) r *= -1;
            mk2[0][1] *= r;    mk2[0][2] *= r;
            mk2[1][1] *= r;    mk2[1][2] *= r;
            mk2[2][1] *= r;    mk2[2][2] *= r;
           }
	}

     MultMatr((double*)mk2,(double*)mk1,3,3,-3,(double*)mk);

//     if ( memcmp(Units,AddSchm.Units,sizeof(Units)) ) return 2;

_10: memcpy(Beg1,ck1,3*sizeof(double));
     memcpy(Beg2,ck2,3*sizeof(double));
     for ( i=0; i<9; i++ ) mk[0][i] *= Scale;

 /*  Пpовеpка пpизнака системы                             */
     TypStep1 = TypStep2 = 0;
     for ( i=0; i<TypeSystem.QuantityStep; i++ )
	BitOn((BYTE*)&TypStep1,TypeSystem.NumStep[i]);
     for ( i=0; i<AddSchm.TypeSystem.QuantityStep; i++ )
	BitOn((BYTE*)&TypStep2,AddSchm.TypeSystem.NumStep[i]);
     TypStep = TypStep1 | TypStep2;
     if ( TypStep != TypStep1 ) {
	if ( TypStep == TypStep2 )
	   memcpy(&TypeSystem,&AddSchm.TypeSystem,sizeof(TYPE_SYSTEM));
	else return 3;  }

     return 0;

}

double SideLength( CK *Crd,WORD NumNode1, WORD NumNode2)
{
     double x, y, z;
     x = Crd[--NumNode1].x - Crd[--NumNode2].x;
     y = Crd[NumNode1].y - Crd[NumNode2].y;
     z = Crd[NumNode1].z - Crd[NumNode2].z;
     return sqrt(x*x+y*y+z*z);
}