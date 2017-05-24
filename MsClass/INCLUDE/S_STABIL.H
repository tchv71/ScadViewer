#ifndef S_STABIL_FLAG_H
#define S_STABIL_FLAG_H
#pragma pack(push, 1)

struct dlg_stab
{
	char  StabRSN;
	char  CoeffStab;
	char  ModeStab;
	char  LongFlam;
	float Lambda;
	float Epsilon;
	short kq;
	short kqComb;
	short *load;
	char  *loadnames;
};

struct HEAD_STABIL
{
        BYTE  Type;      //  тип: загружения или комбинации
        BYTE  ModeStab; 
        BYTE  FreeLine; 
        WORD  QuantityLoad;
	float Lambda;
	float Epsilon;
        
        BYTE  DIM;       /* Dimention of the scheme (2D or 3D)  FreeLine   */
	WORD  KE;        /* Quantity of elements      FreeLine             */
	WORD  KQ;        /* Quantity of loads         FreeLine             */
        DWORD AdrLoads;
        DWORD AdrFreeLine;
        BYTE  Reserv[14];

};

struct s_stabil
{
	WORD     NQ;   		/* Load number                       */
	BYTE     FLAG; 		/* 0 - stability has not been tested */
	               		/* 1 - stability factor OK           */
	                 	/* 2 - stability > MAX_LAMBDA        */
	                 	/* 3 - absolute stability            */
	                 	/* 4 - LAMBDA < Eps                  */
        BYTE     MODE;          /* stability mode calculed           */
	double   LAMBDA;    	/* stability factor                  */
	DWORD    mode_adr;      /* address of mode in F16            */
};

#pragma pack(pop)
#endif
