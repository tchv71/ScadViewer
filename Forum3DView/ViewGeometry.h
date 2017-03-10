// Portions copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
#ifndef ViewGeometryH
#define ViewGeometryH
#include "Model.h"
#include "Rotate.h"
#include "3DVector.h"
#include <vector>
#include "Renderer.h"
#include <set>
typedef ptrdiff_t NODE_NUM_TYPE;
typedef unsigned SCUINT32;

typedef int SC3DRetCode;

#define	S3DRC_OK	0

#define	S3DRC_ERR						-1
#define	S3DRC_ERR_INVALID_ARG			-2
#define	S3DRC_ERR_OUT_OF_MEM			-3
#define	S3DRC_ERR_MTR_DONT_INVERSE		-4
#define	S3DRC_ERR_MATERIAL_ABSENT		-5
#define	S3DRC_ERR_LIGHT_ABSENT			-6
#define	S3DRC_ERR_MODEL_ABSENT			-7
#define	S3DRC_ERR_MODEL_REINIT			-8
#define	S3DRC_ERR_INCOMPABILITY			-9
#define	S3DRC_ERR_MODEL_UNINIT			-10
#define	S3DRC_ERR_MODEL_UNUPDATABLE		-11
#define	S3DRC_ERR_INVALID_IND			-12
#define	S3DRC_ERR_DCMGR_UNINIT			-13
#define	S3DRC_ERR_DCMGR_REINIT			-14
#define	S3DRC_ERR_DC_ABSENT				-15
#define	S3DRC_ERR_DCMGR_INIT			-16
#define	S3DRC_ERR_DC_NOT_INIT			-17

#define	S3DRC_ERR_NOT_IMPL				-256


#define	S3DRC_WRN				1
#define	S3DRC_FIN_ITERATION		2
#define	S3DRC_BREAK_RENDERING	3
#define	S3DRC_REPEAT_RENDERING	4
#define	S3DRC_IMAGE_NOT_ACCESS	5


struct SLineStripRec
{
	NODE_NUM_TYPE Vertex;

	//  FLOAT_TYPE x,y,z;
};


#define CASHE_VECTORS
typedef C3DVector<FLOAT_TYPE> CVectorType;

struct SViewCasheNode
{
	NODE_NUM_TYPE	SecondNode;
	bool			Drawed;
	DWORD_PTR       Next;
#ifdef CASHE_VECTORS
	CVectorType		v;
#endif
};

//typedef S3dPoint TVertex;
struct SViewVertex : public S3dPoint
{
	SViewVertex(): FragmentFlag(true), Flag(0), nMainVertex(0)
	{};
	SViewVertex(const S3dPoint &p) : S3dPoint(p), FragmentFlag(true), Flag(0), nMainVertex(-1) {};
public:
	bool	FragmentFlag;
	byte	Flag;
	NODE_NUM_TYPE		nMainVertex; // Номер вершины, из которой эта вершина была порожена при применении профиля стержней
						 //  -1, если такой нет
};

struct SViewFactorVertex : public SViewVertex
{
	SViewFactorVertex(const SViewVertex& v)
	{
		memcpy(this, &v, sizeof(SViewVertex));
	};
	SViewFactorVertex(): fFactor(0), clr(0), nElement(0), nVertex(0), nVertexIndex(0)
	{
	};

		
public:
	double	fFactor;
	COLORREF	clr;
	NODE_NUM_TYPE		nElement;		// element number for this vertex (-1 for common vertex)
	NODE_NUM_TYPE		nVertex;
	byte	nVertexIndex;	// Vertex number (relative to the element)
};

enum ECutType { CUT, INV_CUT, HIDE_ELEMENT, HIDE_ELEMENT_PLATE, SHOW_ELEMENT_PLATE };

struct SCutRecord
{
	ECutType	Type;
	FLOAT_TYPE		x1, y1, x2, y2;
	CRotator	Rot;
	SCutRecord	*Next;
	NUM_ELEM_TYPE		NumEl;
};

class CViewElement : public SElement
{
public:
	bool			FragmentFlag;
	bool			DrawFlag;
	bool			bContoured;
	bool			bContourOnly; // Draw only the contour of this element
	int				NumVertexs(void) const	{ return int(Type) + 2; };
	CVectorType		Norm;
    CVectorType     OrgNorm;    // Normal to original element without profile or thickness
	void __fastcall SetNormal(SViewVertex *Vertexs);
	CViewElement(const SElement &OldElem);
	CViewElement();
	CViewElement(TColor color);

	// This element is actually a contour of forum objects
	bool IsContour() const
	{
		return Type == EL_LINE && (int(OrgType) > EL_SOLID) && !IsBarLike();
	}
	bool IsBarLike() const
	{
		return OrgType == EL_BAR || OrgType == EL_COLUMN || OrgType == EL_BEAM || OrgType == EL_ISO;
	}
	size_t		m_nExtraPoints; // смещение в массиве  CViewGeometry::m_vecExtraPoints
									// там:
									// {Общее количество узлов; Доп. точка1;...; Доп. точка k}
									//  k - количество доп. точек
};


