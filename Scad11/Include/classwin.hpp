#ifndef CLASS_WINDOWS_H
#define CLASS_WINDOWS_H

#include <windows.h>
#pragma pack(push,1)

#ifdef  CLASSHELP_EXPORTS
#define CLASS_EXPORT __declspec(dllexport)
#else
#define CLASS_EXPORT __declspec(dllimport)
#endif

#define BITSPERBYTE  8
#define MAXDIR   _MAX_DIR
#define MAXDRIVE _MAX_DRIVE
#define MAXEXT   _MAX_EXT
#define MAXPATH  _MAX_PATH
#define MAXFILE  _MAX_PATH
#define M_PI     3.1415926535897932384626433832795

#define fnmerge  _makepath
#define fnsplit  _splitpath

#include <math.h>
#include <stdarg.h>
#include <process.h>
#include <time.h>
#include <ctype.h>
#include <sys\stat.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <typedata.h>
#include <fileprnt.h>
#include <filework.h>
#include <filetext.h>
#include <file_mem.h>
#include <message.h>
#include <messageLib.h>
#include <rc_text.h>
#include <gauss.h>
#include <errno.h>
#include <ObjectString.hpp>
#include <ObjectFile.hpp>
#include "read_memory.hpp"
#include "vk_poly.hpp"

CLASS_EXPORT void    Crash(LPCSTR Text);
CLASS_EXPORT void    Crash(LPCSTR Text1, LPCSTR Text2 );
CLASS_EXPORT void    CrashFull(LPCSTR Text, ...);
CLASS_EXPORT void    ExitSystem(int);

//   Программы работы с битами
CLASS_EXPORT  void    BitOff(BYTE *c,int n);
CLASS_EXPORT  void    BitOn(BYTE *c,int n);
CLASS_EXPORT  int     BitRead(BYTE *c,int n);
CLASS_EXPORT  void    ConvStrBit(LPCSTR Inp,LPSTR Out);
CLASS_EXPORT  int     DecodeNumBit( BYTE *Inp, BYTE Quantity, BYTE *Num);
CLASS_EXPORT  void    DecodeStrBit( BYTE *Inp, int Qntt, BYTE *Out);
CLASS_EXPORT  int     SumBit(BYTE *Inp, int Length );
CLASS_EXPORT  void    AddBit(BYTE *Inp, BYTE *Out, int Length );

//   Программы конвертировани
CLASS_EXPORT  double  CharDouble( LPCSTR s, BYTE & knt );
CLASS_EXPORT  long    CharLong  ( LPCSTR s, BYTE & knt );
CLASS_EXPORT  WORD    CharWord  ( LPCSTR s, BYTE & knt );
CLASS_EXPORT  DWORD   CharDWord ( LPCSTR s, BYTE & knt );
CLASS_EXPORT  void    DoubleChar  ( double Dbl, LPSTR Str, int LenStr);
CLASS_EXPORT  void    DoubleCharP ( double Dbl, LPSTR Str, int LenStr);
CLASS_EXPORT  void    FloatChar   ( float  Flt, LPSTR Str, int LenStr);
CLASS_EXPORT  long    DoubleLong(double s,BYTE &i);


CLASS_EXPORT void     CopyWordToLong( long *Out, WORD *Inp, int Quantity );
CLASS_EXPORT void     CopyFloatToDouble( double *Out, float *Inp, int Quantity );
CLASS_EXPORT void     CopyDoubleToFloat( float *Out, double *Inp, int Quantity );

CLASS_EXPORT void     CrashMessage();
CLASS_EXPORT void     CrashMessage( int NumError ... );

CLASS_EXPORT void     ExitMessage(DWORD);
CLASS_EXPORT void     det3x3(double w[], double *dj);
CLASS_EXPORT double   det3x3(double w[]);

CLASS_EXPORT int      MathError( struct _exception *e );

CLASS_EXPORT void     FileComponentDrive( LPSTR Name, LPSTR DriveOut );
CLASS_EXPORT void     FileComponentDir( LPSTR Name, LPSTR DirOut );
CLASS_EXPORT void     FileComponentName( LPSTR Name, LPSTR NameOut );
CLASS_EXPORT void     FileComponentExt( LPSTR Name, LPSTR ExtOut );

CLASS_EXPORT void     FileError(WORD ns,LPCSTR TextFileName );
CLASS_EXPORT void     FontSize(LPCSTR FontName, BYTE FntSize, BYTE &FontHeight, BYTE &FontWidth,
                          BYTE &LineSpacing  );
