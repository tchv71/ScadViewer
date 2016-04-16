// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
#ifndef ExportDXFH
#define ExportDXFH
#include "ViewGeometry.h"

// Utility class for DXF export
class	CExportDXF
{

	FILE			*fileDXF;
	void  WriteHeader(void) const;
public:
	CExportDXF(): fileDXF(nullptr)
	{
	}
	bool  Open(LPCTSTR FileName);
	void  Write(int tag, char *value) const
	{ fprintf(fileDXF, "%3d\n%s\n", tag, value); }
	void  Write(int tag, FLOAT_TYPE value) const
	{ fprintf(fileDXF, "%3d\n%g\n", tag, value); }
	void  Close(void) const;
};

//---------------------------------------------------------------------------
#endif
