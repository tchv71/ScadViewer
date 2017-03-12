#ifndef RSU_FLAG_H
#define RSU_FLAG_H
#pragma pack(push,1)

struct S_SECD8
{
	short ityp;        	// type    of the load    	
	short igob;        	// groups obied-ia  loads 	
	short iznp;        	// variable sign          	
	short ivizr[2];    	// incompatible  vz-isk   	
	short isopr[2];    	// soputstvuechhie        	
	char  iprr[2];
	float pk;           // overload factor  peregruzka  
	float pkd;          // long operation factor      	
	float pk1[16];    	// koef-s  rsu     88 byte      

	WORD  NumLoad;    	// number of load               
    WORD  NumBegSumUs;     // номер строки начала данных в суммарных усилий 
    WORD  QuantityStringSum;  // число строк суммарных усилий для загружения 

    WORD  NumStringCrit[204];  //  номера строк критериев

	char  ipr[2];      	// vybor                        
	short isop[2];          // soot.isopr                   
	short iviz[2];     	// soot.ivizr                   
    short sRes;

    double zkro;            	// primary criterion 		
	double zkr1;            	// criterion 1-oj sop. 		
	double zkr2;            	// """"""""  2-oj sop. 		
	double zkrs;            	// summary criterion 		
	double pkr;	 	// working factor		
};

struct sup_sc1
{
	short punf;    // priznak unifik. 				
	short ksfd8;   // kol-vo strok SecD8(sformirov.) 	        
	short QuantitySumUs;   /* kol-vo strok суммарное усилий	        */
	short kqr;     // kol-vo prav. parti 				
	short kzg;     // kol-vo zagr. ! kol-vo strok dok8(isxod.) 	
	short iqaiqa;
};

struct strsc2
{
	short kkn16;   // stroka 16 dok0 				
	short ktn16;   // stroka 16 dok0 				
	short kkn8;    // dok8   					
	short ktn8;    // dok8   					
	short kgo;     // kol. grupp union  2-stolbetz dok8 	
	short kvz;     // kol. groupp vz. 4-stolbetz dok8 	
	char  nvz2[2]; // 2-2vz,3-nsop,4-typ>2,5-typ=0 b 		
	short kspk1 ;  // kol. pkr  				
};

struct opsvkt
{
	double sumvkt;
	double vkft[MAX_SCHEMA_LOAD+1];
	short numvkt;
	short numskt;
	short sRes[2];
};

struct opsvk
{
	double sumvk;
	double vkf[MAX_SCHEMA_LOAD+1];
	short numvk;
	short numsk;
	short sRes[2];
};

struct  S_SECRS
{
	short  nvkrs;   	// numvkt 		
	short  nvsrs;   	// numskt 		
	short  icr;
	short  isei;
	double vnpr;    	// sumvk 		
	char   nvz[MAX_SCHEMA_LOAD/8+4]; 	// (1024+4*8) bit(1),		
	int    lh2;         // nomer el-ta 		
	short  iqs;         // nomer sechenia  	
	short  iqq;         // nomer stroku us 	
	char   lh1[2];      // num sloy obl		
	LONGLONG PosPrint;
};// 200 

struct RSU_FE 
{
        BYTE  * ElemRSU;   //  список элементов для РСУ
        BYTE  * TypeUnif;
        WORD  * GroupUnif;
        WORD  * GrafRSU;
        WORD  * GrafRSU2;  //  для старых

		WORD    ProcElemRSU;
        BYTE    TypeUnifElem;
        WORD    GroupUnifElem;
        WORD    GrafElemRSU;
        WORD    GrafElemRSU2;
};

struct s_dok8
{
	short typ;
	short gob;
	short znp;
	short viz[2];
	short sop[2];
	short ipr;
	float pk;
	float pkd;
	float pk1[16];
};

#pragma pack(pop)
#endif
