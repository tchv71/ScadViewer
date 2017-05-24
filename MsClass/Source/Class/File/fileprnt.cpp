#include <stdafx.h>
#include "fileprnt.h"
#include "typedata.h"
#include <edit_wrt.h>
#include <stdio.h>

EXPORT void  TextWrite(LPCSTR);
EXPORT void  FontSize( LPCSTR FontName, BYTE FntSize,
					BYTE &FontHeight, BYTE &FontWidth, BYTE &LineSpacing );
int  FormatSelect(LPSTR &pF, LPSTR  &pN );

EXPORT void  FILEPRINT::Open( LPCSTR TextFileName, LPCSTR Mode,
         LPCSTR FontNm, BYTE FntSize,
	      int PageH, int PageW, int TextH, int TextW, int Left,  int Top,
         BYTE ListYes )
{
         BYTE Line;
	      Edit = 1;
	      strncpy(FontName,FontNm,MAXPATH);
	      FontSize( FontNm,FntSize,FontHeight,FontWidth,Line);
         if ( FontWidth == 0 ) FontWidth = FontHeight;
	      LineSpacing = Line;
    	   Open(TextFileName,Mode,PageH,PageW,TextH,TextW,Left,Top,ListYes);

}

EXPORT void   FILEPRINT::Open(LPCSTR TextFileName,LPCSTR Mode,
          int PageH, int PageW, int TextH, int TextW,
          int Left,  int Top,
          BYTE ListYes )
{
         char Buf[512];

         FILEBASE::Open(TextFileName,Mode);

	 if ( FontHeight == 0 )  FontHeight  = 10;
	 if ( FontWidth  == 0 )  FontWidth   = 10;
	 if ( LineSpacing == 0 ) LineSpacing = 12;

     PageHeight = (WORD)(PageH * 56.6929);
	 PageWidth  = (WORD)(PageW * 56.6929);
	 TextHeight = (WORD)(TextH * 56.6929);
	 TextWidth  = (WORD)(TextW * 56.6929);
     MarginLeft = (WORD)(Left  * 56.6929);
	 MarginTop  = (WORD)(Top   * 56.6929);

     LengthLine = (WORD)(TextWidth  * 0.08 / FontHeight);
	 Width  =  LengthLine * FontHeight;
	 Height =  TextHeight / 20 - 3 * LineSpacing;

	 if ( Edit ) {
//	    fprintf(fName,"//%s\n",FontName);
	    sprintf(Buf,"//%s\n",FontName);
             Put(Buf);
	    sprintf(Buf,"%%%hd/%hd/%hd/%hd/%hd/%hdP\n",
	      PageHeight,PageWidth,MarginTop,TextHeight,MarginLeft,TextWidth);
	    Put(Buf);
 	    sprintf(Buf,"%%3/%hdW",FontHeight);
	    Put(Buf);   }

         if ( ListYes ) NumPage = 1;

}

EXPORT void FILEPRINT::OpenLandscape( LPCSTR TextFileName, LPCSTR Mode,
         LPCSTR FontNm, BYTE FntSize )
{
      Open(TextFileName,Mode,FontNm,FntSize,210,297,160,250,30,30,1);
}

EXPORT void  FILEPRINT::Open(LPCSTR TextFileName,LPCSTR Mode,
          int PageH, int PageW, BYTE ListYes )
{
    FILEBASE::Open(TextFileName,Mode);

	 FontHeight  = 10;
	 FontWidth   = 10;
	 LineSpacing = 12;

	 if ( PageH > 255 ) PageH = 255;
	 if ( PageW > 512 ) PageW = 512;

	 PageHeight = TextHeight = 12 * PageH;
	 PageWidth  = TextWidth  = 10 * PageW;

	 LengthLine = PageW;
	 Width  =  LengthLine * FontHeight;
	 Height =  12 * ( PageH - 3 );

	 if ( ListYes ) NumPage = 1;
//		 Page();

}

