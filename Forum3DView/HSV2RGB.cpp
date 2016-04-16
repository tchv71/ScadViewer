#include "stdafx.h"
#include "HSV2RGB.h"


CHSV2RGB::CHSV2RGB()
{
}


CHSV2RGB::~CHSV2RGB()
{
}


unsigned int CHSV2RGB::Hsv2Rgb(int H, int S, int V)
{
	int Hi = H / 60;
	int Vmin = (100 - S) * V / 100;
	int a = (V - Vmin) * (H % 60) / 60;
	int Vinc = Vmin + a;
	int Vdec = V - a;
	Vmin *= 255;
	Vmin /= 100;
	Vinc *= 255;
	Vinc /= 100;
	V *= 255;
	V /= 100;
	Vdec *= 255;
	Vdec /= 100;
	UINT c = 0;
	switch (Hi)
	{
	case 0:
		c = RGB(V, Vinc, Vmin);
		break;
	case 1:
		c = RGB(Vdec, V, Vmin);
		break;
	case 2:
		c = RGB(Vmin, V, Vinc);
		break;
	case 3:
		c = RGB(Vmin, Vdec, V);
		break;
	case 4:
		c = RGB(Vinc, Vmin, V);
		break;
	case 5:
		c = RGB(V, Vmin, Vdec);
		break;
	}
	return c;
}

unsigned int CHSV2RGB::Hsv2Rgb255(int H, int S, int V)
{
	int Hi = H / 43;
	int Vmin = (256 - S) * V / 256;
	int a = (V - Vmin) * (H % 43) / 43;
	int Vinc = Vmin + a;
	int Vdec = V - a;
	UINT c = 0;
	switch (Hi)
	{
	case 0:
		c = RGB(V, Vinc, Vmin);
		break;
	case 1:
		c = RGB(Vdec, V, Vmin);
		break;
	case 2:
		c = RGB(Vmin, V, Vinc);
		break;
	case 3:
		c = RGB(Vmin, Vdec, V);
		break;
	case 4:
		c = RGB(Vinc, Vmin, V);
		break;
	case 5:
		c = RGB(V, Vmin, Vdec);
		break;
	}
	return c;
}

static int Conv(double P, double Q, double Tc)
{
	if (Tc < 0)
		Tc += 1;
	if (Tc > 1)
		--
			Tc -= 1;
	double c;
	if (Tc < 1.0 / 6)
		c = P + (Q - P) * 6 * Tc;
	else if (Tc < 1.0 / 2)
		c = Q;
	else if (Tc < 2.0 / 3)
		c = P + (Q - P) * (2.0 / 3 - Tc) * 6;
	else
		c = P;
	int C = int(c * 255);
	if (C > 255) C = 255;
	return C;
}

unsigned int CHSV2RGB::Hsl2Rgb255(int H, int S, int L)
{
	double _S = double(S) / 255;
	double _L = double(L) / 255;
	double Q = (L < 0.5) ? _L * (1 + _S) : _L + _S - (_L * _S);
	double P = 2 * _L - Q;
	double Hk = double(H) / 255;
	double Tr = Hk + 1.0 / 3;
	double Tg = Hk;
	double Tb = Hk - 1.0 / 3;
	return RGB(Conv(P, Q, Tr),Conv(P, Q, Tg),Conv(P, Q, Tb));
}

