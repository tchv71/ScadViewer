/*
	SvTypes.h - basic types for Scad/Forum Viewer
*/
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#ifndef _SV_TYPES_H
#define _SV_TYPES_H


//#define USE_DOUBLE

#ifndef USE_DOUBLE
typedef float FLOAT_TYPE;
#define _glVertex3		glVertex3f
#define _glVertex3v		glVertex3fv
#define _glTranslate	glTranslatef
#define _glNormal3v		glNormal3fv
#define _glRotate		glRotatef
#define _glScale		glScalef
#else
typedef double FLOAT_TYPE;
#define _glVertex3		glVertex3d
#define _glVertex3v		glVertex3dv
#define _glTranslate	glTranslated
#define _glNormal3v		glNormal3dv
#define _glRotate		glRotated
#define _glScale		glScaled
#endif

#if defined(SCAD11) || defined(SCAD21)
typedef int	NUM_ELEM_TYPE;
#else
typedef WORD	NUM_ELEM_TYPE;
#endif


#endif