// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#ifndef _TIMER_H
#define _TIMER_H

class CTimer
{
public:
	LARGE_INTEGER	freq, start;
	void Start(void)
	{
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
	}
	FLOAT_TYPE Stop()
	{
		LARGE_INTEGER	end;
		QueryPerformanceCounter(&end);
		return FLOAT_TYPE(end.QuadPart - start.QuadPart) / FLOAT_TYPE(freq.QuadPart); 
	}
	CString StopStr()
	{
		LARGE_INTEGER	end;
		QueryPerformanceCounter(&end);
		CString str;
		str.Format(_T("%.1f мсек"), Stop() * 1000);
		return str;
	}
	
};
#endif