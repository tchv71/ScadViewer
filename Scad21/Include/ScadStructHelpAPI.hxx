#ifndef ScadStructHelpApiFLAG_H
#define ScadStructHelpApiFLAG_H

#pragma pack(push,1)

typedef double * lpDouble;

struct UnitsAPI  {
	char Name[10];
	float coef;       };
typedef	  const UnitsAPI * LPCUnitsAPI;
struct CNodeApi
{
	LPCSTR  		Text;	//	CSCSTR        Text;
	double  		x, y, z;
	BYTE 			Flag;	 
};

typedef	  CNodeApi * LPCNodeApi;

struct CElemInfApi
{
	LPCSTR  	Text;	//	CSCSTR        Text;
	UINT        QuantityNode;
	UINT      * Node;

	WORD        TypeElem;            // тип элемента
	BYTE        IsDeletet;		     // флаги элемента
	UINT        TypeRigid;           /// тип жесткости
	UINT        NumInsert;           // номеp списка жест.вст.
	UINT        NumSysCoord;         // номеp списка угл. повоp.
	UINT        NumSysCoordEffors;   // номеp списка угл. повоp.выч.напp.
	UINT        NumBed;              // номеp списка коэффициентов постели.
	UINT        NumStress;         // преднапряжение

	struct {  UINT Quantity;  UINT * Pointer;  } * Hole;     // отверстия  

};

struct SCAD_IDENT
{
	char          Text[256];
	int           Quantity;
	double        Data[32];
};

struct SCAD_SECTION {
	char            Name[512];      //  имя типа жесткости 
	int             NumRgd;         //  номер типа жесткости в документе жесткостей или подбора сечений
	int             Group;          //  0-7 - пользовательское сечение
                                        //  201-230 - сечения из металлопроката
                                        //  231 - 234 - спаренные сечения из металлопроката   
                                        //  99 - численное задание данных
                                        //  199 - данных конструктора сечений
	int             GroupSection;   //  0-7 - пользовательское сечение
                                        //  201-230 - сечения из металлопроката
                                        //  231 - 234 - спаренные сечения из металлопроката   
	
	int             QuantityGeom;   //  для пользовательского сечени его размеры
	double          Geom[200];      //  размеры пользовательского сечения
	
	char            NameBase[_MAX_PATH];  // имя базы металлопроката
	char            FileSection[16];    // имя секции базы металлопроката
	int             NumString;          // номер строки в секции
	
	int             QuantityDataSection;  //  число дополнительных данных для для спаренных сечений
	double          DataDoubleSection[4]; //  дополнительных данных для для спаренных сечений:
                                              //  тип соединения для конструктора,
            	                              //  зазор соединения или размер по Z и т.д.
	
	int             YesConstructor;       //  данные из конструктора сечений
	char            NameFileConstructor[_MAX_PATH]; //  имя файла для конструктора
	double          DataConstructor[13];      //  данные о жесткостях 
	
	int             TypeElem;             //  для численного задания тип элемента: 1-5, 10
	int             YesN;                 //  Учет преднапряжения или сдвига
	double          N;                    //  Величина преднапряжения
	
	double          ema[6];               //  EF,EIY,EIZ,GKP,GFY,GFZ  величины для численного моделировани
	
	double          E;                   //  Модуль упругости
	double          ro;                  //  плотность
	double          nu;                  //  Коэффициент Пуассона
	
};

//  флаги степеней свободы
#define SgDirectX      0x0001
#define SgDirectY      0x0002
#define SgDirectZ      0x0004
#define SgDirectUX     0x0008
#define SgDirectUY     0x0010
#define SgDirectUZ     0x0020
#define SgDirectAX     0x0040
#define SgDirectAY     0x0080
#define SgDirectAZ     0x0100
#define SgDirectBX     0x0200
#define SgDirectBY     0x0400
#define SgDirectBZ     0x0800
#define SgDirectCX     0x1000
#define SgDirectCY     0x2000
#define SgDirectCZ     0x4000

//  флаги нагрузки
#define SgUnknown     0 
#define SgForceX      1
#define SgForceY      2
#define SgForceZ      3
#define SgForceUX     4
#define SgForceUY     5
#define SgForceUZ     6

