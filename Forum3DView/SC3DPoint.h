//////////////////////////////////////////////////////////////////////
//
// SC3DPoint.hxx: interface for the SC3DPoint class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SC3DPoint_hxx__
#define SC3DPoint_hxx__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include <float.h>

//#include "SCADBaseTypes.hxx"
//#include "SCADConstants.hxx"
//#include "SCADBaseVectors.hxx"
//#include "SCAD3DModelDef.hxx"
#include <vector>
#include <afx.h>
typedef bool SCBOOL;
typedef float SCDOUBLE32;

//#pragma	pack(push,1)

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
inline SCBOOL SCFloatEq( SCDOUBLE32 f1, SCDOUBLE32 f2, SCDOUBLE32 fDelta = 0.0f )
{
	return fabs( f1 - f2 ) <= fDelta ? TRUE : FALSE;
}
/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
#define SCAD3DMODEL_API

class SCAD3DMODEL_API SC3DPoint
{
public:
	SC3DPoint() { m_fX = m_fY = m_fZ = 0.0f; }
	SC3DPoint( SCDOUBLE32 x, SCDOUBLE32 y, SCDOUBLE32 z ) { m_fX = x; m_fY = y; m_fZ = z; }
	SC3DPoint( const SC3DPoint& pt ) { *this = pt; }

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DPoint&	operator =	( const SC3DPoint& pt );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DPoint&	operator +=	( const SC3DPoint& pt );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DPoint&	operator -=	( const SC3DPoint& pt );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DPoint&	operator *=	( float f );
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	bool		operator ==	( const SC3DPoint& pt ) const;
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	bool		operator !=	( const SC3DPoint& pt ) const;
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	bool		operator <	( const SC3DPoint& pt ) const;

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DPoint	operator +	( const SC3DPoint& pt ) const;
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DPoint	operator -	( const SC3DPoint& pt ) const;

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DPoint	operator *	( float f ) const;

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	void		Set			( SCDOUBLE32 x, SCDOUBLE32 y, SCDOUBLE32 z ) { m_fX = x; m_fY = y; m_fZ = z; }
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	void		Normalize	();

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SCBOOL		Equal		( const SC3DPoint& pt, SCDOUBLE32 fDelta = 0.0f ) const;
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SCBOOL		EqualDirect	( const SC3DPoint& pt, SCDOUBLE32 fDelta = 0.0f ) const;
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SCDOUBLE32	AbsValue	() const;
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SCDOUBLE32	DotProduct	( const SC3DPoint& pt ) const;
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DPoint	CrossProduct( const SC3DPoint& pt ) const;


	SCDOUBLE32	m_fX;
	SCDOUBLE32	m_fY;
	SCDOUBLE32	m_fZ;
};

inline SC3DPoint& SC3DPoint::operator=( const SC3DPoint& pt )
{ 
	m_fX = pt.m_fX; 
	m_fY = pt.m_fY; 
	m_fZ = pt.m_fZ; 
	
	return *this;
}

inline SC3DPoint& SC3DPoint::operator+=( const SC3DPoint& pt )
{
	m_fX += pt.m_fX; 
	m_fY += pt.m_fY; 
	m_fZ += pt.m_fZ; 
	
	return *this;
}

inline SC3DPoint& SC3DPoint::operator-=( const SC3DPoint& pt )
{
	m_fX -= pt.m_fX; 
	m_fY -= pt.m_fY; 
	m_fZ -= pt.m_fZ; 
	
	return *this;
}

inline SC3DPoint& SC3DPoint::operator*=( float f )
{
	m_fX *= f; 
	m_fY *= f; 
	m_fZ *= f; 
	
	return *this;
}

inline bool SC3DPoint::operator==( const SC3DPoint& pt ) const
{
	return Equal( pt ) ? true : false;
}

inline bool SC3DPoint::operator!=( const SC3DPoint& pt ) const
{
	return !( *this == pt );
}

inline bool SC3DPoint::operator<( const SC3DPoint& pt ) const
{
	if( SCFloatEq( m_fX, pt.m_fX ) )
	{
		if( SCFloatEq( m_fY, pt.m_fY ) )
		{
			if( SCFloatEq( m_fZ, pt.m_fZ ) )
				return false;
			else
				return m_fZ < pt.m_fZ ? true : false;
		}
		else
			return m_fY < pt.m_fY ? true : false;
	}
	else
		return m_fX < pt.m_fX ? true : false;
}

inline SC3DPoint SC3DPoint::operator+( const SC3DPoint& pt ) const
{
	SC3DPoint res( *this );

	res += pt;

	return res;
}

