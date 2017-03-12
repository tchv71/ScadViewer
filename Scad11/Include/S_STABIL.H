#ifndef S_STABIL_FLAG_H
#define S_STABIL_FLAG_H
#pragma pack(push,1)

struct dlg_stab
{
	char   StabRSN;			//  0 - считать загружения, 1 - считать комбинации
	char   CoeffStab;		//  вычисление коэффициентов
	char   ModeStab;		//  вычисление форм
	char   LongFlam;		//  вычисление свободных длин
    char   ListLoad;        //  0 - все загружения, 1 - из списка 
	char   TypeFixedLoad;   //  тип фиксированного загружения. 0 - загружение, 1 - комбинация
	WORD   NumFixedLoad;    //  номер фиксированного загружения

	double Lambda;			//  верхняя граница поиска
	double Epsilon;			//  нижняя граница поиска и точность оценки интервала

    char   Res2[16];

	BYTE   NumLoad[MAX_SCHEMA_LOAD/8];    //  в бит номера загружения(комбинации) признак вычисления

};

struct dlg_stab_old
{
	char   StabRSN;
	char   CoeffStab;
	char   ModeStab;
	char   LongFlam;
	float  Lambda;
	float  Epsilon;
	short  kq;
	short  kqComb;
	short *load;
	char  *loadnames;
};

struct HEAD_STABIL
{
	BYTE Type;  	//  тип: загружения или комбинации
	BYTE ModeStab;
	BYTE FreeLine;
	WORD QuantityLoad;
	float Lambda;
	float Epsilon;

	BYTE DIM;   	/* Dimention of the scheme (2D or 3D)  FreeLine   */
	WORD KE;		/* Quantity of elements 	 FreeLine   		  */
	WORD KQ;		/* Quantity of loads		 FreeLine   		  */
	LONGLONG AdrLoads;
	LONGLONG AdrFreeLine;
	BYTE Reserv[14];
};

struct s_stabil
{
	WORD NQ;   		       // Load number  					 
	BYTE FLAG; 		       // 0 - stability has not been tested 
	                       // 1 - stability factor OK  		 
	                       // 2 - stability > MAX_LAMBDA   	 
	                       // 3 - absolute stability   		 
	                       // 4 - LAMBDA < Eps 				 
	BYTE MODE;  		   // stability mode calculed  		 
	double   LAMBDA;       // stability factor 				 
	LONGLONG mode_adr; 	   // address of mode in F16  		  
	WORD     NumFixedStep; //  для нелинейного процесса
	WORD     Res[3];
};

#pragma pack(pop)
#endif
