#ifndef RESULT_ARMATUR_FLAG_H
#define RESULT_ARMATUR_FLAG_H
#pragma pack(push,1)

#include "result.hpp"
#include <beton.h>
#include <armrez.h>

#define MAX_QUANTYTI_TYPE_NUR   50
#define MAX_QUANTYTI_TYPE_NUS  100
#define KOL_SECTION             30

struct RESULT_ARM_ELEM  {
	   char    ByteArm[12];
	   BYTE    QuantityData;
	   BYTE    QuantityPoint;
	   double * CoordPoint;
	   double * DataPoint;
	   };

class RESULT_ARMATUR : public MEMORY  {

public:
	   SCHEMA             * SchemaData;

	   int                  QuantityElem;
	   int                  QuantityGroup;
       int                * NumElem;

       ArmEl              * ArmPos;
       ArmInd             * ArmIndex;

	   int                  NumGroup;
	   BYTE                 YesDouble;
	   BYTE                 ReadDouble;
	   BYTE                 ReadSnip;

	   int                  MaxFENode;

	   RESULT_ARM_ELEM    * ResultElem;
	   WORD                 QuantityPoint;
	   double               CoordPoint[KOL_SECTION+1];
	   double               DataPoint[3*KOL_SECTION+3];
public:
       FILEWORK             FileArm;
private:
	   BYTE                 QuantityTypeData;
	   char                 SumByteArm[12];

	   double               OutData[96];
	   double               ArmStep;
	   
	   double               End;

public:

	   RESULT_ARMATUR()  {   ZeroMemory(&SchemaData,(LPSTR)&End-(LPSTR)&SchemaData);  }
	  ~RESULT_ARMATUR()  {   Delete();  }

RESULT_EXPORT  int       Init( SCHEMA &Schm );
RESULT_EXPORT  void      Delete();

private:
void               DeleteResultElem( int NumElem);
void               DeleteResultElem();

public:

RESULT_EXPORT void  GetArmElem( int NumGrp, int NumElem, int NumArm, int & QuantityPoint,
		 double ** Coord, double ** Armatur );

inline int GetDouble() {  return YesDouble;  }
inline int GetQuantityGroup() {  return QuantityGroup;  }

RESULT_EXPORT LPCSTR      GetGroupName( int NumGp );
RESULT_EXPORT int         YesElemGroup(int Num);

RESULT_EXPORT BYTE *      GetSumArm( int NumGr);

RESULT_EXPORT void        ChangeStep(double r);

private:

int   GetGroup( int NumGp );

void  RESULT_ARMATUR::PlateArmatur( T_GRA_REP *pTGR, T_GRA *pG,
		 BYTE *Flag, int &Qntt, double Out[] );
void  RESULT_ARMATUR::RodArmatur( T_GRA_REP *pTGR, T_GRA *pG,
		 BYTE *Flag, int &Qntt, double Out[], BYTE YesTr );
};

#pragma pack(pop)
#endif