#define SgEffortsN      0x000000000000000001
#define SgEffortsMk     0x000000000000000002 
#define SgEffortsM      0x000000000000000004
#define SgEffortsQ      0x000000000000000008
#define SgEffortsMy     0x000000000000000010
#define SgEffortsQz     0x000000000000000020
#define SgEffortsMz     0x000000000000000040
#define SgEffortsQy     0x000000000000000080
#define SgEffortsNX     0x000000000000000100
#define SgEffortsNY     0x000000000000000200
#define SgEffortsNZ     0x000000000000000400
#define SgEffortsTXY    0x000000000000000800
#define SgEffortsTXZ    0x000000000000001000
#define SgEffortsTYZ    0x000000000000002000
#define SgEffortsMX     0x000000000000004000
#define SgEffortsMY     0x000000000000008000
#define SgEffortsMXY    0x000000000000010000
#define SgEffortsQX     0x000000000000020000
#define SgEffortsQY     0x000000000000040000
#define SgEffortsQXY    0x000000000000080000
#define SgEffortsRZP    0x000000000000100000
#define SgEffortsNEQ    0x000000000000200000
#define SgEffortsN1     0x000000000000400000
#define SgEffortsN2     0x000000000000800000
#define SgEffortsAlfa   0x000000000001000000
#define SgEffortsWG     0x000000000002000000
#define SgEffortsRX     0x000000000004000000
#define SgEffortsRY     0x000000000008000000
#define SgEffortsRZ     0x000000000010000000
#define SgEffortsRUX    0x000000000020000000
#define SgEffortsRUY    0x000000000040000000
#define SgEffortsRUZ    0x000000000080000000
#define SgEffortsRAX    0x000000000100000000
#define SgEffortsRAY    0x000000000200000000
#define SgEffortsRAZ    0x000000000400000000
#define SgEffortsRBX    0x000000000800000000
#define SgEffortsRBY    0x000000001000000000
#define SgEffortsRBZ    0x000000002000000000
#define SgEffortsRCX    0x000000004000000000
#define SgEffortsRCY    0x000000008000000000
#define SgEffortsRCZ    0x000000010000000000

typedef enum : BYTE
{
	ApiGroupUndefined	    = 0,
	ApiGroupRod			= 1,
	ApiGroupPlate			= 2,
	ApiGroupVolume			= 3,
	ApiGroupSpecial		= 4,
	ApiGroupAxecymmetric	= 5,
}  ApiGroupType;

typedef enum : BYTE
{
	ApiLocalSystemCoord       	 =  0,   // 
	//  Стержни, координатные оси
	ApiRodCornerInDegrees  	 =  1,   // угол в градусах
	ApiRodCornerInRadians	     =  2,  //  угол в радианах
	ApiRodPointFocusAxecY   	 =  3,   // точка, на которую ориентирована  гл. ось Y
	ApiRodVectorFocusAxecY      =  4,   // вектор, на которую ориентирована гл. ось Y
	ApiRodPointFocusAxecZ 		 =  5,   // точка, на которую ориентирована  гл. ось Z
	ApiRodVectorFocusAxecZ  	 =  6,   // вектор, на которую ориентирована гл. ось Z
	//  Стержни, главные оси
	ApiRodPointFocusGeomAxecY   =  7,   // точка, на которую ориентирована  геом. ось Y
	ApiRodVectorFocusGeomAxecY  =  8,   // вектор, на которую ориентирована геом. ось Y
	ApiRodPointFocusGeomAxecZ 	 =  9,   // точка, на которую ориентирована  геом. ось Z
	ApiRodVectorFocusGeomAxecZ  = 10,   // вектор, на которую ориентирована геом.  ось Z
	//  Плиты
	ApiPlateAxecX               = 16,  // направление Х в глобальной СК
	ApiPlatePointFocusAxecX     = 17,  // направление Х на точку
	ApiPlatePointFocusCentersAxecX = 18,  // направление Х на точку из центра
	ApiPlateAxecY               = 19,  // направление Y в глобальной СК
	ApiPlatePointFocusAxecY     = 20,  // направление Y на точку
	ApiPlatePointFocusCentersAxecY = 21,  // направление Y на точку из центра
	//  Volume
	ApiVolumeAxecXY             = 32,  // направление Х, Y 
	ApiVolumeAxecXZ             = 33,  // направление Х, Z 
	ApiVolumeAxecYZ             = 34,  // направление Y, Z 
	ApiVolumeCornersInDegrees   = 35,  // углы Эйлера в градусах
	ApiVolumeCornersInRadians   = 36,  // углы Эйлера в радианах
	ApiVolumeCylinderTwoPointsZ = 37,  // цилиндр. Задаются две точки на оси от и до 
	ApiVolumeCylinderPointsAndVectorZ = 38,  // цилиндр. Задаются точка и направление 
	ApiVolumeSphereCentreAndPointY    = 39,  // сфера. Задаются точка и точка, на которую ориентирована ось Y 
	ApiVolumeSphereCentreAndVectorY   = 40,  // сфера. Задаются Задаются точка и направление оси Y
}  ApiSystemCoord;