EXPORT void FILEPRINT::Close()
{
                 char Name[MAXPATH];
                 if ( this == NULL ) return;
		 if (  GetHandle() == NULL ) return;
		 Column(0);
		 if ( PosPage ) {
		    PosPage = 0;
		    if ( EndPage ) {   EndPage(HeadParam);   Print();  }
                   if ( NumPage )  Write("\f",1);  }
                 strncpy(Name,FileName,MAXPATH);
		 FILEBASE::Close();
		 if ( Edit ) TextWrite(Name);
		 memset(this,0,sizeof(FILEPRINT));
}

EXPORT void FILEPRINT::Column(int NumPos)
{
		 WORD n = PosLine / FontWidth;
		 if ( PosLine >= Width || NumPos < n ) {   Print('\n');  n = 0;  }
		 CopySymbol(' ',NumPos-n-1);
}

EXPORT void FILEPRINT::ColumnEnd() {    Column(LengthLine);  }

EXPORT void FILEPRINT::CopySymbol(char Symbol,int Quantity)
{
		 int i;
		 for ( i=0; i<Quantity; i++ ) Print(Symbol);
}

EXPORT void FILEPRINT::Page(void)
{
                   char Buf[256];
                   int k;

		 if (  GetHandle() == NULL ) return;
		 if ( PosLine ) {  Print();  PosPage = 1;  }

                 if ( NumPage ) {
		    if ( PosPage ) {
                       PosPage = 0;
		       if ( EndPage ) {   EndPage(HeadParam);   Print();  }
                       Write("\f",1);
                       Print();   }
		    if ( Head ) Head(HeadParam);
                    else {
                       k = sprintf(Buf,"%s%*c%04d.",
                          Title,LengthLine-5-strlen(Title),' ',NumPage++);
                       Write(Buf,k);
                       Print();  Print();  }
                    }

}

void FILEPRINT::Print(void)
{
		 if (  GetHandle() == NULL ) return;
		 Buffer[PosCursor++] = 0x0D;
		 Buffer[PosCursor++] = 0x0A;
                 Write(Buffer,PosCursor);
		 PosCursor = 0;  PosLine = 0;
	 	 PosPage += LineSpacing;
}

EXPORT void FILEPRINT::PrintCenter(LPCSTR Text)
{
		 int i=0, k=0, n;
		 int Len = strlen(Text);

		 while( i < Len ) {
			 n = LengthLine;
			 for ( ; i <= Len && i - k < LengthLine; i++ )
				 if ( Text[i] == ' ' || i == Len ) n = i;
			 Column((LengthLine+k-n)/2);
			 Print(&Text[k],n-k);
			 k += n + 1;  i = k;  }

}

EXPORT void FILEPRINT::PrintCenter(LPCSTR Text, WORD Length)
{      LPCSTR pT = Text;
		 for ( ; ; ) {
			 PrintCenter(pT);
			 pT += strlen(pT) + 1;
			 if ( pT - Text >= Length ) break;
			 }
}

EXPORT void FILEPRINT::Print(char Symbol) {     Print(&Symbol,1);  }
EXPORT void FILEPRINT::Print(LPCSTR Text) {     Print(Text,strlen(Text));  }

EXPORT void FILEPRINT::Print(LPCSTR Text, WORD LengthText)
{
		 WORD i;
		 char  c;

		 if (  GetHandle() == NULL ) return;

		 if ( LengthText ) LastChar = Text[LengthText-1];

		 for ( i=0; i<LengthText; i++ ) {
			 c = Text[i];
			 if ( c == 0 ) c = '\n';
			 if ( c == '@' ) c = ' ';
			 if ( c >= 9 && c < 14 && c != '\n' ) c = ' ';
			 if ( PosLine >=  Width || c == '\n' )  {
				 if ( PosPage >= Height ) Page();
				 else Print();
				 }
			 if ( c != '\n' ) {
				 Buffer[PosCursor++] = c;
				 PosLine += FontWidth;  }
			 }
}

