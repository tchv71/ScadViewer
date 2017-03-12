#ifndef DATA_RIGID_PLATE_FLAG_H
#define DATA_RIGID_PLATE_FLAG_H
#pragma pack(push,1)

#include <schema.hpp>
#include <rgd_pl.hpp>

class DATA_RIGID_PLATE : MEMORY {

      SCHEMA        * Schem;
      DATA_RIGID    * SchemaRigid;
      IDENTIFICATOR   Ident;

public:

      char            Name[512];
      int             NumRgd;

      BYTE            TypeConstr;    //  '','P','B','D'   PD
      BYTE            TypeMaterial;  //  '','I','O','A'


      double          e1;
      double          e2;
      double          nu12;
      double          nu21;
      double          g12;
      double          etaxy1;
      double          etaxy2;
      double          eta1xy;
      double          eta2xy;

      double          delta;
      double          ro;

      BYTE            TypeMaterialZ;  //  '','I','O','A'

      EPD             Epd;

      D3SL            Lauer;

      double          dz;
      double          dlk;
      double          GibridCoef;
      BYTE            GibridStepB;
      BYTE            GibridStepP;

      double          tmpalx;
      double          tmpaly;

      double          nx;
      double          ny;
      double          nxy;

      double          Res[100];
	  int             QuantityHole; 
	  int           * ListHole; 

      ELAST_LAYER     Lauers[50];

      double          End;

  	DATA_RIGID_PLATE()      {  Init();    }
  ~DATA_RIGID_PLATE(void)  {  Delete();  }

void  SCHEMA_EXPORT  Init();
void  SCHEMA_EXPORT  Delete();
void  SCHEMA_EXPORT  Destroy();

void  SCHEMA_EXPORT  SetPointer( SCHEMA &, DATA_RIGID & );

void  SCHEMA_EXPORT  SetHole( int NumList,  int ListNode[] );

void  SCHEMA_EXPORT  Get( int NumRgd );

int   SCHEMA_EXPORT  Set( int Num=0);
void  SCHEMA_EXPORT  SetIn();

};


#pragma pack(pop)
#endif
