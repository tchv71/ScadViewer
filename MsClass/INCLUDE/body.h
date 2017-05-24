#pragma pack(push, 1)
struct DECART {
	float x, y, z;
};

struct ELEM_BODY {
	WORD NumElem;
	BYTE Type;  /* 1-4 - n - узловой                            */
	/*  5  - 3-x узловой, пpоециpующийся в отpезок  */
	/*  6  - 3-x узловой, пpоециpующийся в отpезок  */
	BYTE DifferNode;   
	long Node[4];
};

struct LOOK_BODY {
	
	ELEM_BODY       * ElemBody;
	DWORD             QuantityElemBody;
	double            MK[3][3];
	BYTE              TypeBase;
	long            * Order;
	
	BYTE              TypeProfile;
	BYTE              TypePlate;
	BYTE              FragmParam;
	BYTE              Fragm;
	BYTE              DeleteProcess;
	BYTE              Res[3];
	WORD              QuantityElemMask;
	BYTE            * MaskElem;  /* Маска фрагмента                               */
	BYTE            * MaskFragm;  /* Маска фрагмента                               */
	
	DWORD             QuantityNodeBody;
	CK              * Coord;      /* Кооpдинаты дополнительных узлов для профилей  */
	GrafCK          * GrafCoord;  /* Гpафические кооpдинаты дополнительных узлов для профилей */
	float             DelProfile; /*  отступы при отображении профилей  */
	
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
	ELEM_BODY_GEOM * pEBG;
	BYTE        QuantityLine;
	LINE_BODY   LineBody[4];
	float Eps;
};

#define  EPSILON   1e-4
#pragma pack(pop)
