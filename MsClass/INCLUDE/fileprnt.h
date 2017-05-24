#ifndef FILEPRINT_FLAG_H
#define FILEPRINT_FLAG_H
#pragma pack(push, 1)
#include <filebase.h>
#include "convert.h"

#define MAX_TITLE  40

class FILEPRINT:FILEBASE {

private :
		 BYTE  Edit;
		 char  FontName[MAXPATH+1];
		 WORD  PageHeight;
		 WORD  PageWidth;
		 WORD  TextHeight;
		 WORD  TextWidth;
		 WORD  MarginTop;
		 WORD  MarginLeft;
		 WORD  Board;
		 WORD  NumPage;
		 WORD  PosPage;
		 WORD  PosLine;
		 BYTE  Justification;
		 BYTE  FontHeight;
		 BYTE  FontWidth;
		 WORD  LineSpacing;
		 WORD  LengthLine;
		 WORD  Height;
		 WORD  Width;
		 WORD  PosCursor;
		 char  LastChar;
		 char  Title[MAX_TITLE+1];
		 char  Buffer[512];
		 void  (*Head)(void*);
		 void  (*EndPage)(void*);
		 void  *HeadParam;

	 void Print(void);

public :
EXPORT    FILEPRINT() {  memset(this,0,sizeof(FILEPRINT));  };
EXPORT   ~FILEPRINT() {  Close();  };

EXPORT void  Open( LPCSTR TextFileName,LPCSTR Mode, int PageH=63, int PageW=72, BYTE ListYes=0);

EXPORT void  Open( LPCSTR TextFileName, LPCSTR Mode,
		         LPCSTR FontName, BYTE FontSize = 10 );
EXPORT void  OpenLandscape( LPCSTR TextFileName, LPCSTR Mode,
		         LPCSTR FontName, BYTE FontSize = 10 );
EXPORT void  Open( LPCSTR TextFileName, LPCSTR Mode,
           LPCSTR FontName, BYTE FontSize=10,
           int PageH=297, int PageW=210, int TextH=250, int TextW=160, int Left=30,  int Top=15,
           BYTE ListYes=1 );

EXPORT void  Open(LPCSTR TextFileName,LPCSTR Mode,
           int PageH, int PageW,  int TextH, int TextW, int Left,  int Top,
           BYTE ListYes=1 );

EXPORT void  Close();

EXPORT void  Page(WORD PageH,WORD PageW,WORD TextH,WORD TextW,WORD MrgnTop,WORD MrgnLeft);
EXPORT void  Column(int);
EXPORT void  ColumnEnd();
EXPORT void  CopySymbol(char,int);
EXPORT void  Page();
EXPORT void  PrintCenter(LPCSTR Text);
EXPORT void  PrintCenter(LPCSTR Text,WORD Length);
EXPORT int   Put(LPCSTR Format, void FAR * Block, int LengthBlock );
EXPORT int   Put(LPCSTR Format);
EXPORT int   Put(LPCSTR Format,WORD Length);
EXPORT int   Format(LPCSTR _format ...);

EXPORT void  Print(LPCSTR);
EXPORT void  Print(char);
EXPORT void  Print(LPCSTR,WORD);
EXPORT void  PrintPhrase(LPCSTR);

inline  void   SetTitle(LPCSTR Text) {   strncpy(Title,Text,MAX_TITLE);  }
inline  LPCSTR GetFileName()   {  return FileName;  }

inline  BYTE   GetEdit()       {  return Edit; }
inline  void   SetEdit(BYTE Name) {   Edit = Name;   }

inline  WORD   GetBoard()      {  return Board;      }
inline  void   SetBoard(WORD Boa)    {  Board = Boa; }

inline  WORD   GetNumPage()    {  return NumPage;    }
inline  void   SetPage(WORD Pg)  {  NumPage = Pg; }

inline  int    GetPosPage(void)   {  return ( PosPage / LineSpacing );  }
inline  int    GetPosLine(void)   {  return ( PosLine / FontHeight );  }
inline  int    GetLengthPage()   {  return Height / LineSpacing;  }
inline  int    GetLengthLine()   {  return LengthLine;  }
inline  int    GetHeight()       {  return Height;  }
inline  int    GetWidth()        {  return Width;  }

inline  BYTE   GetJustification() {  return Justification;  }
inline  void   SetJustification(BYTE Ju)  {  Justification = Ju; }

inline  BYTE   GetFontHeight()   {  return FontHeight;   }
inline  void   SetFontHeight(BYTE FontH) {   FontHeight = FontH;   }

inline  BYTE   GetFontWidth()   {  return FontWidth;   }
inline  void   SetFontWidth(BYTE FontW) {   FontWidth = FontW;   }

inline  WORD   GetLineSpacing()   {  return LineSpacing;  }
inline  void   SetLineSpacing(WORD LineS)  {  LineSpacing = LineS; }

inline  void * GetHeadParam(void)    {   return HeadParam;  }

inline  void   SetHead(void Header(void*))    {
	 Head = Header;  HeadParam = NULL;  EndPage = NULL;  }
inline  void   SetHead(void Header(void*),void FAR *HeaderParam)    {
	 Head = Header;  HeadParam = HeaderParam;  EndPage = NULL;  }
inline  void   SetHead(void Header(void*),void FAR *HeaderParam, void End(void*))    {
	 Head = Header;  HeadParam = HeaderParam;  EndPage = End;  }
inline  void   SetEndPage(void End(void*)) {  EndPage = End;  }

	      friend class INPUT;

};
#pragma pack(pop)

#endif

/*---------------------------------------------------------------------------*/