/*
template<class T>
class TArray // : public SElementArray 
{
public:
	TArray():	NumElements(0),	Elements(nullptr)
	{
	}
	TArray (TArray &V)
	{
		NumElements = V.size();
		Elements = new T[NumElements];
		memcpy(Elements, &V[0], sizeof(T) * NumElements);
	};
	void reserve(int n)
	{
		delete[] Elements;
		Elements = new T[n];
		NumElements = n;
	}

	~TArray()
	{
		delete[] Elements;
	};
	int size() { return NumElements; }
	T& operator[](int nIndex) { return Elements[nIndex]; }
	T* GetVector() { return Elements; }
	void resize(int nNewSize) { NumElements = nNewSize; }
private:
	int			NumElements;	// Количество примитивов
	T			*Elements;  // Массив примитивов
};
*/

//typedef TArray<SViewVertex> CViewVertexArray;
//typedef TArray<CViewElement> CViewElementArray;
class CViewElementArray : public std::vector <CViewElement>
{
public:
	CViewElementArray(): m_SelElOrgType()
	{
		m_nNumElSelected = 0;
	}
	CViewElement * GetVector() { return size()>0?&(operator[](0)):nullptr; }
	int GetMaxElemID()
	{
		int nMaxRealElemNum = -1;
        for(UINT i = 0; i < size(); i++)
		{
			CViewElement &El = at(i);
			if (El.NumElem > nMaxRealElemNum)
				nMaxRealElemNum = El.NumElem;
		}
		return nMaxRealElemNum;
	}
	void UnselectElements()
	{
		m_nNumElSelected = 0;
	}
	void SelectElement(NUM_ELEM_TYPE NumElem)
	{
		m_nNumElSelected = NumElem;
		m_SelElOrgType = TOrgElemType(0);
        for(UINT i = 0; i < size(); i++)
		{
			CViewElement &El = at(i);
			if (El.NumElem == NumElem)
			{
				m_SelElOrgType = El.OrgType;
				break;
			}
		}
	}
	NUM_ELEM_TYPE GetSelectedElement() const
	{
		return m_nNumElSelected;
	}
	TOrgElemType GetSelElemOrgType() const
	{
		return m_SelElOrgType;
	}
protected:
	NUM_ELEM_TYPE m_nNumElSelected;
	TOrgElemType m_SelElOrgType;
};
class CViewVertexArray : public std::vector <SViewVertex>
{
public:
	SViewVertex * GetVector() { return size()>0?&(operator[](0)):nullptr; }
};

typedef  std::vector<SViewFactorVertex> CViewFactorArray;
/*
class CViewVertexArray : public TVertexArray
{
public:
	SViewVertex *Vertexs;
};
*/
#ifdef SCAD21
#include "SCADAPIX.hxx"

typedef APIHandle_tag SCHEMA; 
#else
class SCHEMA;
#endif
struct SSortVertex : public S3dPoint
{
	int N;
};

struct SModelInfo
{
	SModelInfo() :	m_nNodeCount(0), m_nElementCount(0)
	{
	};
	int m_nNodeCount;
	int m_nElementCount;
};

struct SAxe
{
	FLOAT_TYPE m_pos;
	CString	   m_name;
};

typedef std::vector<SAxe>  TAxeSet;

struct SAxes
{
	TAxeSet X;
	TAxeSet Y;
	TAxeSet Z;
};

class CViewGeometry;

class INodeCashe
{
public:
	virtual void 	Clear(void) = 0;
	virtual void 	SetupLineStrips() =0;
	virtual bool 	WasDrawed(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2)=0;
	virtual void 	Recreate(void)=0;
	virtual void	Construct(void)=0;
	virtual SLineStripRec* Strips(int n) = 0;
	virtual ~INodeCashe() {};

};
class CCutter;

class IModelDraw
{
public:
	virtual ~IModelDraw()
	{
	}

private:
	virtual void		Render(IFemRenderer *pRenderer, SViewOptions *pViewOptions, CDrawOptions *pDrawOptions) =0;
	virtual void		OnDrawScene(IFemRenderer *pRenderer, SViewOptions *pViewOptions, CDrawOptions *pDrawOptions,SPerspectiveView&	ViewPos) =0;
	virtual INodeCashe* GetNodeCashe() = 0;
	virtual void		PerformCut(CCutter& rCutter, SCutRecord *r) = 0;
	virtual void		DrawOptionsChanged(CDrawOptions *DrawOptions, bool bShowUsedNodes)=0;
	virtual bool		IsIso() const =0;
};

class IGeomCut
{
public:
	virtual ~IGeomCut()
	{
	}

private:
	virtual void PerformCut(CCutter& rCutter, SCutRecord *r)=0;
	virtual void ClearCut(void)=0;
};

class CNodeCashe : public INodeCashe
{
public:
	CNodeCashe(CViewGeometry *pGeom, bool bCheckStraitLines) :
		m_bCheckStraitLines(bCheckStraitLines),
		m_pGeom(pGeom)
	{
		CNodeCashe::Construct();	
	};
	virtual ~CNodeCashe()
	{
		Destroy();
	}

