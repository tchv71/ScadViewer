#ifndef CLASS_WINDOWS_H
#define CLASS_WINDOWS_H

#include <windows.h>
#include <defclass.h>
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

#include <bit.h>
#include <convert.h>
#include <stringup.h>
#include <typedata.h>
#include <fileprnt.h>
#include <filework.h>
#include <file_mem.h>
#include <message.h>
#include <rc_text.h>
#include <gauss.h>
#include <space.h>
#include <errno.h>
//#include "BaseClass.hpp"
//#include "ObjectList.hpp"
//#include "ObjectString.hpp"

#pragma pack(push, 1)
EXPORT  void     CopyWordToLong( long *Out, WORD *Inp, int Quantity );
EXPORT  void     CopyFloatToDouble( double *Out, float *Inp, int Quantity );
EXPORT  void     PASCAL CopyDoubleToFloat( float *Out, double *Inp, int Quantity );

EXPORT  void     CrashMessage();
EXPORT  void     CrashMessage( int NumError ... );

EXPORT  void     ExitMessage(DWORD);
EXPORT  void     det3x3(double w[], double *dj);
EXPORT  double   det3x3(double w[]);

EXPORT  int      MathError( _exception *e );

EXPORT  void     FileError(WORD ns,LPCSTR TextFileName );
EXPORT  void     FontSize(LPCSTR FontName, BYTE FntSize,
                          BYTE &FontHeight, BYTE &FontWidth,
                          BYTE &LineSpacing  );
EXPORT  int      FileTime( LPCSTR Name, FILETIME *TimeCreate, FILETIME *TimeAccess,  FILETIME *TimeLastWrite );
EXPORT  int      FileTime( HANDLE, FILETIME *TimeCreate, FILETIME *TimeAccess,  FILETIME *TimeLastWrite );
//EXPORT  int      FileTime( LPCSTR Name, ftime *Time);
//EXPORT  int      FileTimeCompare( ftime *T1, ftime *T2 );
EXPORT  long     FileTimeCompare( FILETIME *T1, FILETIME *T2 );
EXPORT  void     FilePath(LPCSTR Name,LPSTR Path);
EXPORT  void     FilePath( HINSTANCE , LPCSTR Name,LPSTR Path);
EXPORT  LPCSTR   GetPath(LPCSTR Name);
EXPORT  LPCSTR   GetPath(HINSTANCE hInst,LPCSTR Name);

EXPORT  short    index(LPSTR s1,short l1,LPSTR s2,short l2);
EXPORT  float    Interpol( float Arg, float ListArg[], float Table[], int Quantity, int Step = 1 );
EXPORT  float    InterpolTable( float ArgX,      float ArgY,
                    float ListArgX[], float ListArgY[], float Table[],  int QuantityX, int QuantityY );

EXPORT  double   LinePunct(double t1[3], double t2[3], double t[3], double Eps );

EXPORT  int      ListText(WORD Quantity, WORD *List, LPSTR Out, int MaxLenOut );

EXPORT  int      MatrCos(double *CoordList, double *MatrCosOut);
EXPORT  int      MatrCos(double SF,double CF,double *CoordList,double *MatrCosOut);
EXPORT  void     MultMatr( double *, double *u, int, int, int, double *);
EXPORT  void     MultVect (int QuantityVect, int LengthVect, double *MatrCos, double *Vectr, int OrderMK );
EXPORT  void     MultVect ( int OrderMK, double *MatrCos, int OrderVector, double *VectrIn, double *VectOut );
EXPORT  void     MultVect ( int Order, double *Matr, double *Vect, double *Out );

EXPORT  int      NormVector( long Order, double *Vector );
EXPORT  double   NormVectorC( long Order, double *Vector, double Eps=0 );
EXPORT  double   NormVectorL( long Order, double *Vector, double Eps=0 );
EXPORT  void     NormVect( int Order, double *Mas, double *Inp, double *Out =NULL);
EXPORT  void     NormVect( int Order, double *In1, double *In2, double *In3, double &Res );
EXPORT  void     NormVect( int Order, double *In1, double *In2, double *In3, long double &Res );
EXPORT  void     VectorOrt( int Order, double *Base, double *Forma1, double *Forma2, double Norm=0 );

EXPORT  int      poly_2(double a, double b, double c, double &x1, double &x2 );
EXPORT  int      poly_2(long double a, long double b, long double c, long double &x1, long double &x2 );
EXPORT  int      poly_3(double a, double b, double c, double d, double &x1, double &x2, double &x3 );
EXPORT  int      poly_3(long double a, long double b, long double c, long double d,
                        long double &x1, long double &x2, long double &x3 );
EXPORT  void     PolyDiffer( int Step, double *Inp, double *Out=NULL);
EXPORT  void     PolyDiffer( int Step, long double *Inp, long double *Out=NULL );

EXPORT  double   PolyValue(int Step, double  *Pol, double  x, int Type=0 );
EXPORT  long double PolyValue(int Step, long double  *Pol, long double  x, int Type=0 );

EXPORT  int     ParamText(LPSTR Param, LPSTR Name, LPSTR Out);
EXPORT  int     ParamValue(LPSTR Param, LPSTR Name, int &Value );
EXPORT  int     ParamValue(LPSTR Param, LPSTR Name, short &Value );

EXPORT  void    Printf(LPCSTR ...);
EXPORT  void    dPrintf(LPCSTR ...);
EXPORT  void    dPrintfTime();

EXPORT  int     ReadString(WORD &LenBuf, LPSTR Buffer,FILETEXT &fInp);
EXPORT  void    StringRead(LPCSTR String,DWORD LenStr,DWORD & PosStr, LPCSTR & Word);
EXPORT  void    ReadWord(WORD &LenBuf, LPSTR Buffer, LPSTR & pos, FILETEXT &fInp);

EXPORT  BYTE    Separate( LPCSTR InpString,  DWORD LengthInpString,
                                 DWORD &CurrentPos, LPCSTR SeparateSymbol, LPSTR OutString);

EXPORT  int     TextList( LPCSTR Text, WORD MaxNum, WORD &Quantity, WORD *List, BYTE &Control );
EXPORT  int     TextListFull( LPCSTR Text, WORD MaxNum, WORD &Quantity, WORD *List, BYTE &Control );
EXPORT  void    TextWrite(LPCSTR FileName, LPCSTR FileNameWord);
EXPORT  void    TextWrite(LPCSTR FileName);

EXPORT  void    ToupRus(LPSTR Text);
#pragma pack(pop)

#endif