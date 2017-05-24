#ifndef SCAD_SE_FLAG_H
#define SCAD_SE_FLAG_H
#pragma pack(push, 1)
#include <schema.h>

struct  SUPER_DATA {

	short          Level;              /* уровень SE в основной схеме       */
 	short          TypeError;          /* наличие и тип ошибки при стыковке */

   short          NumSchema;
   short          NumVorSE;
   short          NumElemInVorSE;
   BYTE         * NumNextSE;
   long           NumNodeBase;

	WORD           QuantityNodeSE;     /* к-во узлов SE             */
	long         * NumNodeVorSE;       /* номера узлов SE           */

	double         XA, YA, ZA;         /* привязка SE  в основной схеме      */
	double         MatrCosCoord[9];    /*                                    */

	double         MatrCosSE[9];       /* привязка SE к порождающему SE     */

	int            QuantitySE;         /* число пристыкованных суперэлементов */
	int            NumBeginSE;         /* начало в списке                     */

   long           NumBeginElem;
   long           NumBeginNode;
   long           NumStepBegin;
   long           OrderMatrize;


};

class SUPER : MEMORY
{
public:
	int             MaxLevel;
	int             QuantitySE;
	int             QuantityAllocSE;
	SUPER_DATA    * SuperData;

	int             QuantitySchema;
	int             QuantityAllocSchema;
   SCHEMA       ** Schem;

   int             QuantityLoad;
   long            QuantityNode;

   char            Catalog[MAXPATH];
   int             Error;
   int             TypeRead;

int   EXPORT  AddSuper(int);
void  EXPORT  AddSuper(SCHEMA &, SUPER_DATA &);
int   EXPORT  AddSchema(LPCSTR Name);
int   EXPORT  AddSchema(int);

public:

EXPORT	SUPER()     {   Init();    }
EXPORT ~SUPER(void) {   Delete();  }

void  EXPORT  Init()  {  memset(this,0,sizeof(SUPER));  };
void  EXPORT  Delete();
int   EXPORT  Init(SCHEMA &, char WorkCatalog[], int );
void  EXPORT  Init(SCHEMA &, int );

void  GetNextSE( SUPER_DATA &, SUPER_DATA &, int Num );

int   EXPORT   Access(LPCSTR filename,int NumSchem=0);
void  EXPORT   Remove(LPCSTR filename,int NumSchem=0);
LPSTR EXPORT   GetFileName(LPCSTR Extension,int NumSchem=0);
LPSTR EXPORT   GetFileName(int Num,int NumSchem=0);

};

#pragma pack(pop)
#endif
