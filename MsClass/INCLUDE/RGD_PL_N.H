#pragma pack(push, 1)
		  /*   tags of structures for flat FE NEUD   */
  struct D3NPLATE {
		  double ungb, kpu, unga;
		  struct PLACE sg; 
		  struct PLACE sga;
		  struct PLACE ssa;
		  struct PLACE sml;
		  struct PLACE stn;
		  struct shd  {  short nphd; short kzhd;  } shd;
		  float eps;
		  short nkx;
		  short nop;
		  short nap;
		  short kdh;
		  short nres;
		  double rez1;
		  float metrcm;
		  float  res3;    };

#define UNGB  pd3n->ungb
#define KPU   pd3n->kpu
#define SG    pd3n->sg
#define NSG   pd3n->sg.ns
#define NPSG  pd3n->sg.np
#define KZSG  pd3n->sg.kz
#define SGA   pd3n->sga
#define NGA   pd3n->sga.ns
#define NPGA  pd3n->sga.np
#define KZGA  pd3n->sga.kz
#define SSA   pd3n->ssa
#define NSA   pd3n->ssa.ns
#define NPSA  pd3n->ssa.np
#define KZSA  pd3n->ssa.kz
#define SML   pd3n->sml
#define NML   pd3n->sml.ns
#define NPML  pd3n->sml.np
#define KZML  pd3n->sml.kz
#define STN   pd3n->stn
#define NTN   pd3n->stn.ns
#define NPTN  pd3n->stn.np
#define KZTN  pd3n->stn.kz
#define NPHD  pd3n->shd.nphd
#define KZHD  pd3n->shd.kzhd
#define UNGA  pd3n->unga
#define EPS   pd3n->eps
#define NKX   pd3n->nkx
#define NOP   pd3n->nop
#define NAP   pd3n->nap
#define KDH   pd3n->kdh
#define NRES  pd3n->nres
#define METRCM  pd3n->metrcm

#pragma pack(pop)