typedef enum : BYTE
{
	ApiForceNode              =  0,	// Сосредоточенная
	ApiForceNodeDisplace      =  1,	// Заданные перемещения (сосредоточенная)
	ApiForceNodeSpecial       =  2,	// Сосредоточенная

	ApiForcePointLocal        =  5,	// Сосредоточенная 
	ApiForceEvenlyLocal       =  6,	// Стержень - линейная, пластина - площадная, volume - объемная или площажная
	ApiForceTrapezLocal       =  7,	// Стержень - линейная, пластина - площадная, volume - объемная
	ApiForceTempLocal         =  8,  
	ApiForceLineEvenlyLocal   =  9,	// Линейная
	ApiForceLineTrapezLocal   = 10,	// Линейная  

	ApiForceNullElem 		  = 11,	// Метры/углы

	ApiForcePointGlobal       = 15,	// Сосредоточенная 
	ApiForceEvenlyGlobal      = 16,	// Стержень - линейная, пластина - площадная, volume - объемная или площажная
	ApiForceTrapezGlobal      = 17,	// Стержень - линейная, пластина - площадная, volume - объемная
	ApiForceTempTrapez        = 18,  // Температура у узлах элемента: dta1 dtb1 dta2 dtb2 ...
	ApiForceLineEvenlyGlobal  = 19,	// Линейная 
	ApiForceLineTrapezGlobal  = 20, 	// Линейная 

	ApiForcePointPartLocal    = 45,   // В долях длины для стержней 	// Сосредоточенная
	ApiForceEvenlyLocalIns    = 46,	 // Стержень - линейная. Нагрузка с учетом жесткич вставок
	ApiForceTrapezPartLocal   = 47,	 // Линейная    
	ApiForcePointPartGlobal   = 55,   // Сосредоточенная
	ApiForceEvenlyGlobal_INS  = 56,	 // Стержень - линейная. Нагрузка с учетом жесткич вставок
	ApiForceTrapezPartGlobal  = 57,	 // Линейная   

	ApiForcePointMass         = 85,   //  массы соср. по всем направлениям
	ApiForceEvenlyMass        = 86,   //  массы р/р по всем направлениям

	ApiForceTempUnif          = 88, 

	ApiForceWeight            = 96,	// Стержень - линейная, пластина - площадная, volume - объемная
	ApiForceWeightIns         = 116,	// Стержень - линейная. Нагрузка с учетом жесткич вставок

}   ApiForceType;

struct   ApiRSU_ADD { BYTE Type;  UINT NumNagr;  };

struct APIRsuNew  {
	WORD       TypeLoad;          // тип згружения
	WORD       ModeLoad;          // вид загружения
	WORD       Sign;              // variable sign
	WORD       Crane;             // номер крана 
	WORD       CraneRegime;       // Группа режимов работы крана, 1-8
	WORD       NoActive;          // Не активное   
	double     CoeffSafetyFactor;  //  коэффициент надежности по нагрузке
	double     LongTimeLoadComponent;  // доля длительной составляющей
	double     Coeff[16];          // koef-s  rsu
};

