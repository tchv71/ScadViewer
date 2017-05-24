#include <stdafx.h>
#include <defclass.h>

EXPORT void ToupRus(LPSTR Text)
{
       static char RusLow[] =
	      "יצףךוםדרשחץתפûגאןנמכהז‎ÿקסלטעüב‏";
       static char RusUp[] =
	      "ÉÖÓKEHÃØÙÇXÚÔÛBAÏPOËÄÆÝ‗×CMÈTÜÁÞ";

       LPCSTR p;
       LPSTR  pT = Text;

       for ( ; *pT; pT++ )  {
	  p = strchr(RusLow, *pT = toupper(*pT));
	  if ( p ) *pT = RusUp[p-RusLow];   }

}