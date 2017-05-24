#ifndef CALC_DATA__H
#define CALC_DATA__H
#pragma pack(push, 1)

#include <fe_form.h>
#include <sg_dyn1.h>

struct CALC_DATA
{
   char       Ident[8];
   WORD       Length;          // Длина CTG
   WORD       Version;

   FILE_MARK  FileMark[100];   //  Контроль при открытии

   BYTE       TypeProcess;
   WORD       QuantityNodeSE;

   WORD       QuantityElem;    // Количество элементов
   WORD       QuantityNode;    // Число узлов
   BYTE       YesZEL;          // null elem yes
   BYTE       MaxLayer;        // Максимальное число слоев в многослойках
   BYTE       QuantityElemStep;  // В схеме есть шаговые элементы

   WORD       QuantityLoad;    // Число статических загружений
   WORD       QuantityLoadDyn;
   WORD       QuantityLoading; // Количество правых частей
   WORD       MaxFormD15;
   long       SumQuantityForm;

   long       OrderDispl;      // Порядок вектора перемещений
   long       OrderSystem;     // Порядок системы
   long       OrderSE;         // Порядок суперєлемента

   long       HSystem;         // Ширина ленты
   WORD       HElem;           // Номер H-элемента

   long       MaxLenFormat;    // len format
   long       MaxLenAddFormat; // len format
   long       MaxQuantityValue;// max числовых характеристик местн.нагр.

   BYTE       MODE;             //  модальный  анализ, модуль 100
   WORD       YesAvtoMass;      // ???????

   WORD       MaxNodeElem;
   WORD       MaxKD;
   WORD       MaxKN;
   WORD       MaxKR;
   long       MaxKDxKN;
   long       MaxKG;
   WORD       MaxKNLitera;
   DWORD      MaxLengthEq;

   BYTE       WorkStep;         // позиция выполнения

   long       NumLineMatr;      //  точка прерывания при составлении матрицы

   BYTE       YesData;
   BYTE       YesOptimize;
   BYTE       YesMatr;
   BYTE       YesGauss;         // Прошел прямой ход Гаусса
   BYTE       YesStartVector;
   BYTE       YesMass;
   BYTE       YesForm;
   long       MaxForm;
   BYTE       YesDynForce;
   BYTE       YesForce;
   BYTE       YesDisplace;
   BYTE       YesEffors;

   BYTE       YesRSU;
   WORD       QuantityGroupUnific;

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

   BYTE       YesRes[10];

   BYTE       NullStringMatrize;
   BYTE       GIS;

   DOCUMENT   Format;
   DOCUMENT   Doc05;

   DOCUMENT   DocDynamic;
   DOCUMENT   HeadDispl;
   DOCUMENT   PositionEffors;
   DOCUMENT   PositionEfforsComb;
   DOCUMENT   DocStepData;
   DOCUMENT   DocUnite;
   DOCUMENT   DocSE;
   DOCUMENT   DocR01;
   DOCUMENT   DocR02;
   DOCUMENT   DocR03;

   DWORD      AdrNewNumber;     // адрес номеров неизвестных после оптимизации
   DWORD      AdrProfMatr;      //
   DWORD      AdrFormPos;       // adrel
   DWORD      PosGaussWork;     // Позиции состояния прямого хода
   DWORD      LenGaussWork;     // длина
   DWORD      AdrPosEquation;   // Позиции уравнений в матрице
   long       MaxLengthH;

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
   int        QuantityLoadStep;
   int        QuantityFixedStep;
   int        QuantityStep;

   int        NumWorkStep;
   int        NumIteration;
   int        NumFixedStep;
   int        NumStepFile;
   int        NumWorkFile;

   BYTE       NoData;

   BYTE       TypeIterationSolver;
   WORD       RangIterationSolver;
   BYTE       SaveMatrIter;

   WORD       QuantityMatrIter;
   long       QuantityElemIter;
   long       MaxOrderMatrize;
   long       SumOrderIter;

   DWORD      AdrNumNodeStep;

   DWORD      AdrElemNode;
   DWORD      MaxLengthMatrIter;
   long       NumMatrGaussIter;

   double     FuncIter;

   BYTE       ReservEnd[200];

};

	/* Descriptor of the right hand side column */

struct HEAD_DISPLACE
{
	short NQ; // Load number
   BYTE  Type;  // 0 - OrderSystem, 1 - OrderDisplace
	BYTE  PQ; /* Load flag: 0 - static with node and local forces;
			1 - static with local forces;
			2,3,4,5,... - dynamic forces                  */
	short NF; // Form number for the dynamic load
	short KF; // Number of the forms for the dynamic load
};

struct HEAD_USIL
{
	DWORD PosForm;   // Adress on the disk of the internal data
	WORD  NumEl;     // NumBer FE
	WORD  Res;       //
	DWORD L_US;      // Length in the bait of the stresses array
	WORD  KD_US;     // Quantity of the seshenij
	WORD  NS_US;     // Number of the secheniq
	DWORD L_RS;      // Length of the combination characteristic
	short KR1_RS;    // Number of the combinations of the first group
	short KR2_RS;    // Number of the combinations of the second group
};

#include <s_rsu.h>

struct Combinations  /* Structure of combinations */
{
	short KCQ;
	short nComb;      /* Number of combinations    */
	float *CombCoef;  /* Chain of coefficients of combinations: */
							/* Its number = (KCQ + KCQ * (nComb - 1)) * nComb / 2  */
};

struct FORMAT_POSITION {
   long   min;
   long   max;
   DWORD  Pos;  };

struct ITER_SOLVER
{
   WORD    QuantityElem;
   WORD    QuantityNode;
   long    Order;
   long    SumOrder;
   DWORD   PosMatrize;
   DWORD   LenMatrize;
};
#pragma pack(pop)

#endif
