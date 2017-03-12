#ifndef RESULT_FLAG_H
#define RESULT_FLAG_H
#pragma pack(push,1)

#ifdef  RESULT_EXPORTS
#define RESULT_EXPORT __declspec(dllexport)
#else
#define RESULT_EXPORT __declspec(dllimport)
#endif

#include <schema.hpp>
#include <fe_form.h>
#include <s_rsu.h>
#include <calcdata.h>
#include "sg_dyn1.h"
#include "s_stabil.h"
#include "tablload.h"
#include "fe_head.h"
//#include "amplitud.h"

/*
Тип информации в таблице загружений:

	0 - перемещения и усили
	1 - РСН, перемещения и усили
       11 - динамика, перемещени
       12 - устойчивость
       13 - устойчивость от РСН
       21 - динамика, массы
       22 - динамика, инерционные силы
*/

#define MAX_QUANTYTI_TYPE_NUR   50
#define MAX_QUANTYTI_TYPE_NUS  100
#define KOL_SECTION             30

struct RESULT_ELEM  {
	   char     Nus[8];
	   BYTE     QuantityEffors;
	   BYTE     QuantityPoint;
	   double * CoordPoint;
	   double * DataPoint;
	   };

class RESULT : public MEMORY  {

public:
	   SCHEMA            * SchemaData;

       CALC_DATA           CalcData;
       FORMAT_POSITION   * FormPosRes;

       LOAD_CALC   * LoadCalc;
	   LPSTR         IZ;
       FE_DATA       DataFE;

       FE_FORMAT   * FormElem;
       FE_COORD    * ckwf;
	   double      * emwf;
	   long        * mgwf;
	   FE_FORCE    * mqwf;
       char          SumNus[8];

	   UNITS         UnitsOut[5];
	   double        UnitsCoefDispl[16];
	   double        UnitsCoefReak[16];
	   double        UnitsCoefEffors[64];

	   RSN_STR     * LoadCombination;
	   RSN_STR       LoadCombinationOne;

	   WORD          QuantityLoad;
	   WORD          QuantityStrTableLoad;
	   WORD          QuantityStrTableDisplace;
	   WORD          QuantityStrTableEffors;
	   TABLE_LOAD  * TableLoad;

       long        * NumStep;

	   WORD          NumStrTableLoad;
	   BYTE          YesDisplaceElem;
	   BYTE          YesEfforsElem;
	   short         NumLayer;
	   BYTE          TypeLayer;

       HEAD_USIL     HeadUsil;
	   WORD          MaxFENode;

       double      * ForceValue;
       double      * Displace;
	   double      * DisplaceNode;
	   RESULT_ELEM * ResultElem;
	   WORD          QuantityPoint;
	   double        CoordPoint[6*KOL_SECTION+1];
	   double        DataPoint[3*KOL_SECTION+3];

	   BYTE          TypeSystemCoordEffors;  /*  0 - не пpеобpазовывать                   */
						 /*  1 - пpеобpазовывать в декаpтовую систему */
						 /*  2 -    цилиндpическую                    */
						 /*  3 -    сфеpическую                       */
	   double        EfforsSystemCoord[2][3];/*    оpты, пpоекции котоpыx опpеделяют ось x1      */

public:
       FILEWORK      Form;

       FILEWORK      FileDisplace;
       FILEWORK      FileEffors;
       FILEWORK      FileEfforsComb;
       FILEWORK      FileDynamic;
       FILEWORK      FileStabil;
       FILEWORK      FileStep;

       FILEWORK      FileDisplaceComb;
       FILEWORK      FileStabilComb;

       HEAD_STABIL   HeadStabil;
       HEAD_STABIL   HeadStabilComb;

       BYTE          QuantityTypeEffors;

	   double        OutData[64];
	   sg_dyn1       StrDyn;
	   s_stabil      StrStab;

	   BYTE          TypeEffors;
	   double      * EfforsFull;

	   FORMAT_UNITE * FormUnite;

	   int            NumStrEnergy;
	   double       * Energy;
	   char         * VolEnergy;

	   BOOL     (*Progress) (int);

       char           End;

public:

	    RESULT()  {   ZeroMemory(&SchemaData,&End-(LPSTR)&SchemaData);  }
	   ~RESULT()  {   Delete();  }

RESULT_EXPORT  int    Init( SCHEMA &Schm, UNITS *UnOut, BOOL Func(int) );
RESULT_EXPORT  void   Delete();
void           DeleteResultElem( int NumElem);
void           DeleteResultElem();
void           DeleteResult();

inline CALC_DATA       * GetCalcData()  {   return &CalcData;  }
inline FORMAT_POSITION * GetFormatPosition() {   return FormPosRes;  }

//inline int  GetYesCombinationDisplace() {   return Ctg.YesDisplaceComb;  }
//inline int  GetYesCombinationEffors()   {   return Ctg.RSN;  }
inline int  GetQuantityLoad()           {   return QuantityLoad;  }

RESULT_EXPORT  int     GetQuantityForm( int Num);
RESULT_EXPORT  void    SetUnitsOut(UNITS Un[]);

RESULT_EXPORT  int     GetDisplace( WORD NumStr, BYTE Type );

RESULT_EXPORT  int     GetLoad( WORD NumStr, int  NumLayer= -1, int  TypeLayer=0);

RESULT_EXPORT  void    NameLoadGrand( TABLE_LOAD &TL, LPSTR Text );
RESULT_EXPORT  void    NameLoadAgent( TABLE_LOAD &TL, LPSTR Text );
RESULT_EXPORT  void    NameStrTableLoadG( TABLE_LOAD &TL, char Text[] );
RESULT_EXPORT  void    ReadLoadBuf( TABLE_LOAD &TL );

RESULT_EXPORT  int     GetFormat( TABLE_LOAD *pTL, int NumElem );

private:

int        WorkDisplaceElem();
double *   GetDisplaceNodeIn( int NumNode, BYTE TypeUnits = 1 );
void       GetDisplace(WORD Quantity, long ListStep[], double Per[] );
void       RodDisplace( double per[] );
void       RodDisplaceForce( double rmk1[3][3], double rmk2[], double *xyz, short ix,double xi[] );

void       ReadEffors( LONGLONG &Pos, double * Ef);
void       ReadEfforsLayer( LONGLONG &Pos, double * Ef);

void       RodPoint( double *Coord, WORD &QnttX );

void       RodDisplaceNode( double Dsplc[], double pl[12][6][4], double  nul[2],
		      double  rmk1[3][3], double  rmk2[3][3], double sw[6] );

public:

RESULT_EXPORT  double *  GetDisplaceNode( WORD NumStr, int NumNode, BYTE TypeUnits = 1  );
RESULT_EXPORT  double *  GetMassaNode( WORD NumStr, int NumNode, BYTE TypeUnits = 1  );
RESULT_EXPORT  double *  GetFullDisplaceNode( int NumNode, BYTE *MaskLoad, BYTE Type );
RESULT_EXPORT  void      GetDisplaceElem( WORD NumStr, int NumElem,
		WORD & QuantityPoint, double **Coord, double **Disp );

RESULT_EXPORT  void      SetSystemCoordEffors(BYTE Type, double X[2][3]);
RESULT_EXPORT  void      GetSystemCoordEffors( BYTE &Type, double X[2][3]);

RESULT_EXPORT  LPCSTR    GetNameLoadDisplace(WORD Num);
RESULT_EXPORT  LPCSTR    GetNameLoadEffors(WORD Num);
RESULT_EXPORT  LPCSTR    GetNameLoadResult(WORD Num, BYTE Type);

RESULT_EXPORT  TABLE_LOAD *   GetLoadTableDisplace(WORD Npr);
RESULT_EXPORT  TABLE_LOAD *   GetLoadTableEffors(WORD Npr);
RESULT_EXPORT  TABLE_LOAD *   GetStrTableLoad(WORD Npr, BYTE Type, WORD &NumStr);

RESULT_EXPORT  void      ForceInRes( BYTE Type, BYTE YesNode, BYTE YesFE, int NumNagr, double *Force, double Coef, int TypeLoad );

inline int    GetQuantityStrTableDisplace() {  return QuantityStrTableDisplace;  };
inline int    GetQuantityStrTableEffors()   {  return QuantityStrTableEffors;  };

inline char * GetTypeEffors () { return SumNus;  }
inline WORD   GetQuantityTypeEffors () { return QuantityTypeEffors;  }

inline RESULT_ELEM * GetResultElem( int NumElem) {  return &ResultElem[NumElem-1];  };

RESULT_EXPORT  void     GetEfforsElem( WORD NumStr, int NumElem,
			WORD NumUs,  WORD & QuantityPoint,
			LPSTR  * NusElem, double **Coord,  double **Effors );
RESULT_EXPORT  void     GetEfforsFlat( int NumStr, int NumFlat,
			WORD NumUs,  WORD & QuantityPoint,
			LPSTR  * NusElem, double **Coord,  double **Effors );
RESULT_EXPORT  double  *  GetEfforsElem( BYTE TypeE, int &NumElem, WORD &TypeElem,
	     WORD &QuantityEffors, BYTE NUS[8], WORD & QuantityPoint );

inline int  GetQuantityDynamicLoad() { return CalcData.QuantityLoadDyn; }
RESULT_EXPORT  double  *  GetMassNode( int NumNode, BYTE *MaskLoad );
RESULT_EXPORT  double  *  GetForceDynamicNode( int NumNode);

inline  void * This() {  return this; }
inline  SCHEMA * GetSchema() {  return SchemaData; }

RESULT_EXPORT  void    EndEfforsElem();

RESULT_EXPORT  void    SetFileMark(FILEWORK &, int Num );

RESULT_EXPORT  int     EfforsPlate();

RESULT_EXPORT  void    EnergyElem( int NumStrTbl, double Energy[], BYTE *YesVol=NULL );
RESULT_EXPORT  void    GetEfforsLiteraElem( int NumElem, int Type, RESULT_ELEM *pRE, int NumTeoty, double Const[], LIT_WORK LitWork[] );

RESULT_EXPORT  void    Amplitude(void * /* AMPLITUDE &Ampl */);

	 friend class RESULT_FUND;
	 friend class RESULT_ARMATUR;
	 friend class AGENT;

};

void RESULT_EXPORT SumEffors( int NPR, int  KF, int KN, 
							  double *Chast, double *US, double *USR, 
							  WORD IS,  WORD INR, int *KST );

#pragma pack(pop)
#endif
