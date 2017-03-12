#ifndef SPECTR_FLAG_H
#define SPECTR_FLAG_H
#pragma pack(push,1)

#include <result.hpp>
//#include <inp_doc.h>
//#include <inp_def.h>

#include <sg_dyn1.h>
#include <math.h>

struct LOAD_INFORM
{
	WORD      NumLoad;
	BYTE      Ort;
	WORD      NumAksel;
	WORD      QuantityForm;
	LONGLONG  PosVector;
	LONGLONG  PosValue;
};

struct SPECTR_INFORM {
	WORD      NumLoad;
	BYTE      Ort;
	WORD      NumAksel;
	int       NumNode;
	int       QuantityOften;
	LONGLONG  PosOften;
};

struct TYPE_SPECTR {
	BYTE     Type;
	double   Value;
	double   Often;
};

class SPECTR : public MEMORY
{
public:

	short           Ort[3];
	double          CoefDis;
	int             QuantityLoad;
	int             QuantityNode;
	int             QuantityCoefDemp;

    int           * NumLoad;
	int           * ListNode;
	double        * CoefDempf;

	int             QuantityLoadDyn;
	int           * NumLoadDyn;
    
	int             QuantityStrLoad;     
	LOAD_INFORM   * LoadInf;

	SPECTR_INFORM * SpectrInform;

	int             QuantityPunct; //  данные акселерограммы
	double          DeltaTime;
	double          Time;
	double        * ValueAksel;

	char            End; 

    RESULT        * Res; 

	OBJECT_STRING   NameAxsel;	
	MESSAGE         Message;
	FILEWORK        FileRes;

    SPECTR()	{  Init();	};
   ~SPECTR()	{  Delete();	};

	void Init() {	ZeroMemory(Ort,(LPSTR)&End-(LPSTR)&Ort);  };

	void Delete();
	int  Init( RESULT & );

	void Spectr();

	void SetNumNode(int Qntt, int* List);

	void SpectrOut();

	int  ReadAksel(LPCSTR Name);

	void SpectrPrint(LPCSTR FileNameForm);

	void SpectrPrint();

    void Read( ); 
    void Write( ); 

};

void Separate(LPSTR Text, WORD Quantity, char Name[][6]);

//void FilePath(HINSTANCE hInst,LPCSTR Name,LPSTR Path);

void Row(double DeltaTime, WORD QuantityPunct, double* Value, WORD QuantityForm,
	double* AmplitudeSin, double* AmplitudeCos, double Eps);

void Solution( double DeltaTime, int QuantityPunct, double* ValueIn,
	double Omega, double Ksi, double Kappa, double* ValueOut);

void PutRunst(short Proc);

#pragma pack(pop)
#endif
