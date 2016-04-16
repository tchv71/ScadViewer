// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
#include "stdafx.h"
#include <stdio.h>

#include "ExportDXF.h"

char	LineLayer[] = "BARS";
char	FaceLayer[] = "FACES";

char	Sec[] = "SECTION";
char	Esec[] = "ENDSEC";


void CViewGeometry::ExportToDxf(LPCTSTR szFileName)
{
	CExportDXF	dxf;
	if(!dxf.Open(szFileName))
		return;
	for(UINT i = 0; i < ElementArray.size(); i++)
	{
		CViewElement	&El = ElementArray[i];
		SViewVertex &p1 = VertexArray[El.Points[0]];
		SViewVertex	&p2 = VertexArray[El.Points[1]];
		if (El.IsContour())
			continue;
		int			NumPoints=0;
		switch(El.Type)
		{
			case EL_LINE:
				NumPoints = 2;
				dxf.Write(0, "LINE");
				dxf.Write(8, LineLayer);
				dxf.Write(10, p1.x);
				dxf.Write(20, p1.y);
				dxf.Write(30, p1.z);

				dxf.Write(11, p2.x);
				dxf.Write(21, p2.y);
				dxf.Write(31, p2.z);

				break;
			case EL_QUAD:
				NumPoints = 4;
				break;
			case EL_TRIANGLE:
				NumPoints = 3;
				break;
		}

		if(NumPoints != 2)
		{
			dxf.Write(0, "3DFACE");
			dxf.Write(8, El.IsBarLike() ? LineLayer : FaceLayer);
			for(int j = 0; j < NumPoints; j++)
			{
				SViewVertex &p = VertexArray[El.Points[j]];
				dxf.Write(10 + j, p.x);
				dxf.Write(20 + j, p.y);
				dxf.Write(30 + j, p.z);
				if(NumPoints == 3 && j == 2)
				{
					dxf.Write(13, p.x);
					dxf.Write(23, p.y);
					dxf.Write(33, p.z);
				}
			}
		}
	}

	dxf.Close();
}

void CExportDXF::WriteHeader(void) const
{
	Write(0, Sec);
	Write(2, "HEADER");
	Write(9, "$EXTMAX");
	Write(10, "0.0");
	Write(20, "0.0");
	Write(9, "$EXTMIN");
	Write(10, "297.0");
	Write(20, "297.0");
	Write(0, Esec);

	Write(0, Sec);
	Write(2, "TABLES");
	Write(0, "TABLE");
	Write(2, "LAYER");

	Write(0, "LAYER");
	Write(2, LineLayer);
	Write(70, 64);
	Write(62, 1);
	Write(6, "CONTINUOUS");

	Write(0, "LAYER");
	Write(2, FaceLayer);
	Write(70, 64);
	Write(62, 5);
	Write(6, "CONTINUOUS");
	Write(0, "ENDTAB");
	Write(0, Esec);

	Write(0, Sec);
	Write(2, "ENTITIES");
}

bool  CExportDXF::Open(LPCTSTR FileName)
{
	_tfopen_s(&fileDXF,FileName, _T("wt"));
	if(fileDXF == nullptr)
		return false;
	WriteHeader();
	return true;
}

void  CExportDXF::Close(void) const
{
	Write(0, Esec);
	Write(0, "EOF");
	fclose(fileDXF);
}