EXPORT int FILEPRINT::Format(LPCSTR _format ...)
{
        int k;
	va_list arg_ptr;
	char debug[512];
	va_start(arg_ptr,_format);
	k = vsprintf(debug,_format,arg_ptr);
        Print(debug);
	va_end(arg_ptr);
        return k;
}

EXPORT void FILEPRINT::PrintPhrase(LPCSTR Text)
{
		 int i, k = -1, l;
		 char R[] = "><!(),:; ";

		 for ( i=0; i<=strlen(Text); i++ )  {
			 if (  ( strchr(R,Text[i]) || Text[i] >= 0 && Text[i] <= ' ' )	&& k >= 0 ) {
				 l = i - k;
				 if ( PosLine / FontHeight + l >= LengthLine ) {
					 Print('\n');
					 CopySymbol(' ',Board); 	}
				 Print(&Text[k],l);
				 if ( Text[i] ) Print(Text[i]);
				 k = -1;  }
			 else if ( k < 0 ) k = i;
			 }
}


#include <ctype.h>

EXPORT int FILEPRINT::Put(LPCSTR Format) {
		int i;
		return Put(Format,&i,0);
		}


EXPORT int FILEPRINT::Put(LPCSTR Format,WORD Length) {
		LPSTR s=(LPSTR)Format;
		while ( s - (LPSTR)Format < Length ) {
			if ( Put(s) ) return 1;
			Print('\n');
			s += strlen(s) + 1;  }
			return 0;
}