typedef enum : BYTE
{
    ApiDYN_NO     =   0,  // статика
    ApiDYN_TIME   =   1,  // интегрирование по времени
    ApiDYN_LS     =   2,  // статическая составляющая ветровой нагрузки (только для нелинейности и монтажа) ( 252 )
    ApiDYN_LN_LS  =   3,  // нелинейность/монтаж + статическая составляющая ветровой нагрузки ( 253 )
    ApiDYN_LB_LS  =   4,  // нелинейность/монтаж + статическая составляющая ветровой нагрузки ( 253 )
    ApiDYN_MASS   =   5,  // формы
    ApiDYN_FORM   =  11,  // формы
    ApiDYN_STAB   =  12,  // формы потери устойчивости
    ApiDYN_RD     =  13,  // действительная часть
    ApiDYN_RI     =  14,  // комплексная часть
    ApiDYN_FORMX  =  15,  // шестикомпонентное
    ApiDYN_FORMY  =  16,  // шестикомпонентное
    ApiDYN_FORMZ  =  17,  // шестикомпонентное
    ApiDYN_FORMUX =  18,  // шестикомпонентное
    ApiDYN_FORMUY =  19,  // шестикомпонентное
    ApiDYN_FORMUZ =  20,  // шестикомпонентное

    ApiDYN_SD     =  21,  // динамическая огибающая ( сумма квадратов, по нормам )
    ApiDYN_SI     =  22,  // динамическая огибающая от действительной и комплексной части
    ApiDYN_LS_SD  =  31,  // статическая + динамическая огибающая.
    ApiDYN_LN_SD  =  32,  // нелинейность/монтаж + динамическая огибающая ( 251 ) 
    ApiDYN_LS_SI  =  34,  // статическая + динамическая огибающая.
    ApiDYN_LN_SI  =  35,  // нелинейность/монтаж + динамическая огибающая ( 251 ) 
    ApiDYN_LB_SD  =  37,  // монтаж + динамическая огибающая ( 251 ) 
    ApiDYN_LB_SI  =  39,  // монтаж + динамическая огибающая ( 251 ) 
    ApiDYN_LN_TIME=  41,  // интегрирование по времени
    ApiDYN_LB_TIME=  42,  // интегрирование по времени
    ApiResultTypeUndefined =0xFF
}   ApiLoadingStringType;


struct ApiLoadingData {
	BYTE     TypeInf;            // RESULT_DATA
	BYTE     TypeLoad;           // 
	WORD     TypeEnvelope;       // 1-200, 200
	WORD     NumLoad;
	WORD     NumSchemUnite;      //  номер задачи вариации 
	WORD     NumLoadSchemUnite;  //  номер загружения в задаче вариации 
	WORD     NumStep;            //  Шаг для нелинейного процесса 
	WORD     NumFixedStep;       // номер п/п сохранения в шаговом процессе 
	UINT32   QuantityForm;
	UINT32   NumForm;
	double   Value;              //  собст. значения, время для динамики
	float    ProcMassX;        //  Для формы колебаний процент масс
	float    ProcMassY;        //  Для формы колебаний процент масс
	float    ProcMassZ;        //  Для формы колебаний процент масс
	LPCTSTR  Name;
	double * Comb;
};

typedef ApiLoadingData * lpApiLoadingData;

struct  ApiElemEffors 
{
	UINT           NumElem; 
	BYTE           QuantityUs; 
	const BYTE   * TypeUs;
	BYTE           QuantityPoint;
	WORD           QuantityPointLayers;
	WORD           QuantityLoading;
	WORD           QuantityComb;
	BYTE           IsComb; 
	size_t         MaxSizeUs; 
	size_t         QuantityDataUs; 
	double       * Us;
	size_t         MaxSizeUsComb; 
	size_t         QuantityDataUsComb; 
	double       * UsComb;
};

struct  ApiElemRsuStr 
{
	UINT    NumElem;      // номер элемента. При унификации не равен, указанному в HEAD_USIL
	BYTE    NumPoint;      // номер сечения элемента. При унификации не равен для элемента
	BYTE    NumPointElem;  // номер сечения элемента
	BYTE    NumColumn;   	// номер столбца
	BYTE    GroupRsu;     // наличие загружений 0 - все загружения, 1 - только длительная часть									
	//					  2 - нормативная,    3 - только длительная часть нормативной									 
	WORD    NumCrit;   	// номер критерия
	WORD    QuantityCoef;
	BYTE    YesSeism;     // признак наличия сейсмической нагрузки
	BYTE    YesSpec;      // признак наличия специальной не сейсмической нагрузки 
	BYTE    YesCrane;     // признак наличия кранов
	BYTE    YesTransport; // наличие транспортных нагрузок в сейсмике
	BYTE    Res[4];
	float * Us;
	WORD  * NumLoad;
	float * Coef;
	float   Value; 
};

struct  ApiElemRsu 
{
	UINT    NumElem;     // номер КЭ или группы унификации РСУ
	BYTE    TypeUnif;    // Тип унификации РСУ
	WORD    GroupUnif;  // 
	BYTE    TypeConstr;  // тип конструкции из группы в РСУ
	BYTE    QuantityPoint;
	BYTE    QuantityUs;
	UINT    LengthData;  // Длина данных
	UINT    Quantity;    // Число комбинаций
	ApiElemRsuStr * Str;
};

typedef enum
#ifndef _lint
		: BYTE