CLASS_EXPORT int      FileTime( LPCSTR Name, FILETIME *TimeCreate, FILETIME *TimeAccess,  FILETIME *TimeLastWrite );
CLASS_EXPORT int      FileTime( HANDLE, FILETIME *TimeCreate, FILETIME *TimeAccess,  FILETIME *TimeLastWrite );
CLASS_EXPORT long     FileTimeCompare( FILETIME *T1, FILETIME *T2 );
CLASS_EXPORT long     FileTimeCompare( SYSTEMTIME &ST1, SYSTEMTIME &ST2 );
CLASS_EXPORT void     FileNameComponent( LPSTR Name, LPSTR NameOut, LPSTR Dir=NULL );
CLASS_EXPORT void     FileNameAdd( LPSTR Name, LPSTR NameAdd, LPSTR NameOut );

CLASS_EXPORT void     FileAddPath( LPSTR Path, LPSTR Name, LPSTR NameOut );
CLASS_EXPORT void     FilePath(LPCSTR Name,LPSTR Path);
CLASS_EXPORT void     FilePath(LPCSTR Name1, LPSTR Name2,LPSTR Name, LPSTR Exp=NULL );
CLASS_EXPORT void     FilePathBase( LPCSTR NameBase, LPCSTR NameOld,LPSTR Path );
CLASS_EXPORT void     FilePathBase( LPCSTR NameBase, LPCSTR NameOld,LPSTR Ext, LPSTR Path );
CLASS_EXPORT LPCSTR   GetPath(LPCSTR Name);

CLASS_EXPORT short    index(LPSTR s1,short l1,LPSTR s2,short l2);
CLASS_EXPORT float    Interpol( float Arg, float ListArg[], float Table[], int Quantity, int Step = 1 );
CLASS_EXPORT float    InterpolTable( float ArgX,      float ArgY,
           float ListArgX[], float ListArgY[], float Table[],  int QuantityX, int QuantityY );
CLASS_EXPORT double    Interpol( double Arg, double ListArg[], double Table[], int Quantity, int Step = 1 );
CLASS_EXPORT double    InterpolTable( double ArgX,      double ArgY,
           double ListArgX[], double ListArgY[], double Table[],  int QuantityX, int QuantityY );

CLASS_EXPORT double    LinePunct(double t1[3], double t2[3], double t[3], double Eps );

CLASS_EXPORT   int     ListText( WORD Quantity, WORD *List, LPSTR Out, int MaxLenOut );
CLASS_EXPORT   void    ListText( WORD Quantity, BYTE *List, LPSTR Out, int MaxLenOut );
CLASS_EXPORT   int     ListText( int  Quantity, int  *List, LPSTR Out, int MaxLenOut );
CLASS_EXPORT   void    ListText( int  Quantity, BYTE *List, LPSTR Out, int MaxLenOut );

CLASS_EXPORT   int     PointLine( double *Point1, double *Point2,  double *Point, double Eps );
CLASS_EXPORT   int     ListReadWord( FILETEXT &Work, LPSTR Buffer, WORD &LenBuf );
CLASS_EXPORT   int     ListReadLong( FILETEXT &Work, LPSTR Buffer, WORD &LenBuf );

CLASS_EXPORT   int     MatrCos(double *CoordList, double *MatrCosOut);
CLASS_EXPORT   int     MatrCos(double SF,double CF,double *CoordList,double *MatrCosOut);
CLASS_EXPORT   void    MultMatr( double *, double *u, int, int, int, double *);
CLASS_EXPORT   void    MultVect (int QuantityVect, int LengthVect, double *MatrCos, double *Vectr, int OrderMK );
CLASS_EXPORT   void    MultVect ( int OrderMK, double *MatrCos, int OrderVector, double *VectrIn, double *VectOut );
CLASS_EXPORT   void    MultVect ( int Order, double *Matr, double *Vect, double *Out );

CLASS_EXPORT   int     NormVector( long Order, double *Vector );
CLASS_EXPORT   double  NormVectorC( long Order, double *Vector, double Eps=0 );
CLASS_EXPORT   double  NormVectorL( long Order, double *Vector, double Eps=0 );
CLASS_EXPORT   void    NormVect( int Order, double *Mas, double *Inp, double *Out =NULL);
CLASS_EXPORT   void    NormVect( int Order, double *In1, double *In2, double *In3, double &Res );
CLASS_EXPORT   void    NormVect( int Order, double *In1, double *In2, double *In3, long double &Res );

CLASS_EXPORT   void    NumericalIntegrationLine( int QuantityPunct, double x1, double x2, 
							int &QuantityPunctOut, double * sn, double * xn );
CLASS_EXPORT   void    NumericalIntegrationLine( int QuantityPunct, double x1, double y1, double x2, double y2,
						    int &QuantityPunctOut, double * sn, double * xn, double * yn );
CLASS_EXPORT   void    NumericalIntegrationTriangle( int QuantityPunct, double x1, double y1, double x2, double y2, double x3, double y3,
 						    int &QuantityPunctOut, double * sn, double * xn, double * yn );