inline SC3DPoint SC3DPoint::operator-( const SC3DPoint& pt ) const
{
	SC3DPoint res( *this );

	res -= pt;

	return res;
}

inline SC3DPoint SC3DPoint::operator*( float f ) const
{
	SC3DPoint res( *this );

	res *= f;

	return res;
}

inline SCBOOL SC3DPoint::Equal( const SC3DPoint& pt, SCDOUBLE32 fDelta/* = 0.0f*/ ) const
{
	return SCFloatEq( m_fX, pt.m_fX, fDelta ) && 
			SCFloatEq( m_fY, pt.m_fY, fDelta ) && 
			SCFloatEq( m_fZ, pt.m_fZ, fDelta );
}

inline SCBOOL SC3DPoint::EqualDirect( const SC3DPoint& pt, SCDOUBLE32 fDelta/* = 0.0f*/ ) const
{
	return DotProduct( pt ) <= fDelta ? TRUE : FALSE;
}

inline SCDOUBLE32 SC3DPoint::AbsValue() const
{
	return SCDOUBLE32(sqrt( DotProduct( *this ) ));
}

inline SCDOUBLE32 SC3DPoint::DotProduct( const SC3DPoint& pt ) const
{
	return m_fX * pt.m_fX + m_fY * pt.m_fY + m_fZ * pt.m_fZ;
}

inline SC3DPoint SC3DPoint::CrossProduct( const SC3DPoint& pt ) const
{
	return SC3DPoint( m_fY * pt.m_fZ - m_fZ * pt.m_fY,
						m_fZ * pt.m_fX - m_fX * pt.m_fZ,
						m_fX * pt.m_fY - m_fY * pt.m_fX );
}

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
typedef class SCAD3DMODEL_API std::vector<SC3DPoint> SC3DPointVector;
/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
typedef class SCAD3DMODEL_API std::vector<SC3DPoint*> SC3DPointPtrVector;

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
struct SCAD3DMODEL_API SC3DCube
{
	SC3DCube()
	{
		m_fMinX = m_fMaxX = m_fMinY = m_fMaxY = m_fMinZ = m_fMaxZ = FLT_MAX;
	}

	SC3DCube&	operator =	( const SC3DCube& cube );

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SCBOOL		IsValid		() const;
	
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SCDOUBLE32	GetDX		() const { return m_fMaxX - m_fMinX;}
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SCDOUBLE32	GetDY		() const { return m_fMaxY - m_fMinY;}
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SCDOUBLE32	GetDZ		() const { return m_fMaxZ - m_fMinZ;}

	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SC3DPoint	GetCenter	() const;
	/*
		Name:
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	SCDOUBLE32	GetRadius	() const;

	SCDOUBLE32	m_fMinX;
	SCDOUBLE32	m_fMaxX;
	SCDOUBLE32	m_fMinY;
	SCDOUBLE32	m_fMaxY;
	SCDOUBLE32	m_fMinZ;
	SCDOUBLE32	m_fMaxZ;
};

inline SC3DCube& SC3DCube::operator=( const SC3DCube& cube )
{
	m_fMinX = cube.m_fMinX;
	m_fMaxX = cube.m_fMaxX;
	m_fMinY = cube.m_fMinY;
	m_fMaxY = cube.m_fMaxY;
	m_fMinZ = cube.m_fMinZ;
	m_fMaxZ = cube.m_fMaxZ;

	return *this;
}

inline SCBOOL SC3DCube::IsValid() const
{
	if( m_fMinX == FLT_MAX || m_fMaxX == FLT_MAX ||
		m_fMinY == FLT_MAX || m_fMaxY == FLT_MAX ||
		m_fMinZ == FLT_MAX || m_fMaxZ == FLT_MAX )
			return FALSE;

	return TRUE;
}

inline SC3DPoint SC3DCube::GetCenter() const
{
	return SC3DPoint( ( m_fMaxX + m_fMinX ) / 2.f, ( m_fMaxY + m_fMinY ) / 2.f, ( m_fMaxZ + m_fMinZ ) / 2.f );
}

inline SCDOUBLE32 SC3DCube::GetRadius() const
{
	SC3DPoint pt = GetCenter() - SC3DPoint( m_fMaxX, m_fMaxY, m_fMaxZ );

	return SCDOUBLE32(sqrt( pt.m_fX * pt.m_fX + pt.m_fY * pt.m_fY + pt.m_fZ * pt.m_fZ ));
}

//#pragma	pack(pop)


#endif //SC3DPoint_hxx__
