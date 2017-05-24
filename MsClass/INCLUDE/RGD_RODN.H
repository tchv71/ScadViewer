 /*   tags of structures    */
#pragma pack(push, 1)

  struct D3NROD  {
		  struct PLACE sss;
		  struct { short nphd; short kphd; } hd;
		  struct PLACE sg;
		  struct PLACE sga;
		  struct PLACE ssa;
		  struct PLACE po;
		  short nkx;
		  float eps;
		  short nim;
		  short nres[3];
		  float metrcm;
		  float fres;
		  } *pd3n;

#define SSS    pd3n->sss
#define NSS    pd3n->sss.ns
#define NPSS   pd3n->sss.np
#define KZSS   pd3n->sss.kz
#define NPHD   pd3n->hd.nphd
#define KPHD   pd3n->hd.kphd
#define SG     pd3n->sg
#define NSG    pd3n->sg.ns
#define NPSG   pd3n->sg.np
#define KZSG   pd3n->sg.kz
#define SGA    pd3n->sga
#define NGA    pd3n->sga.ns
#define NPGA   pd3n->sga.np
#define KZGA   pd3n->sga.kz
#define SSA    pd3n->ssa
#define NSA    pd3n->ssa.ns
#define NPSA   pd3n->ssa.np
#define KZSA   pd3n->ssa.kz
#define PO     pd3n->po 
#define NPO    pd3n->po.ns
#define NPPO   pd3n->po.np
#define KZPO   pd3n->po.kz
#define EPS    pd3n->eps
#define NKX    pd3n->nkx
#define NIM    pd3n->nim
#define METRCM  pd3n->metrcm

  struct def { double ex, vxx, wxx; };

  struct dsr { double dyi;
	       double dzi;
	       short pim;
	       double pli;
	       double dy;
	       double dz;  } ;

#pragma pack(pop)
