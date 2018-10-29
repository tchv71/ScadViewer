// Copyright (C) 2005,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#ifndef _VERSION_H
#define _VERSION_H
#define V_MINOR 4
#define V_BUILD 7
#define STR(x) #x
#define STR1(x) STR(x)

////////////////////////////////////////////////////////////////////////////////////
// Version info
#ifdef SCAD11
#define SV_VER				1,11,V_MINOR,V_BUILD
#define SV_VER_STR			"1.11." STR1(V_MINOR) "." STR1(V_BUILD) "\0"
#define SV_PRODUCT_VER		11,1,0,0
#define SV_PRODUCT_VER_STR	"11.1.0.0\0"
#define SV_PRODUCT_NAME		"Scad Office R11.1\0"
#else
#ifdef SCAD21
#define SV_VER				1,21,V_MINOR,V_BUILD
#define SV_VER_STR			"1.21." STR1(V_MINOR) "." STR1(V_BUILD) "\0"
#define SV_PRODUCT_VER		21,1,3,1
#define SV_PRODUCT_VER_STR	"21.1.3.1\0"
#define SV_PRODUCT_NAME		"Scad Office R21.1\0"
#else
#define SV_VER				1,11,V_MINOR,V_BUILD
#define SV_VER_STR			"1.11." STR1(V_MINOR) "." STR1(V_BUILD) "\0"
#define SV_PRODUCT_VER		7,31,5,0
#define SV_PRODUCT_VER_STR	"7,31,5,0\0"
#define SV_PRODUCT_NAME		"Scad Office 7.31 R5\0"
#endif
#endif
#define SV_COPYRIGHT		"Copyright (C) 2000-17 Dmitry Tcvetkov\0"
#endif
