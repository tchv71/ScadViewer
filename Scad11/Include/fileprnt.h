#ifndef FILEPRINT_FLAG_H
#define FILEPRINT_FLAG_H
#pragma pack(push,1)

#include <filebase.h>

#define MAX_TITLE  40

class FILEPRINT:  public FILEBASE 
{
private :
		 int   Edit;
		 int   LengthPage;
		 int   LengthLine;
		 int   Board;

		 int   NumPage;
		 int   PosPage;
		 int   PosLine;

		 char  LastChar;
		 char  Title[MAX_TITLE+1];
		 char  Buffer[512];
		 void  (*Head)(void*);
		 void  (*EndPage)(void*);
		 void  *HeadParam;

	 void Print(void);

public :
CLASS_EXPORT       FILEPRINT() {  memset(this,0,sizeof(FILEPRINT));  };
CLASS_EXPORT      ~FILEPRINT() {  Close();  };

int   CLASS_EXPORT   Open( LPCSTR TextFileName,LPCSTR Mode, int PageH=63, int PageW=72, BYTE ListYes=0);

void  CLASS_EXPORT   Close();

void  CLASS_EXPORT   Page(WORD PageH,WORD PageW,WORD TextH,WORD TextW,WORD MrgnTop,WORD MrgnLeft);
void  CLASS_EXPORT   Column(int);
void  CLASS_EXPORT   ColumnEnd();
void  CLASS_EXPORT   CopySymbol(char,int);
void  CLASS_EXPORT   Page();
void  CLASS_EXPORT   PrintCenter(LPCSTR Text);
void  CLASS_EXPORT   PrintCenter(LPCSTR Text,WORD Length);
int   CLASS_EXPORT   Put(LPCSTR Format, void FAR * Block, int LengthBlock );
int   CLASS_EXPORT   Put(LPCSTR Format);
int   CLASS_EXPORT   Put(LPCSTR Format,WORD Length);
int   CLASS_EXPORT   Format(LPCSTR _format ...);

void  CLASS_EXPORT   Print(LPCSTR);
void  CLASS_EXPORT   Print(char);
void  CLASS_EXPORT   Print(LPCSTR,WORD);
void  CLASS_EXPORT   PrintPhrase(LPCSTR);

inline  void   SetTitle(LPCSTR Text) {   strncpy(Title,Text,MAX_TITLE);  }
inline  LPCSTR GetFileName()   {  return FileName;  }

inline  BYTE   GetEdit()       {  return Edit; }
inline  void   SetEdit(BYTE Name) {   Edit = Name;   }

inline  WORD   GetBoard()      {  return Board;      }
inline  void   SetBoard(WORD Boa)    {  Board = Boa; }

inline  WORD   GetNumPage()      {  return NumPage;    }
inline  void   SetPage(WORD Pg)  {  NumPage = Pg; }

inline  int    GetPosPage(void)  {  return PosPage;  }
inline  int    GetPosLine(void)  {  return PosLine;  }
inline  int    GetLengthPage()   {  return LengthPage;  }
inline  int    GetLengthLine()   {  return LengthLine;  }

inline  void * GetHeadParam(void)    {   return HeadParam;  }

inline  void   SetHead(void Header(void*))    {
	 Head = Header;  HeadParam = NULL;  EndPage = NULL;  }
inline  void   SetHead(void Header(void*),void FAR *HeaderParam)    {
	 Head = Header;  HeadParam = HeaderParam;  EndPage = NULL;  }
inline  void   SetHead(void Header(void*),void FAR *HeaderParam, void End(void*))    {
	 Head = Header;  HeadParam = HeaderParam;  EndPage = End;  }
inline  void   SetEndPage(void End(void*)) {  EndPage = End;  }

inline  LONGLONG  GetLength() {  return LengthFile + PosLine;  }
};

#pragma pack(pop)
#endif


