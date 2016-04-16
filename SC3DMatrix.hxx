//////////////////////////////////////////////////////////////////////
//
// SC3DMatrix.hxx: interface for the SC3DMatrix class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SC3DMatrix_hxx__
#define SC3DMatrix_hxx__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "SCAD3DModelDef.hxx"
#include "SC3DRetCodes.hxx"
#include "SC3DPoint.h"


#pragma	pack(push,1)

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
typedef  const float*          LPCSCDOUBLE32;
typedef  float*          LPSCDOUBLE32;


class SC3DMatrix
{
public:
	SC3DMatrix();
    SC3DMatrix( const SC3DMatrix& mtr );
    SC3DMatrix( LPCSCDOUBLE32 pElements );

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DMatrix&	operator =	( const SC3DMatrix& mtr );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	operator LPSCDOUBLE32	() const;

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DMatrix	operator *	( const SC3DMatrix& mtr ) const;
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DMatrix&	operator *=	( const SC3DMatrix& mtr );
	
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	Identity	();
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	Inversing	();
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	Inversing	( const SC3DMatrix& mtr );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SCDOUBLE32	Determinant	();

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	SetPos		( const SC3DPoint& pos );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	Move		( const SC3DPoint& dist );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	RotateX		( const SC3DPoint& center, SCDOUBLE32 fAngleX );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	RotateY		( const SC3DPoint& center, SCDOUBLE32 fAngleY );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	RotateZ		( const SC3DPoint& center, SCDOUBLE32 fAngleZ );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	ScaleXYZ	( SCDOUBLE32 fScale );

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	LookAt		( const SC3DPoint& ptFrom, const SC3DPoint& ptTo, const SC3DPoint& ptUp );

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	PrjOrto			( SCDOUBLE32 fMinX, SCDOUBLE32 fMaxX, SCDOUBLE32 fMinY, SCDOUBLE32 fMaxY, SCDOUBLE32 fMinZ, SCDOUBLE32 fMaxZ );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DRetCode	PrjPerspective	( SCDOUBLE32 fMinX, SCDOUBLE32 fMaxX, SCDOUBLE32 fMinY, SCDOUBLE32 fMaxY, SCDOUBLE32 fMinZ, SCDOUBLE32 fMaxZ );
	
	SCDOUBLE32	m_fElements[4][4];
};

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
SCAD3DMODEL_API SC3DPoint operator*( const SC3DPoint& pt, const SC3DMatrix& mtr );
/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
SCAD3DMODEL_API SC3DCube operator*( const SC3DCube& cube, const SC3DMatrix& mtr );


#pragma	pack(pop)


#endif //SC3DMatrix_hxx__