CLASS_EXPORT   void    NumericalIntegrationQuadrangle( int QuantityPunct, double a, double b,
						    int &QuantityPunctOut, double * sn, double * xn, double * yn );
CLASS_EXPORT   void    NumericalIntegrationQuadrangle( int QuantityPunct, double x1, double y1, double x2, double y2, double x3, double y3,
 						    int &QuantityPunctOut, double * sn, double * xn, double * yn );

CLASS_EXPORT   int     PointLine( double *Point1, double *Point2,  double *Point, double Eps=0 );

CLASS_EXPORT   int     poly_2(double a, double b, double c, double &x1, double &x2 );
CLASS_EXPORT   int     poly_2(long double a, long double b, long double c, long double &x1, long double &x2 );
CLASS_EXPORT   int     poly_3(double a, double b, double c, double d, double &x1, double &x2, double &x3 );
CLASS_EXPORT   int     poly_3(long double a, long double b, long double c, long double d,
                        long double &x1, long double &x2, long double &x3 );
CLASS_EXPORT   void    PolyDiffer( int StepDif, int Step, double *Inp, double *Out=NULL);
CLASS_EXPORT   void    PolyDiffer( int StepDif, int Step, long double *Inp, long double *Out=NULL );

CLASS_EXPORT   double  PolyValue(int Step, double  *Pol, double  x, int Type=0 );
CLASS_EXPORT  long double PolyValue(int Step, long double  *Pol, long double  x, int Type=0 );

CLASS_EXPORT   int     ParamText(LPSTR Param, LPSTR Name, LPSTR Out);
CLASS_EXPORT   int     ParamValue(LPSTR Param, LPSTR Name, int &Value );
CLASS_EXPORT   int     ParamValue(LPSTR Param, LPSTR Name, short &Value );

CLASS_EXPORT   void    Printf(LPCSTR ...);
CLASS_EXPORT   void    dPrintf(LPCSTR ...);
CLASS_EXPORT   void    dPrintfTime(LPSTR Text=NULL);

CLASS_EXPORT   void    PrintList(FILEPRINT &Print, WORD Quantity, WORD *List, char );
CLASS_EXPORT   void    PrintList( FILEPRINT &Work, int Quantity, int *List, char End );
CLASS_EXPORT   void    PrintList( FILEPRINT &Work, int Quantity, double *List, char End );

CLASS_EXPORT   int     ReadString(WORD &LenBuf, LPSTR Buffer,FILETEXT &fInp);
CLASS_EXPORT   void    StringRead(LPCSTR String,DWORD LenStr,DWORD & PosStr, LPCSTR & Word);
CLASS_EXPORT   void    ReadWord(WORD &LenBuf, LPSTR Buffer, LPSTR & pos, FILETEXT &fInp);

CLASS_EXPORT   BYTE    Separate( LPCSTR InpString,  DWORD LengthInpString,
                                     DWORD &CurrentPos, LPCSTR SeparateSymbol, LPSTR OutString);

CLASS_EXPORT   void    SeparateString(LPSTR Text, int Quantity, char Name[][16]);

CLASS_EXPORT   int     strcmpup( LPCSTR Str1, LPCSTR Str2);
CLASS_EXPORT   int     strncmpup( LPCSTR Str1, LPCSTR Str2, int Len );
CLASS_EXPORT   LPSTR   strstrup( LPCSTR Str1, LPCSTR Str2 );

CLASS_EXPORT   int     sPrintFormat( LPSTR Buffer, LPCSTR Format, void * Block, int LengthBlock );

CLASS_EXPORT   int     TextList( LPCSTR Text, WORD MaxNum, WORD &Quantity, WORD *List, BYTE &Control );
CLASS_EXPORT   int     TextList( LPCSTR Text, int MaxNum, int &Quantity, int *List, BYTE &Control );
CLASS_EXPORT   int     TextListFull( LPCSTR Text, WORD MaxNum, WORD &Quantity, WORD *List, BYTE &Control );
CLASS_EXPORT   int     TextListFull( LPCSTR Text, int MaxNum, int &Quantity, int *List, BYTE &Control );

CLASS_EXPORT   void    TextWrite(LPCSTR FileName, LPCSTR FileNameWord);
CLASS_EXPORT   void    TextWrite(LPCSTR FileName);

CLASS_EXPORT   char    TolowerRus( char Text );
CLASS_EXPORT   void    Tolower( LPSTR Text );
CLASS_EXPORT   char    ToupRus( char Text );
CLASS_EXPORT   void    ToupRus( LPSTR Text );

CLASS_EXPORT   int     Trace( double a1, double b1, double c1, double a2, double b2, double c2, 
					          double &xp, double &yp );  //  пересечение двух линий

CLASS_EXPORT   void    VectorOrt( int Order, double *Base, double *Forma1, double *Forma2, double Norm=0 );


#pragma pack(pop)

#endif
