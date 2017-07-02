//////////////////////////////////////////////////////////////////////
//
// SC3DRetCodes.hxx: SCAD3DModel returned codes.
//
//////////////////////////////////////////////////////////////////////


#ifndef SC3DRetCodes_hxx__
#define SC3DRetCodes_hxx__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "SCAD3DModelDef.hxx"
//#include "SCADException.hxx"

typedef int SC3DRetCode;


#define	S3DRC_OK	0

#define	S3DRC_ERR						-1
#define	S3DRC_ERR_INVALID_ARG			-2
#define	S3DRC_ERR_OUT_OF_MEM			-3
#define	S3DRC_ERR_MTR_DONT_INVERSE		-4
#define	S3DRC_ERR_MATERIAL_ABSENT		-5
#define	S3DRC_ERR_LIGHT_ABSENT			-6
#define	S3DRC_ERR_MODEL_ABSENT			-7
#define	S3DRC_ERR_MODEL_REINIT			-8
#define	S3DRC_ERR_INCOMPABILITY			-9
#define	S3DRC_ERR_MODEL_UNINIT			-10
#define	S3DRC_ERR_MODEL_UNUPDATABLE		-11
#define	S3DRC_ERR_INVALID_IND			-12
#define	S3DRC_ERR_DCMGR_UNINIT			-13
#define	S3DRC_ERR_DCMGR_REINIT			-14
#define	S3DRC_ERR_DC_ABSENT				-15
#define	S3DRC_ERR_DCMGR_INIT			-16
#define	S3DRC_ERR_DC_NOT_INIT			-17

#define	S3DRC_ERR_NOT_IMPL				-256


#define	S3DRC_WRN				1
#define	S3DRC_FIN_ITERATION		2
#define	S3DRC_BREAK_RENDERING	3
#define	S3DRC_REPEAT_RENDERING	4
#define	S3DRC_IMAGE_NOT_ACCESS	5

#endif //SC3DRetCodes_hxx__
