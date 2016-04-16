//////////////////////////////////////////////////////////////////////
//
// SC3DMatrix.cxx: implementation of the SC3DMatrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SC3DMatrix.hxx"
#include <D3dx8math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SC3DMatrix::SC3DMatrix() 
{ 
	 Identity();
}

SC3DMatrix::SC3DMatrix( const SC3DMatrix& mtr )
{
	*this = mtr;
}

SC3DMatrix::SC3DMatrix( LPCSCDOUBLE32 pElements )
{
	if( !pElements )
		Identity();
	else
		memcpy( m_fElements, pElements, sizeof( m_fElements ) );
}

SC3DMatrix& SC3DMatrix::operator=( const SC3DMatrix& mtr )
{
	memcpy( m_fElements, mtr.m_fElements, sizeof( m_fElements ) );
	return *this;
}

SC3DMatrix::operator LPSCDOUBLE32() const
{
	return (LPSCDOUBLE32)m_fElements;
}

SC3DMatrix SC3DMatrix::operator*( const SC3DMatrix& mtr ) const
{
	SC3DMatrix mtrRes;

	D3DXMatrixMultiply( (D3DXMATRIX*)mtrRes.m_fElements, (D3DXMATRIX*)m_fElements, (D3DXMATRIX*)mtr.m_fElements );
	
	return mtrRes;
}

SC3DMatrix& SC3DMatrix::operator*=( const SC3DMatrix& mtr )
{
	D3DXMatrixMultiply( (D3DXMATRIX*)m_fElements, (D3DXMATRIX*)m_fElements, (D3DXMATRIX*)mtr.m_fElements );

	return *this;
}

SC3DRetCode SC3DMatrix::Identity()
{
	D3DXMatrixIdentity( (D3DXMATRIX*)m_fElements );

	return S3DRC_OK;
}

SC3DRetCode SC3DMatrix::Inversing()
{
	if( !D3DXMatrixInverse( (D3DXMATRIX*)m_fElements, NULL, (D3DXMATRIX*)m_fElements ) )
		return S3DRC_ERR_MTR_DONT_INVERSE;

	return S3DRC_OK;
}

SC3DRetCode SC3DMatrix::Inversing( const SC3DMatrix& mtr )
{
	if( !D3DXMatrixInverse( (D3DXMATRIX*)m_fElements, NULL, (D3DXMATRIX*)mtr.m_fElements ) )
		return S3DRC_ERR_MTR_DONT_INVERSE;

	return S3DRC_OK;
}

SCDOUBLE32 SC3DMatrix::Determinant()
{
	return D3DXMatrixfDeterminant( (D3DXMATRIX*)m_fElements );
}

SC3DRetCode SC3DMatrix::SetPos( const SC3DPoint& pos )
{
	m_fElements[3][0] = pos.m_fX;
	m_fElements[3][1] = pos.m_fY;
	m_fElements[3][2] = pos.m_fZ;

	return S3DRC_OK;
}

SC3DRetCode SC3DMatrix::Move( const SC3DPoint& dist )
{
	m_fElements[3][0] += dist.m_fX;
	m_fElements[3][1] += dist.m_fY;
	m_fElements[3][2] += dist.m_fZ;

	return S3DRC_OK;
}

SC3DRetCode SC3DMatrix::RotateX( const SC3DPoint& center, SCDOUBLE32 fAngleX )
{
	SC3DMatrix mtr;
	D3DXQUATERNION qR;
	D3DXVECTOR3 d3d_center( center.m_fX, center.m_fY, center.m_fZ );
    
	D3DXQuaternionRotationYawPitchRoll( &qR, fAngleX, 0.0f, 0.0f );
	D3DXMatrixAffineTransformation( (D3DXMATRIX*)mtr.m_fElements, 1.f, &d3d_center, &qR, NULL );
	*this *= mtr;

	return S3DRC_OK;
}

SC3DRetCode SC3DMatrix::RotateY( const SC3DPoint& center, SCDOUBLE32 fAngleY )
{
	SC3DMatrix mtr;
	D3DXQUATERNION qR;
	D3DXVECTOR3 d3d_center( center.m_fX, center.m_fY, center.m_fZ );
    
	D3DXQuaternionRotationYawPitchRoll( &qR, 0.0f, fAngleY, 0.0f );
	D3DXMatrixAffineTransformation( (D3DXMATRIX*)mtr.m_fElements, 1.f, &d3d_center, &qR, NULL );
	*this *= mtr;

	return S3DRC_OK;
}

SC3DRetCode SC3DMatrix::RotateZ( const SC3DPoint& center, SCDOUBLE32 fAngleZ )
{
	SC3DMatrix mtr;
	D3DXQUATERNION qR;
	D3DXVECTOR3 d3d_center( center.m_fX, center.m_fY, center.m_fZ );
    
	D3DXQuaternionRotationYawPitchRoll( &qR, 0.0f, 0.0f, fAngleZ );
	D3DXMatrixAffineTransformation( (D3DXMATRIX*)mtr.m_fElements, 1.f, &d3d_center, &qR, NULL );
	*this *= mtr;

	return S3DRC_OK;
}

SC3DRetCode SC3DMatrix::ScaleXYZ( SCDOUBLE32 fScale )
{
	D3DXMatrixScaling( (D3DXMATRIX*)m_fElements, fScale, fScale, fScale );

	return S3DRC_OK;
}

