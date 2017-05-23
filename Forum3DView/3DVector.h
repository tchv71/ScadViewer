//////////////////////////////////////////////////////////////////////
// 3DVector.h: interface for the C3DVector class.
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV

// All Rights Reserved

// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#if !defined(AFX_3DVECTOR_H__150AF9C5_003B_459E_880C_62D81D752423__INCLUDED_)
#define AFX_3DVECTOR_H__150AF9C5_003B_459E_880C_62D81D752423__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Model.h"

template <class T>
class C3DVector
{
public:
	C3DVector()
	{
	};
	C3DVector(T x, T y, T z) 
	{
		v[0]= x;
		v[1]= y;
		v[2]= z;
	};
	C3DVector(const S3dPoint &pt)
	{
		v[0]= pt.x;
		v[1]= pt.y;
		v[2]= pt.z;
	}
	S3dPoint operator+(const S3dPoint& p) const
	{
		return S3dPoint(p.x + v[0], p.y + v[1], p.z + v[2]);
	}
	C3DVector operator -(const C3DVector<T> &rv2) const
	{
		return C3DVector<T>(v[0]-rv2.v[0],v[1]-rv2.v[1], v[2]-rv2.v[2]);
	}
	C3DVector operator +(const C3DVector<T> &rv2) const
	{
		return C3DVector<T>(v[0]+rv2.v[0],v[1]+rv2.v[1], v[2]+rv2.v[2]);
	}
	C3DVector operator *(const T &n) const
	{
		return C3DVector<T>(v[0]*n,v[1]*n, v[2]*n);
	}
	// —кал€рное произведение векторов
	T DotProduct(const C3DVector<T> &rv) const
	{
		return v[0]*rv.v[0]+v[1]*rv.v[1]+v[2]*rv.v[2];
	};
	T Length() const
	{
		return T(sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
	}
	void Invert()
	{
		v[0]= -v[0];
		v[1]= -v[1];
		v[2]= -v[2];
	};

	C3DVector CrossProduct(const C3DVector<T> &rv2) const
	{
		C3DVector<T> resV;
		resV.v[0] = v[1] * rv2.v[2] - v[2] * rv2.v[1];
		resV.v[1] = v[2] * rv2.v[0] - v[0] * rv2.v[2];
		resV.v[2] = v[0] * rv2.v[1] - v[1] * rv2.v[0];
		resV.Normalize();
		return resV;
	};

	void SetCrossProduct(const C3DVector<T> &rv1, const C3DVector<T> &rv2)
	{
		v[0] = rv1.v[1] * rv2.v[2] - rv1.v[2] * rv2.v[1];
		v[1] = rv1.v[2] * rv2.v[0] - rv1.v[0] * rv2.v[2];
		v[2] = rv1.v[0] * rv2.v[1] - rv1.v[1] * rv2.v[0];
		Normalize();
	};
	void Normalize()
	{
		T d = Length();
		if(d < 1e-5f)
		{
			v[0] = v[1] = v[2] = 0;//      ErrorMg("zero length vector");
			return;
		}
		
		v[0] /= d;
		v[1] /= d;
		v[2] /= d;
	};
	T * GetVector()
	{
		return v;
	};
	void RotateAroundAxis(const C3DVector<T> &axis, T ang)
	{
		const T cosa = cos(ang);
		const T sina = sin(ang);
		const T x = axis.v[0];
		const T y = axis.v[1];
		const T z = axis.v[2];

		const T M[3][3] =
		{
			{cosa + (1 - cosa)*x*x, (1 - cosa)*x*y - sina*z, (1 - cosa)*x*z + sina*y},
			{(1-cosa)*y*x+sina*z, cosa+(1-cosa)*y*y, (1-cosa)*y*z-sina*x},
			{ (1 - cosa)*z*x-sina*y, (1-cosa)*z*y+sina*x, cosa+(1-cosa)*z*z }
		};
		C3DVector<T> res;
		for (size_t i = 0; i < 3; i++)
			res.v[i] = v[0] * M[i][0] + v[1] * M[i][1] + v[2] * M[i][2];
		*this = res;
	}
	T AngleTo(const C3DVector<T> &vec) const
	{
		return acos(DotProduct(vec) / (Length()*vec.Length()));
	}
	T v[3];
};

inline S3dPoint operator+(const S3dPoint& pt, const C3DVector<FLOAT_TYPE>& vec) 
{
	return S3dPoint(pt.x + vec.v[0], pt.y + vec.v[1], pt.z + vec.v[2]);
}
#endif // !defined(AFX_3DVECTOR_H__150AF9C5_003B_459E_880C_62D81D752423__INCLUDED_)
