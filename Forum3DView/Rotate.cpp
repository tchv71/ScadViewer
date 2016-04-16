// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
#include "stdafx.h"
#include <math.h>
#include "SCADDefProj.h"

#ifndef USE_DOUBLE
#define sin sinf
#define cos cosf
#endif

#include "Rotate.h"

CRotator::CRotator(void): Fy_rot(0)
{
	Fz_rot = Fx_rot = z_s = y_s = x_s = 0;
	z_c = x_c = y_c = 1;
}

void CRotator::z_rotate(FLOAT_TYPE &x, FLOAT_TYPE &y, FLOAT_TYPE &z) const
{
	FLOAT_TYPE	x1, y1;
	x1 = x;
	y1 = y;
	x = x1 * z_c - y1 * z_s;
	y = x1 * z_s + y1 * z_c;
};

void CRotator::y_rotate(FLOAT_TYPE &x, FLOAT_TYPE &y, FLOAT_TYPE &z) const
{
	FLOAT_TYPE	x1, z1;
	x1 = x;
	z1 = z;
	x = x1 * y_c + z1 * y_s;
	z = -x1 * y_s + z1 * y_c;
};

void CRotator::x_rotate(FLOAT_TYPE &x, FLOAT_TYPE &y, FLOAT_TYPE &z) const
{
	FLOAT_TYPE	y1, z1;
	y1 = y;
	z1 = z;
	y = y1 * x_c - z1 * x_s;
	z = y1 * x_s + z1 * x_c;
}

void CRotator::SetRot(FLOAT_TYPE z_rot, FLOAT_TYPE x_rot)
{
	Fz_rot = z_rot;
	Fx_rot = x_rot;
	Fy_rot = 0;
	z_s = sin(z_rot);
	z_c = cos(z_rot);
	x_s = sin(x_rot);
	x_c = cos(x_rot);
}

void CRotator::SetRot(FLOAT_TYPE z_rot, FLOAT_TYPE y_rot, FLOAT_TYPE x_rot)
{
	Fz_rot = z_rot;
	Fx_rot = x_rot;
	Fy_rot = 0;
	z_s = sin(z_rot);
	z_c = cos(z_rot);
	x_s = sin(x_rot);
	x_c = cos(x_rot);
	y_s = sin(y_rot);
	y_c = cos(y_rot);
}

void CRotator::GetRot(FLOAT_TYPE &z_rot, FLOAT_TYPE &x_rot) const
{
	z_rot = Fz_rot;
	x_rot = Fx_rot;
}

void CRotator::Rotate(FLOAT_TYPE &x, FLOAT_TYPE &y, FLOAT_TYPE &z) const
{
	z_rotate(x, y, z);
	x_rotate(x, y, z);
}

// Обратное вращение
void CRotator::Rotate_1(FLOAT_TYPE &x, FLOAT_TYPE &y, FLOAT_TYPE &z)
{
	SetRot(-Fz_rot, -Fx_rot);
	x_rotate(x, y, z);
	z_rotate(x, y, z);
	SetRot(-Fz_rot, -Fx_rot);
}


void CRotator::SetPredefinedView(int ViewNo)
{
	SCDefProjInfo info;
	SCADDefProj::GetInfo(SCDefProjType(ViewNo), info);
	SetRot(info.m_fZ_rot * atanf(1) / 45, info.m_fX_rot * atanf(1) / 45);
}

//---------------------------------------------------------------------------
//#pragma package(smart_init)
