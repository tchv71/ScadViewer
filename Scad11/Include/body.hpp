#ifndef BODY_FLAG_H
#define BODY_FLAG_H

#include <vector>
#include <algorithm>

#pragma pack(push,1)

#define  EPSILON   1e-4

typedef BOOL (WINAPI *ConsulExport)( LPCSTR buf, int size, double** pnts_buf, int& pnts_count, int** ndxs_buf, int& ndxs_count);
typedef BOOL (WINAPI *ConsulExportFin)(double* pnts, int pnts_count, int* ndxs, int ndxs_count);

#pragma pack(pop)

#pragma pack(push,4)

struct DECART {  float x, y, z;   };

struct ELEM_BODY {
       int  NumElem;
       BYTE Type;  // 1-4 - n - узловой                            
		           //  5  - 3-x узловой, пpоециpующийся в отpезок  
		           //  6  - 3-x узловой, пpоециpующийся в отpезок  
       BYTE NoVideo;
       BYTE Res[2];
       int  Node[4];
       };

struct LOOK_BODY {

       ELEM_BODY       * ElemBody;
       int               QuantityElemBody;
       double            MK[3][3];
       BYTE              TypeBase;
       int             * Order;

       BYTE              TypeProfile;
       BYTE              TypePlate;
       BYTE              FragmParam;
       BYTE              Fragm;
       BYTE              DeleteProcess;
       BYTE              YesForum;
       BYTE              Res[3];
       int               QuantityElemMask;
       BYTE            * MaskElem;   /* Маска фрагмента                               */
       BYTE            * MaskFragm;  /* Маска фрагмента                               */

       int               QuantityNodeBody;
       CK              * Coord;      /* Кооpдинаты дополнительных узлов для профилей  */
       GrafCK          * GrafCoord;  /* Гpафические кооpдинаты дополнительных узлов для профилей */
       double            DelProfile; /*  отступы при отображении профилей  */

	   HINSTANCE         LibTonus;
       ConsulExport      ConExport;
       ConsulExportFin   ConExportFinalize;

       };

struct LINE_BODY {
       DECART     *pD1;
       DECART     *pD2;
       float      xp, yp, zp;  /*  вектоp, паpаллельный линии    */
       float      c;           /*  уpавнение пpоекции            */
/*    zb * x - xb * z + c = 0     */
       };

struct ELEM_BODY_GEOM {
       float       a, b, c, d;  /*  уpавнение плоскости            */
				/*   a * x + b * y + c * z + d = 0 */
       float       xMax, xMin, yMax, yMin, zMax, zMin;
       };

struct ELEM_BODY_FULL {
       ELEM_BODY      * pEB;
	   int              NumBodyFirst;
	   int              NumBodyNext;
	   int              NumBodyEq;
	   BYTE             YesBodyVor;
       BYTE             QuantityLine;
	   BYTE             Res[2];
       ELEM_BODY_GEOM   EBG;
       LINE_BODY        LineBody[4];
       };

class BODY_EQUIVALENT
{
public:

     int              NumBody;
	 ELEM_BODY_FULL * pEBF;
     
	 BODY_EQUIVALENT();                   // Constructor
     virtual ~BODY_EQUIVALENT();          // Destructor

     BODY_EQUIVALENT( const BODY_EQUIVALENT &Src); // Copy constuctor
     BODY_EQUIVALENT & operator =(const BODY_EQUIVALENT &Src);
     void Set( int Num, ELEM_BODY_FULL &EBF );
     bool operator >(const BODY_EQUIVALENT &Frst) const;
     bool operator <(const BODY_EQUIVALENT &Frst) const;
     bool operator ==(const BODY_EQUIVALENT &Frst)const;

};

#pragma pack(pop)

#endif
