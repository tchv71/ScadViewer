#pragma once
class CHSV2RGB
{
public:
	CHSV2RGB();
	~CHSV2RGB();
	static unsigned int Hsv2Rgb(int H, int S, int V);
	static unsigned int Hsv2Rgb255(int H, int S, int V);
	static unsigned int Hsl2Rgb255(int H, int S, int L);
};

