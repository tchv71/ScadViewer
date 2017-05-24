#include <stdafx.h>
#include <schema.h>

EXPORT void  SCHEMA::SetTypeOptimization(BYTE Num)
{
      if ( Param.TypeOptimization != Num ) ModifyCalc = 1;
      if ( Num <= 5 ) Param.TypeOptimization = Num;
};

EXPORT BYTE SCHEMA::GetTypeOptimization() {    return Param.TypeOptimization;  }

EXPORT void  SCHEMA::SetPrecessionGauss(BYTE Prec)
{
      if ( Param.PrecessionGauss != Prec ) ModifyCalc = 1;
      if ( Prec <= 15 ) Param.PrecessionGauss = Prec;
      else Param.PrecessionGauss = 15;
      if ( Prec == 0  ) Param.PrecessionGauss = 6;
      if ( Prec < 2   ) Param.PrecessionGauss = 2;
};

EXPORT BYTE SCHEMA::GetPrecessionGauss() {    return Param.PrecessionGauss;  }

EXPORT void  SCHEMA::SetPrecessionDynamic(BYTE Prec)
{
      if ( Param.PrecessionDynamic != Prec ) ModifyCalc = 1;
      if ( Prec <= 6 ) Param.PrecessionDynamic = Prec;
      else Param.PrecessionDynamic = 6;
      if ( Prec == 0  ) Param.PrecessionDynamic = 4;
      if ( Prec < 2   ) Param.PrecessionDynamic = 2;
};

EXPORT BYTE SCHEMA::GetPrecessionDynamic() {    return Param.PrecessionDynamic;  }

EXPORT void SCHEMA::SetPrecessionDockingSE(BYTE Prec)
{
      if ( Param.PrecessionDockingSE != Prec ) ModifyCalc = 1;
      if ( Prec <= 6 ) Param.PrecessionDockingSE = Prec;
      else Param.PrecessionDockingSE = 6;
      if ( Prec == 0  ) Param.PrecessionDockingSE = 4;
      if ( Prec < 2   ) Param.PrecessionDockingSE = 2;
};

EXPORT BYTE SCHEMA::GetPrecessionDockingSE() {    return Param.PrecessionDockingSE;  }

EXPORT void SCHEMA::SetCheckSolution(BYTE Yes)
{
      if ( Param.CheckSolution != Yes ) ModifyCalc = 1;
      Param.CheckSolution = Yes;
};

EXPORT BYTE SCHEMA::GetCheckSolution() {    return Param.CheckSolution;  }

EXPORT void  SCHEMA::SetQuantityIter(WORD Prec)
{
      if ( Param.QuantityIter != Prec ) ModifyCalc = 1;
      Param.QuantityIter = Prec;
      if ( Prec == 0  ) Param.QuantityIter = 30;
      if ( Prec < 2   ) Param.QuantityIter = 2;
};

EXPORT BYTE SCHEMA::GetQuantityIter() {    return Param.QuantityIter;  }

EXPORT void SCHEMA::SetAngleSchema(float uX,float uZ)
{
      if ( Param.AngleX != uX || Param.AngleZ != uZ ) ModifyCalc = 1;
      Param.AngleX = uX;  Param.AngleZ = uZ;
};

EXPORT void SCHEMA::GetAngleSchema( float &uX, float &uZ )
{
      uX = Param.AngleX;  uZ = Param.AngleZ;
}

EXPORT void SCHEMA::SetUnitsOut( UNITS *Un )
{
      if ( memcmp(Un,Param.UnitsOut,sizeof(Param.UnitsOut)) ) ModifyCalc = 1;
      else memcpy(Param.UnitsOut,Un,sizeof(Param.UnitsOut));
}

EXPORT void SCHEMA::GetUnitsOut( UNITS *Un )
{
      memcpy(Un,Param.UnitsOut,sizeof(Param.UnitsOut));
}