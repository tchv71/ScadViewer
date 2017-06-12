#ifndef MODEL_FLAG_H
#define MODEL_FLAG_H

#include "SvTypes.h"
//enum TColor {clMin=-0x7fffffff-1, clMax=0x7fffffff};
typedef UINT	TColor;

struct S3dPoint
{
	S3dPoint(): x(0), y(0), z(0)
	{};
	S3dPoint(FLOAT_TYPE ax, FLOAT_TYPE ay, FLOAT_TYPE az) : x(ax), y(ay), z(az) {};
	FLOAT_TYPE	x;
	FLOAT_TYPE	y;
	FLOAT_TYPE	z;
};

/*
struct TVertexArray
{
	int			NumPoints;			// Количество вершин (в т.ч. фиктивные)
	S3dPoint	*Vertexs;			// Массив координат вершин
	TVertexArray()
	:
	Vertexs(NULL),
	NumPoints(0)
	{
	};
	TVertexArray(TVertexArray * V)
	{
		NumPoints = V->NumPoints;
		Vertexs = new S3dPoint[NumPoints];
		memcpy(Vertexs, V->Vertexs, sizeof(S3dPoint) * NumPoints);
	};
	~TVertexArray()
	{
		delete[] Vertexs;
	};
};
*/

typedef byte	TElemType;		// {EL_LINE =1,EL_TRIANGLE,EL_QUAD};  // Тип примитива отрисовки
const byte		EL_LINE = 0;
const byte		EL_TRIANGLE = 1;
const byte		EL_QUAD = 2;
const byte      EL_UNKNOWN = 100;

enum TOrgElemType // Оригинальный тип элемента
{
	EL_BAR   = 1,
	EL_PLATE = 2,
	EL_SOLID = 3,
	EL_SLAB  = 4,
	EL_WALL	 = 5,
	EL_ROOF  = 6,
	EL_COLUMN = 7,
	EL_BEAM = 8,
	EL_ISO
};

//#pragma pack(1)
struct SElement
{
	TElemType		Type;			// Тип примитива отрисовки
	TOrgElemType	OrgType;		// Оригинальный тип элемента
    NUM_ELEM_TYPE	NumElem;        // Номер элемента
	TColor			Color;			// Цвет примитива отрисовки
	TColor			OriginalColor;
	size_t			Points[4];		// Номера вершин примитива

    // ************ Methods ***************

	int				NumVertexs(void) const
	{
         return int(Type) + 2;
    };

/*
    bool SElement::IsValid(int nMaxVertexs)
    {
        for (int i=0; i<NumVertexs(); i++)
            if (Points[i]<0 || Points[i] >= nMaxVertexs)
                return false;

        if (Type > EL_QUAD)
            return false;

        if (OrgType > EL_SOLID)
            return false;

        return true;
    }
*/

};
/*
struct SElementArray
{
	SElementArray()
	:
	NumElements(0),
	Elements(NULL)
	{
	}
	int			NumElements;		// Количество примитивов
	SElement	*Elements;			// Массив примитивов
	SElementArray(SElementArray * V)
	{
		NumElements = V->NumElements;
		Elements = new SElement[NumElements];
		memcpy(Elements, V->Elements, sizeof(SElement) * NumElements);
	};
	~SElementArray()
	{
		delete[] Elements;
	};
};
*/

// Флаги "настоящих" вершин
#define VF_DELETED	128
/*
struct TGeometry
{
	TVertexArray	*VertexArray;	// Ссылка на вершины
	SElementArray	*ElementArray;	// Ссылка на примитивы

	// Добавлено для удобства, не передается через GetGeometry
	int				NumRealVertexs; // Количество "настоящих" вершин
	byte			*VertexFlag;	// Массив флагов "настоящих" вершин

    // Check for schema consistence
    static bool            ThrowBadElements(SElement *pElements, int &nElements, int nVertexs, unsigned cbElement = sizeof(SElement));
};
*/
#endif