	void	Construct(void) override;
	void 	Clear(void) override;
	bool 	WasDrawed(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2) override;
	bool __fastcall	WasDrawed1(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2);

	void 	Recreate(void) override
	{
		Destroy();
		Construct();
		SetupLineStrips();
	};

protected:
	void 	SetupLineStrips() override;

	SLineStripRec* Strips(int n) override
	{ return UINT(n)<LineStrips.size() ? &LineStrips[n] : nullptr; };
	void				SetVertex(NODE_NUM_TYPE N);
	void				SetBarsDrawed(void);
	void				Destroy(void);
	void __fastcall		AddCacheElement(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2);
	void __fastcall		AddCacheElement1(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2);
	std::vector<SViewCasheNode> vecCashe;
	std::vector<SLineStripRec> LineStrips;
	bool m_bCheckStraitLines;
	CViewGeometry*	m_pGeom;
};

class CViewGeometry : public IModelDraw, public IGeomCut
{
// Methods
public:
	CViewGeometry() :
		m_bDeleteInnerPlates(false),
		m_bForThumbs(false),
		m_bOptimize(false),
		m_pFlatGeometry(nullptr),
		NumRealVertexs(0),
		m_bShowUsedNodes(false),
		m_bForumGeometry(false),
		m_pNodeCashe(nullptr)

	{
	}
	virtual ~CViewGeometry(void);

	void SetElColor(CViewElement& el, const struct SViewOptions* pOptions, EDrawMode Mode) const;
	// IModelDraw implementation
	void Render(IFemRenderer *pRenderer, SViewOptions *pViewOptions, CDrawOptions *pDrawOptions) override;
	void OnDrawScene(IFemRenderer *pRenderer, SViewOptions *pViewOptions, CDrawOptions *pDrawOptions, SPerspectiveView& riewPos) override;
	INodeCashe* GetNodeCashe() override;
	virtual void SetupElementColors(const struct SViewOptions* pOptions, EDrawMode Mode) ;
	virtual void  DrawOptionsChanged(CDrawOptions *DrawOptions, bool bShowUsedNodes) override;
	virtual bool  IsIso() const override { return false; }
	virtual CString Format(double val) const  {return CString();};

	// IGeomCut interface
	virtual void PerformCut(CCutter& rCutter, SCutRecord *r) override;
	virtual void ClearCut(void) override;

	bool LoadFromSchema(SCHEMA *Schem, BYTE TypeProfile, BYTE TypePlate, bool bOptimize = true);
	bool LoadFromFile(LPCTSTR PathName, BYTE TypeProfile, BYTE TypePlate,  bool bOptimize = true, SCHEMA ** ppSchem = nullptr);

	void ExportToDxf(LPCTSTR szFileName);
	void __fastcall		SetupNormals(void);

	virtual void Get3DBox(const CRotator *Rot, S3DBox *Box, CViewVertexArray	*pVertexArray = nullptr);
	void GetMax3DBox(const CRotator *Rot, S3DBox *Box);
	void SetupAndOptimize(bool bReduceGeometry);

	bool	m_bDeleteInnerPlates;
	bool	m_bForThumbs;
	bool	m_bOptimize;
	bool   IsElDuplicated(NUM_ELEM_TYPE nEl) const
	{
		return m_DuplicatedElements.count(nEl)!=0;
	}
	bool IsForumGeometry() const
	{
		return m_bForumGeometry;
	}

public: // Fields
	SModelInfo m_ModelInfo;
	CViewGeometry		*m_pFlatGeometry; // Geometry without profiles and thickness
	size_t					NumRealVertexs; // Количество "настоящих" вершин
	CViewElementArray	ElementArray;
	CViewVertexArray	VertexArray;
	SAxes m_Axes;
	S3DBox m_FragmentBox;
protected:
	std::vector<NODE_NUM_TYPE> m_vecExtraPoints;	// {Общее количество узлов; Доп. точка1;...; Доп. точка k}
									//  k - количество доп. точек

	void RecreateCashe(void) const;
protected:
	class SSortElement : public SElement
	{
public:
		NODE_NUM_TYPE N;
	};
	void __fastcall		DeleteEqualNodes();
	void __fastcall		DeleteEqualElements();
	void LoadAxesInfo(SCHEMA *Schem);
	std::set<NUM_ELEM_TYPE> m_DuplicatedElements;
	void DeleteNondrawableElements();
	bool m_bShowUsedNodes;
	bool m_bForumGeometry;
	void CorrectVertexVisibility();
	virtual void PostProcessSchema(SCHEMA *m_Project, bool bExpandProfiles, bool bExpandPlates) {};
	virtual TOrgElemType GetElemOrgType(WORD wTypeElem);
	INodeCashe* m_pNodeCashe;
};


// Определение различий между ScadViewer и PipeViewer
NODE_NUM_TYPE NUM(NODE_NUM_TYPE x);
#define N_S(x)	NUM_RECODE[x]
extern const NODE_NUM_TYPE	NUM_RECODE[];



//---------------------------------------------------------------------------
#endif
