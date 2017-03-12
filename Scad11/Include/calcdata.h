#ifndef CALC_DATA__H
#define CALC_DATA__H
#pragma pack(push,1)

#include <fe_form.h>
#include <sg_dyn1.h>

struct CALC_DATA
{
   char       Ident[8];
   WORD       Length;          // Длина CTG
   WORD       Version;

   FILE_MARK  FileMark[100];   //  Контроль при открытии

   BYTE       TypeProcess;

   int        QuantityElem;    // Количество элементов
   int        QuantityNode;    // Число узлов

   int        MaxLayer;        // Максимальное число слоев в многослойках
   int        QuantityLinkFE;     // Link FE 
   BYTE       YesZEL;          // null elem yes
   BYTE       QuantityElemStep;  // В схеме есть шаговые элементы

   WORD       QuantityLoad;    // Число статических загружений
   WORD       QuantityLoadDyn;

   WORD       QuantityForce;   // Количество правых частей
   WORD       QuantityLoading; // Количество перемещений и усилий
   WORD       MaxFormLoad;     // Мак. заказанное число форм 
   int        SumQuantityForm;
  

   int        OrderDispl;      // Порядок вектора перемещений
   int        OrderSystem;     // Порядок системы
   int        OrderSE;         // Порядок суперєлемента

   int        HSystem;         // Ширина ленты
   int        HElem;           // Номер H-элемента

   int        MaxLenFormat;    // len format
   int        MaxLenAddFormat; // len format
   int        MaxQuantityValue;// max числовых характеристик местн.нагр.

   BYTE       MODE;             //  модальный  анализ, модуль 100
   BYTE       YesTimeHistory;      //  модуль 101

   BYTE       TypeSolver;       //  метод решения системы уравнений

   BYTE       YesAvtoMass;      // ???????

   WORD       MaxNodeElem;
   WORD       MaxKD;
   WORD       MaxSechOut;
   WORD       MaxKN;
   WORD       MaxKR;
   int        MaxKDxKN;
   int        MaxKG;
   WORD       MaxKNLitera;
   DWORD      MaxLengthEq;

   BYTE       WorkStep;         // позиция выполнения

   int        NumLineMatr;      //  точка прерывания при составлении матрицы

   BYTE       YesData;
   BYTE       YesOptimize;
   BYTE       YesMatr;
   BYTE       YesGauss;         // Прошел прямой ход Гаусса
   BYTE       YesStartVector;
   BYTE       YesMass;
   BYTE       YesForm;
   int        MaxForm;          // Макс. вычисленное число форм

   BYTE       YesDynForce;
   BYTE       YesForce;
   BYTE       YesDisplace;
   BYTE       YesEffors;

   BYTE       YesRSU;
   WORD       QuantityGroupUnific;

   BYTE       YesNewRSU;

   BYTE       YesComb;
   WORD       QuantityComb;

   BYTE       YesStab;

   BYTE       YesStabCoef;
   BYTE       YesStabForm;
   BYTE       YesRodFree;
   BYTE       YesStabCoefComb;
   BYTE       YesStabFormComb;
   BYTE       YesRodFreeComb;

   BYTE       YesFragment;
   BYTE       YesLitera;
   BYTE       NusLitera[8];
   BYTE       NoStartVector;

   BYTE       YesDestruction;

   BYTE       YesRes[9];

   BYTE       NullStringMatrize;
   BYTE       GIS;

   DOCUMENT_LONG   Format;
   DOCUMENT_LONG   Doc05;

   DOCUMENT_LONG   DocWork;
   DOCUMENT_LONG   HeadDispl;
   DOCUMENT_LONG   PositionEffors;
   DOCUMENT_LONG   PositionEfforsComb;
   DOCUMENT_LONG   DocUnite;
   DOCUMENT_LONG   FormStep;
   DOCUMENT_LONG   DocR02;
   DOCUMENT_LONG   DocR03;

   LONGLONG        AdrNewNumber;     // адрес номеров неизвестных после оптимизации
   LONGLONG        AdrProfMatr;      //
   LONGLONG        AdrFormPos;       // adrel
   LONGLONG        PosGaussWork;     // Позиции состояния прямого хода
   LONGLONG        LenGaussWork;     // длина
   LONGLONG        AdrPosEquation;   // Позиции уравнений в матрице
   LONGLONG        AdrLoadCalc;      // Позиции данных о загружениях

   int             MaxLengthH;

   BYTE       SumNus[8];
   DWORD      MaxLenUS;
   DWORD      MaxLenReak;
   DWORD      MaxLenUsRSU;
   DWORD      MaxLenRsRSU;

