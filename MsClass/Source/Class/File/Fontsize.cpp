#include <stdafx.h>
#include <defclass.h>

EXPORT void  FontSize(
	      	 LPCSTR FontName, BYTE FntSize,
	      	 BYTE &FontHeight, BYTE &FontWidth,
	      	 BYTE &LineSpacing  )
{
		 HDC hdc;
		 LOGFONT LogFont;
		 TEXTMETRIC TextMet;
		 HFONT hFont;
		 HFONT hFontOld;

		 memset(&LogFont,0,sizeof(LOGFONT));
		 LogFont.lfHeight = FntSize;
		 LogFont.lfWidth  = (long)FntSize * 0.75;
		 LogFont.lfPitchAndFamily = FIXED_PITCH;
		 LogFont.lfWeight = FW_NORMAL;
		 strncpy(LogFont.lfFaceName,FontName,LF_FACESIZE);

		 hFont = CreateFontIndirect(&LogFont);

		 hdc = GetDC(NULL);
//		 hdc = CreateCompatibleDC(GetDesktopWindow());
		 hFontOld = (HFONT)SelectObject(hdc,hFont);
		 GetTextMetrics(hdc,&TextMet);

		 FontHeight  = TextMet.tmHeight;
                   if ( FontHeight == 7 ) FontHeight = 8;
		 FontWidth   = TextMet.tmAveCharWidth;
		 LineSpacing = FontHeight + 2 * TextMet.tmDescent;

		 SelectObject(hdc,hFontOld);
		 DeleteObject(hFont);
//		 ReleaseDC(hwnd,hdc);
		 DeleteDC(hdc);

}