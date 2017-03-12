#ifndef DATA_RIGID_VOLUME_FLAG_H
#define DATA_RIGID_VOLUME_FLAG_H
#pragma pack(push,1)

#include <schema.hpp>
#include <rgd_pl.hpp>

class DATA_RIGID_VOLUME : MEMORY {

      SCHEMA        * Schem;
      DATA_RIGID    * SchemaRigid;
      IDENTIFICATOR   Ident;

public:

        char            Name[512];
        int             NumRgd;

        BYTE            TypeConstr;    //  '','P','B','D'   PD
        BYTE            TypeMaterial;  //  '','I','O','A'

        WORD            QuantityPointInt;

		  double e1;        /* MOƒ”À‹ ﬁH√A œO HAœP. OC» "X"    */
		  double e2;        /* MOƒ”À‹ ﬁH√A œO HAœP. OC» "Y"    */
		  double e3;        /* MOƒ”À‹ ﬁH√A œO HAœP. OC» "Z"    */
		  double nu12;      /* KO›‘. œ”ACCOHA "XY"             */
		  double nu21;      /* KO›‘. œ”ACCOHA "XZ"             */
		  double nu13;      /* KO›‘. œ”ACCOHA "YX"             */
		  double nu31;      /* KO›‘. œ”ACCOHA "YZ"             */
		  double nu23;      /* KO›‘. œ”ACCOHA "ZX"             */
		  double nu32;      /* KO›‘. œ”ACCOHA "ZY"             */
		  double g1;        /* MOƒ”À‹ CƒB»√A B OCﬂX "XY"       */
		  double g2;        /* MOƒ”À‹ CƒB»√A B OCﬂX "XZ"       */
		  double g3;        /* MOƒ”À‹ CƒB»√A B OCﬂX "YZ"       */

        double          ro;
        double          dlk;

        double          GibridCoef;

        double          tmpalx;
        double          tmpaly;
        double          tmpalz;

        double          Res[100];
        double          End;

  	DATA_RIGID_VOLUME()      {  Init();    }
  ~DATA_RIGID_VOLUME(void)  {  Delete();  }

void  SCHEMA_EXPORT  Init();
void  SCHEMA_EXPORT  Delete();
void  SCHEMA_EXPORT  Destroy();

void  SCHEMA_EXPORT  SetPointer( SCHEMA &, DATA_RIGID & );

void  SCHEMA_EXPORT  Get( int NumRgd );

int   SCHEMA_EXPORT  Set( int Num=0);
void  SCHEMA_EXPORT  SetIn();

};

#pragma pack(pop)
#endif