EXPORT int FILEPRINT::Put(
	  LPCSTR Format, void FAR * Block, int LengthBlock )
{

/*  	         Format Specifiers  C++                */
/*               ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ                     */
/*  						       */
/*   % [flags] [width] [.prec] [F³N³h³l] type          */
/*  						       */
/*   type  Format of Output                            */
/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ        */
/*    d    signed   decimal int                        */
/*    i    signed   decimal int                        */
/*    o    unsigned octal   int                        */
/*    u    unsigned decimal int                        */
/*    x    In printf =  unsigned hexadecimal int       */
/*         Lowercase; in scanf = hexadecimal int       */
/*    X    In printf =  unsigned hexadecimal int       */
/*         Uppercase; in scanf = hexadecimal long      */
/*    f    Floating point [-]dddd.ddd                  */
/*    e    Floating point [-]d.ddd e [+/-]ddd          */
/*    g    Format e or f based on precision            */
/*    E    Same as e except E for exponent             */
/*    G    Same as g except E for exponent             */
/*  						       */
/*    c    Single character                            */
/*    s    Print characters till '\0' or [.prec]       */
/*    %    The % character                             */
/*  						       */
/*    p    Pointer: near = YYYY; far = XXXX:YYYY       */
/*    n    Stores count of characters written so       */
/*         far in the location pointed to by           */
/*         input argument                              */
/*  						       */
/*   [flag]  What flag specifies                       */
/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ      */
/*   (none)  Right-justify; pad 0 or blank             */
/*             to left                                 */
/*     -     Left-justify; pad spaces to right         */
/*     +     Always begin with + or -                  */
/*   blank   Print sign for negative values only       */
/*  						       */
/*     #     Convert using alternate form:             */
/*            c,s,d,i,u  (no effect)                   */
/*            o          Prepend 0 to nonzero arg      */
/*            x or X     Prepend 0x or 0X to arg       */
/*            e, E, f    Always use decimal point      */
/*            g or G     Same as e, E, or f but        */
/*                         no trailing zeros           */
/*  						       */
/*  						       */
/*   [width]  Effect on Output                         */
/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ      */
/*      n     At least n characters, blank-padded      */
/*      0n    At least n characters, 0 left fill       */
/*????? *     Next argument from list is width         */
/*  	                                               */
/*  						       */
/*   [.prec]  Effect on Output                         */
/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ      */
/*   none     Default precision                        */
/*  .0        (d,i,o,u,x)    Default precision         */
/*            (e,E,f)        No decimal point          */
/*   .n       At most n characters                     */
/*??? *        Next argument from list = precision     */
/*  						       */
/*  						       */
/*   Modifier  How arg is interpreted                  */
/*  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ      */
/*??    F      ÄÄÄÄÄÄ         arg is far pointer       */
/*??    N      ÄÄÄÄÄÄ         arg is near pointer      */
/*      h      d,i,o,u,x,X    arg is short int         */
/*      l      d,i,o,u,x,X    arg is long int          */
/*      l      e,E,f,g,G      arg is double            */
/*                              (scanf only)           */
/*      L      e,E,f,g,G      arg is long double       */
/*-----------------------------------------------------*/
/*      C    ¤®¯®«­¨â¥«ì­ë© ¬®¤¨ä¨ª â®p ¤«ï æ¥«ëx      */
/*             d,i,o,u,x,X    arg is char              */
/*                                                     */
/*      W   type  Format of Write                      */
/*        %n1/n2/n3/n4W                                */
/*        n1 - áâ¨«ì: 0 - ­®p¬                         */
/*                    1 - ¦¨p­®¥ ­ ç¥pâ ­¨¥            */
/*                    2 - ªãpá¨¢­®¥ ­ ç¥pâ ­¨¥         */
/*      A   absatz                                     */
/*                                                     */
/*      P   Page                                       */

		 static char TypeFormatCpp[] = "diouxXeEfgGcspn";
		 static char TypeFloat[]     = "eEfgG";
		 static char TypeInt[]       = "diouxX";
		 static char TypeWrite[]     = "WAP";

		 LPSTR pBlock  = (LPSTR)Block;
		 LPSTR aFormat;
		 LPSTR pFormat;
		 LPSTR pS;
		 int Len = 0, LenFrmt, k;
		 char c, cl, Frmt[128];
		 char buf[513];
		 TYPE_DATA *Data;
		 int i, n, kGrf = -1, iRet = 0, QPos, QPosSign;
		 double d;

		 pFormat = aFormat = (LPSTR)Format;

		 while ( 1 ) {

			i = FormatSelect(pFormat,aFormat);
			if ( *pFormat == 0 ) break;
			if ( i == 0 || i == 2 ) {
			   if ( i == 2 ) iRet = 1;
			   Print(pFormat,(WORD)(aFormat-pFormat));
			   continue;  }

			Data = ( union TYPE_DATA *) &pBlock[Len];

			LenFrmt = (WORD)(aFormat - pFormat);
			c = *( aFormat - 1 );  cl = * ( aFormat - 2 );
			if ( LenFrmt > 100 )  {  iRet = 1;  goto _10;  }
			memcpy(Frmt,pFormat,LenFrmt );  Frmt[LenFrmt] = 0;

			if ( strchr(TypeWrite,c ) ) {
				if ( Edit == 0 ) continue;
				CHP WorkChp;
				PAP WorkPap;
				BYTE b, FntSize;
				if ( c != 'W' && PosCursor ) Print('\n');
				if ( c == 'P' ) continue;
				if ( c == 'W' ) {
					TextWriteFormatCHP(Frmt,LenFrmt,&WorkChp,b);
					FntSize = WorkChp.fontSize / 2;
					FontSize( FontName,FntSize,FontHeight,FontWidth,b);
					FontWidth = FontHeight;
					LineSpacing = b;
					}
				if ( c == 'A' ) {
					TextWriteFormatPAP(Frmt,LenFrmt,&WorkPap,b);
					if ( WorkPap.lineSpacing ) LineSpacing = WorkPap.lineSpacing / 20;
					}
				LengthLine = (WORD)(TextWidth  * 0.08 / FontHeight);
				Width  =  LengthLine * FontHeight;
				Height =  TextHeight / 20 - 3 * LineSpacing;
				Buffer[PosCursor++] = 0x01;
				Buffer[PosCursor++] = ' ' + LenFrmt - 1;
				memcpy(&Buffer[PosCursor],&Frmt[1],LenFrmt - 1);
				PosCursor += LenFrmt - 1;
				continue;    }

			if ( LenFrmt ) {
				QPosSign = (short)strtol(pFormat+1,&pS,10);
				QPos = ( QPosSign > 0 ) ? QPosSign : -QPosSign;
				if ( QPos == 0 ) {
					if ( c == 's' ) QPos = strlen(Data->s);
					else QPos = 1;  }
				if ( *pS != c && *pS != cl && *pS != '.' || QPos > 511 || QPos < -511 )
					{  iRet = 1;  goto _10;  }
				if ( c == 'b' ) c = ' ';
				if ( c == 'N' ) c = '\n';
				if ( c == ' ' ||  c == '\n' ) {   CopySymbol(c,QPos);  continue;  }
				if ( c == 'Z' ) {  Column(QPos);  continue;  }
				if ( c == 'r' ) {  CopySymbol(LastChar,QPos);  continue;  }
				}

			if ( Len >= LengthBlock || kGrf == 0 ) break;
			if ( kGrf > 0 ) kGrf--;

			if ( strchr(TypeFormatCpp,c ) ) {

				if ( c == 's' ) {
					k = sprintf(buf,Frmt,DataS);
					n = QPos;
					goto _05; }
				if ( strchr(TypeInt,c) ) {
					n = sizeof(int);
					if ( cl == 'h' ) {
						k = sprintf(buf,Frmt,DataHI);
						n = sizeof(short);  }
					else if ( cl == 'l' ) {
							  k = sprintf(buf,Frmt,DataL);
							  n = sizeof(long);  }
						  else if ( cl == 'C' ) {
									 Frmt[LenFrmt-2] = 'h';
									 k = sprintf(buf,Frmt,(WORD)DataC);
									 n = 1;  }
								 else k = sprintf(buf,Frmt,DataI);
					goto _05; }

				if ( strchr(TypeFloat,c) ) {
					n = sizeof(float);
					if ( cl == 'l' ) {
						k = sprintf(buf,Frmt,DataD);
						n = sizeof(double);  }
					else if ( cl == 'L' ) {
							  k = sprintf(buf,Frmt,DataLD);
							  n = sizeof(long double);  }
						  else k = sprintf(buf,Frmt,DataF);
					goto _05; }

				if ( c == 'c' ) {
					k = sprintf(buf,Frmt,DataC);
					n = 1;  }

				if ( c == 'p' || c == 'n' ) {
					k = sprintf(buf,Frmt,DataP);
					n = sizeof(void*);   }

_05:        if ( k == EOF || k > 511 )  {  iRet = 1;  goto _10;  }
				if ( k == 0 ) CopySymbol(' ',QPos);
				Print(buf);   Len += n;
				continue;     }

			if ( c == 'K' ) {
				kGrf = Data->hi;   Len += sizeof(short);
				continue;  }

			if ( c == '?' )
				if ( Data->f == -7 ) {
					CopySymbol(' ',QPos);   Len += sizeof(float);
					continue;   }
				else c = 'T';

			if ( c == 'B' ) {   Len += QPos;  continue;  }

			if ( c == 'F' || c == 'T' ) {
				if ( cl == 'l' ) {  d = DataD;   Len += sizeof(double);  }
				else             {  d = DataF;   Len += sizeof(float);   }
				if ( c == 'T' && d == 0 ) CopySymbol(' ',QPos);
				else {
					DoubleChar(d,buf,QPosSign);
					Print(buf);  }   }

			if ( c == 'S' ) {
				if ( DataSFB == 0 ) {
					DoubleChar(DataSFD,buf,-QPosSign);  Print(buf);  }
				else Print(DataS,strlen(DataS));
				Len += 1 + sizeof(double);  }

			}

_10: 	 return iRet;
}