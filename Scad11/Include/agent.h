#ifndef AGENT_FLAG_H
#define AGENT_FLAG_H

#pragma pack(push,1)

#include <result.hpp>
#include <agentinf.h>
#include <litera.h>

struct MAX_MIN_INF {
		 double Value;
		 int   NumNode;
		 int   NumElem;
		 WORD  NumSection;
		 WORD  NumPunct;
		 WORD  Load;
		 char  NumForm[11];
		 };

class AGENT: MEMORY
{
public:
        RESULT     * Result;
        BYTE         QuantityStepNode;
        BYTE       * NumStepNode;
        FILEPRINT    Out;
        FILEWORK   * Work;
        short        TypePrint;

/*      паpаметpы печати               */
        BYTE         Level;
        BYTE         PrintRSN;
        BYTE         Precision;
        BYTE         ReportLang;
        double       PrecisionLimit;
        BYTE      *  LoadList;

        WORD         QuantityLoad;

    	BYTE      *  List;
	    BYTE      *  Mask;
	    WORD         NumPage;

	    BYTE         QuantityText;
	    BYTE         LengthTable;
	    char         Text[12][256];
	    WORD         QuantityGraf;
	    int          NumLast;
	    int          NumPrint[32];
      	WORD         TypeElem;
        BYTE         TypeInf;
     	DWORD        PosDiskFormat;
	    char         pN[64][6];
    	BYTE         TableShortYes;
    	BYTE         TableShortFE[501];
    	BYTE         NumName[64];
    	WORD         StepField;

    	MAX_MIN_INF  MaxSelect[64];
    	MAX_MIN_INF  MaxFull[64];
    	MAX_MIN_INF  MinSelect[64];
    	MAX_MIN_INF  MinFull[64];

        HEAD_USIL       HeadUsil;
        sn           SN;
    	double      * SysCoef;
        BOOL        (*ProgressAgent)(int);
        FE_FORMAT   Wfke, *FormElem;

    	AGENT() {  Init();  }
       ~AGENT(void) {  Delete();  }

inline void     Init() {  memset(this,0,sizeof(AGENT));	}
void   RESULT_EXPORT Delete();

void RESULT_EXPORT Agent( LPCSTR Lvl, RESULT &, BOOL (*Func)(int),
		 short TypeEdit, short TypePrnt, AGENT_INF &AgentInf,
		 PARAM_PRINT &ParamPrint  );

void  AgentInit( short TypeEdit, AGENT_INF &, PARAM_PRINT & );


void  Agent005();
void  AgentInit005(int NumMSG);
void  AgentList005(long *nsw);
int   Agent005n(long *nsw, int NumNode);
void  Agent005v(long *nsw, BYTE Size );
void  Agent005g(long *nsw, BYTE Size );
void  Agent005u();
void  Agent005p(short NumHead);
void  Agent005m(long *nsw);

void  Agent006();
void  AgentInit006(BYTE BegTable, DWORD &Pos);
void  Agent006v(DWORD Pos);
void  Agent006g(DWORD Pos);

void  Agent007();
void  AgentInit007(BYTE BegTable,DWORD &Pos);
void  Agent007v(DWORD Pos);
void  Agent007g(DWORD Pos);
void  Agent007u();

void  Agent008();
void  AgentInit008(DWORD &Pos);

void  Agent009();

void  Agent010();
void  AgentInit010();

void  Agent011();

void  Agent014();
void  AgentInit014(BYTE BegTable, DWORD &Pos);
void  Agent014ReadV(double *Us, int &kNus );
int   Agent014ReadG(double *Us, int &kNus );
void  Agent014v(DWORD Pos);
void  Agent014g(DWORD Pos);


void  Agent017();
void  Agent018();

void  Agent019();
void AgentList019v(FORMAT_POSITION *FormPosAg,double *rL,DWORD Pos,int ke);
void Agent019m(BYTE Type,int ke,WORD kq, double *rL, WORD *ListLoad);
void Agent019v(FORMAT_POSITION *FormPosAg,BYTE Type,int ke,WORD kq, double *rL, WORD *ListLoad);

void  Agent020();

void  Agent025();

//void Agent061();
void  Agent071();

void  AgentText(short NumText);
void  AgentLoadName();
int   AgentLoadTable(short YesFile,short Type);
void  AgentHeadText(int Quantity,char Text[][256]);
void  AgentPhrase(LPCSTR Text);
void  AgentLine();

void  AgentMaxMin(double r, BYTE NumType, int NumNode, WORD NumStrTableLoad );
int   AgentMaxMinEqual();
void  AgentMaxMinPrint(short NumHead,short NumPos,LPSTR *Frmt);

void  AgentEffortReadV( double *Us, BYTE Type);
void  AgentEffortReadG( double *Us, BYTE Type);
void  AgentEffortMaxMin( double Us[], BYTE Step);
void  AgentEffortMaxMin(double Us[], WORD NumStr, WORD QuantityStr,BYTE Step);
void  AgentMaxMinRead(double r,int NumNode, WORD NumStrTableLoad,MAX_MIN_INF *InpInf);
void  AgentUnitEffort();
void  AgentWarning();
RESURCE_INFORM * AGENT::InformLoad(int Num);
};

void  Separate(LPSTR Text,WORD Quantity, char Name[][6]);
void AgentHead(void *);
void AgentPageEnd(void *);

#pragma pack(pop)
#endif