SC3DRetCode SC3DMatrix::LookAt( const SC3DPoint& ptFrom, const SC3DPoint& ptTo, const SC3DPoint& ptUp )
{
	D3DXVECTOR3 from( ptFrom.m_fX, ptFrom.m_fY, ptFrom.m_fZ );
	D3DXVECTOR3 to( ptTo.m_fX, ptTo.m_fY, ptTo.m_fZ );
	D3DXVECTOR3 up( ptUp.m_fX, ptUp.m_fY, ptUp.m_fZ );

	D3DXMatrixLookAtRH( (D3DXMATRIX*)m_fElements, &from, &to, &up );

	return S3DRC_OK;
}

SC3DRetCode SC3DMatrix::PrjOrto( SCDOUBLE32 fMinX, SCDOUBLE32 fMaxX, SCDOUBLE32 fMinY, SCDOUBLE32 fMaxY, SCDOUBLE32 fMinZ, SCDOUBLE32 fMaxZ )
{
	D3DXMatrixOrthoOffCenterRH( (D3DXMATRIX*)m_fElements, 
									fMinX, fMaxX, 
									fMinY, fMaxY, 
									fMinZ, fMaxZ );

	return S3DRC_OK;
}

SC3DRetCode SC3DMatrix::PrjPerspective( SCDOUBLE32 fMinX, SCDOUBLE32 fMaxX, SCDOUBLE32 fMinY, SCDOUBLE32 fMaxY, SCDOUBLE32 fMinZ, SCDOUBLE32 fMaxZ )
{
	D3DXMatrixPerspectiveOffCenterRH( (D3DXMATRIX*)m_fElements, 
										fMinX, fMaxX, 
										fMinY, fMaxY, 
										fMinZ, fMaxZ );

	return S3DRC_OK;
}
	
SCAD3DMODEL_API SC3DPoint operator*( const SC3DPoint& pt, const SC3DMatrix& mtr )
{
	SC3DPoint ptRes;

	ptRes.m_fX = pt.m_fX * mtr.m_fElements[0][0] + pt.m_fY * mtr.m_fElements[0][1] + pt.m_fZ * mtr.m_fElements[0][2] + mtr.m_fElements[0][3];
	ptRes.m_fY = pt.m_fX * mtr.m_fElements[1][0] + pt.m_fY * mtr.m_fElements[1][1] + pt.m_fZ * mtr.m_fElements[1][2] + mtr.m_fElements[1][3];
	ptRes.m_fZ = pt.m_fX * mtr.m_fElements[2][0] + pt.m_fY * mtr.m_fElements[2][1] + pt.m_fZ * mtr.m_fElements[2][2] + mtr.m_fElements[2][3];

	return ptRes;
}

SCAD3DMODEL_API SC3DCube operator*( const SC3DCube& cube, const SC3DMatrix& mtr )
{
	SC3DCube cbRes;
	int i;
	SC3DPoint vertexes[8] = 
	{
		SC3DPoint( cube.m_fMinX, cube.m_fMinY, cube.m_fMinZ ),
		SC3DPoint( cube.m_fMinX, cube.m_fMinY, cube.m_fMaxZ ),
		SC3DPoint( cube.m_fMinX, cube.m_fMaxY, cube.m_fMinZ ),
		SC3DPoint( cube.m_fMinX, cube.m_fMaxY, cube.m_fMaxZ ),
		SC3DPoint( cube.m_fMaxX, cube.m_fMinY, cube.m_fMinZ ),
		SC3DPoint( cube.m_fMaxX, cube.m_fMinY, cube.m_fMaxZ ),
		SC3DPoint( cube.m_fMaxX, cube.m_fMaxY, cube.m_fMinZ ),
		SC3DPoint( cube.m_fMaxX, cube.m_fMaxY, cube.m_fMaxZ ),
	};

	for( i = 0; i < 8; i++ )
		vertexes[i] = vertexes[i] * mtr;
	for( i = 0; i < 8; i++ )
	{
		if( cbRes.m_fMaxX == FLT_MAX || cbRes.m_fMaxX < vertexes[i].m_fX )
			cbRes.m_fMaxX = vertexes[i].m_fX;
		if( cbRes.m_fMinX == FLT_MAX || cbRes.m_fMinX > vertexes[i].m_fX )
			cbRes.m_fMinX = vertexes[i].m_fX;
		if( cbRes.m_fMaxY == FLT_MAX || cbRes.m_fMaxY < vertexes[i].m_fY )
			cbRes.m_fMaxY = vertexes[i].m_fY;
		if( cbRes.m_fMinY == FLT_MAX || cbRes.m_fMinY > vertexes[i].m_fY )
			cbRes.m_fMinY = vertexes[i].m_fY;
		if( cbRes.m_fMaxZ == FLT_MAX || cbRes.m_fMaxZ < vertexes[i].m_fZ )
			cbRes.m_fMaxZ = vertexes[i].m_fZ;
		if( cbRes.m_fMinZ == FLT_MAX || cbRes.m_fMinZ > vertexes[i].m_fZ )
			cbRes.m_fMinZ = vertexes[i].m_fZ;
	}

	return cbRes;
}