   float      UnixCoef[5];
   double     PrecisionGauss;   // точность Гаусса
   float      SumTimeCPU;       // Суммарное время процессора

   BYTE       SumNur[2];
   BYTE       CharacterElement[50]; // Признаки работы элементов:
                                    // Бит 0 - упругое основание

   LONGLONG   LengthStepData;   // Общая длина дополнительных данных одного шага
   int        MaxLenStepFormatElem;    // мах длина сохраняемых на нелинейном шаге данных
   BYTE       YesStressed;
   BYTE       YesOneSide;
   
   int        QuantityFixedStep;    // число фиксированных шагов нел.процесса 
   int        QuantityStep;         // число всех шагов нел.процесса   

   int        NumWorkStep;          // номер текущего шага 
   int        NumIteration;
   int        NumFixedStep;
   int        NumStepFile;
   int        NumWorkFile;

   BYTE       NoData;

   BYTE       TypeIterationSolver;
   WORD       RangIterationSolver;
   BYTE       SaveMatrIter;

   WORD       QuantityMatrIter;
   int        QuantityElemIter;
   int        MaxOrderMatrize;
   int        SumOrderIter;

   LONGLONG   AdrNumNodeStep;

   LONGLONG   AdrElemNode;
   DWORD      MaxLengthMatrIter;
   int        NumMatrGaussIter;

   double     FuncIter;

   LONGLONG   PosForceCenter;

   DWORD      MaxMemory;
   DWORD      MatrPortion;

   int        MatrMinus;

   LONGLONG   AdrRSU;
   LONGLONG   AdrNewRSU;
   LONGLONG   AdrDestructionRSU;

   int        QuantityForceTime;
   LONGLONG   AdrForceTime;

   BYTE       ReservEnd[172];

};

	/* Descriptor of the right hand side column */

struct HEAD_DISPLACE
{
	WORD  NQ;           //  Номер загружения
    WORD  NumStep;      //  Шаг для нелинейного процесса 
    WORD  NumFixedStep; //  номер п/п сохранения в шаговом процессе 
	WORD  PQ;           //	1-10 - статические загружения
		                //  11-199 - динамические загружения
		                //  200 - SD - динамическая огибающая
		                //  201, 202, 203 … -  S1, S2, … - динамическая огибающая. NF - номер
		                //  250 - для процесса интегрирования во времени.
				        //  При значении NumStep к номеру загружения добавляется значении шага.

	int   NF;           // номер перемещения/усилия/огибающей
	int   KF;           // число
	WORD  NumUnite;     //  номер задачи вариации 
	WORD  NumLoadSchemUnite; //  номер загружения в задаче вариации 
    WORD  Res[2]; 
};

struct LOAD_CALC
{
	WORD  NumStringForce;    
	WORD  QuantityStringForce;
	WORD  NumString;    //  Us | Displace - начало
	WORD  Res1;         
	WORD  QuantityString;
	WORD  NumAddString;        //  строка 
	WORD  QuantityEnvelope;    //  число огибающих
	WORD  NumStringEnvelope;   //  огибающая - начало
	WORD  TypeEnvelope;        //  тип огибающих
	WORD  NumDyn; 
	WORD  NumStepLoad;
	WORD  Res[2];
};

struct HEAD_USIL
{
	LONGLONG PosForm;   // Adress on the disk of the internal data

	int      NumEl;     // номер КЭ или группы унификации РСУ
	DWORD    L_US;      // Length in the bait of the stresses array

	WORD     KD_US;     // Quantity of the seshenij
	WORD     NS_US;     // Number of the secheniq
	DWORD    L_RS;      // Length of the combination characteristic
	
	WORD     KR1_RS;    // Number of the combinations of the first group
	WORD     KR2_RS;    // Number of the combinations of the second group
	BYTE     TypeUnif;  // Тип унификации РСУ
	BYTE     TypeConstr;   // тип конструкции из группы в РСУ
	BYTE     QuantityUs; 
	BYTE     TypeUs[8];          // идентификация усилий
    BYTE     Res[9];
};

#include <s_rsu.h>

struct FORMAT_POSITION {
   int       min;
   int       max;
   LONGLONG  Pos;  };

struct FORMAT_UNITE
{
   FILEWORK   Form;
   FILEWORK   Step;
   FILEWORK   Work;    //  рабочие файлы для нормального завершения
   CALC_DATA  CalcData;
};

#pragma pack(pop)
#endif