#endif
	{
		API_RESULT_UNDEFINED   = 0, 
		API_RESULT_LOAD        = 11, 
		API_RESULT_LOAD_COMB   = 12, 
		API_RESULT_MODE        = 13, 
		API_RESULT_STABIL      = 14, 
		API_RESULT_STABIL_COMB = 15, 

		API_RESULT_MASS        = 21,
		
		API_RESULT_FRAGMENT      = 33,
		API_RESULT_FRAGMENT_COMB = 34,
		API_RESULT_FRAGMENT_LINK = 35,
		API_RESULT_FRAGMENT_LINK_COMB = 36,
	} API_RESULT_DATA;  

struct ApiArmElemRod
{
	UINT      PartNo; // номер участка
	double    L_percent; // длина участка в процентах от длины
	UINT      IsS1D2; // S1 имеет два различных диаметра
	UINT      IsS2D2; // S2 имеет два различных диаметра
	UINT      IsSw; // есть поперечка
	UINT      IsS34; // есть S3,S4
	UINT      dS1L1_1; // первый диаметр S1
	UINT      nS1L1_1; // количество стержней S1
	UINT      dS2L1_1; // первый диаметр S2
	UINT      nS2L1_1; // количество стержней S2

	UINT      dS1L1_2; // второй диаметр S1 (IsS1D2==SCTRUE)
	UINT      nS1L1_2; // количество стержней S1 второго диаметра (IsS1D2==SCTRUE)
	UINT      dS2L1_2; // второй диаметр S2 (IsS2D2==SCTRUE)
	UINT      nS2L1_2; // количество стержней S2 второго диаметра (IsS2D2==SCTRUE)
	UINT      dS3L1_1; // диаметр S3
	UINT      nS3L1_1; // количество стержней S3
	UINT      dS4L1_1; // диаметр S4
	UINT      nS4L1_1; // количество стержней S4
	UINT      dSw; // диаметр поперечной арматуры  в плоскости Z
	UINT      nSw; // количество стержней поперечной арматуры  в плоскости Z
	double    StepSw; // шаг поперечной арматуры в плоскости Z
	UINT      dSw2;  // диаметр поперечной арматуры в плоскости Y
	UINT      nSw2; // шаг поперечной арматуры в плоскости Y
	double    StepSw2;// шаг поперечной арматуры в плоскости Y

	// from reserved
	BYTE      IsS1L2; // S1 имеет два ряда
	BYTE      IsS2L2; // S2 имеет два ряда
	double    DeltaS1; // расстояние между рядами S1 (IsS1L2==TRUE)
	double    DeltaS2; // расстояние между рядами S2 (IsS2L2==TRUE)
	UINT      dS1L2; // диаметр S1 второго ряда (IsS1L2==TRUE)
	UINT      nS1L2; // количество стержней S1 второго ряда (IsS1L2==TRUE)
	UINT      dS2L2; // диаметр S2 второго ряда (IsS2L2==TRUE)
	UINT      nS2L2; // количество стержней S2 второго ряда (IsS2L2==TRUE)

	char    reserved[sizeof(double)*14-sizeof(BYTE)*2-sizeof(UINT)*4];
};

struct ApiArmRod {
	LPSTR           Text;
	UINT            Quantity;
	UINT *          List;
	UINT            QuantityArmRod;
	ApiArmElemRod * ArmRod;
};

struct ApiArmElemPlate
{
	UINT	dS1;		// диаметр продольной арматуры S1
	double	StepS1;		// шаг продольной арматуры S1
	UINT	dS2;		// диаметр продольной арматуры S2
	double	StepS2;		// шаг продольной арматуры S2
	UINT	dS3;		// диаметр продольной арматуры S3
	double	StepS3;		// шаг продольной арматуры S3
	UINT	dS4;		// диаметр продольной арматуры S4
	double	StepS4;		// шаг продольной арматуры S4
	UINT	dW;			// диаметр поперечной арматуры
	double	StepWx;		// шаг поперечной арматуры по оси X
	double	StepWy;		// шаг поперечной арматуры по оси Y
	BOOL	NoUp;		// верхней арматуры нет
	BOOL	NoDown;		// нижней арматуры нет
	BOOL	NoTrans;	// поперечной арматуры нет
	char reserved[sizeof(double)*16];
};

struct ApiArmPlate {
	LPSTR             Text;
	UINT              Quantity;
	UINT *            List;
	ApiArmElemPlate   ArmPlate;
};

#pragma pack(pop)

#endif
