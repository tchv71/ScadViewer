#ifndef SG_DYN1_FLAG_H
#define SG_DYN1_FLAG_H
#pragma pack(push,1)

struct   sg_dyn1
{
	BYTE     mod;               //  модуль
	WORD     NumLoad;           //  номер загружения
	WORD     AddLoad;           //  присоединенное загружение
	
	WORD     QuantityForm;      //  число вычисленных собственных векторов
	WORD     QuantityForce;     //  число cформированных правых частей
	WORD     QuantityDisplace;  //  число cформированных перемещений
	
	long     QuantityMass;      //  число масс
	double   MaxAbsMas;         //  для сравнения динамических загружений
	
	DWORD    ResDubl;
	WORD     ResBuf; // 
	
	LONGLONG AdrMass;
	LONGLONG AdrAddForce;
	
	LONGLONG AdrOften;
	LONGLONG AdrForm;
	LONGLONG AdrDispl;
	LONGLONG AdrForce;
	LONGLONG AdrSum;
	
	long     QuantityPointTime; //   число точек проверки временной нагрузки
	LONGLONG AdrPointTime;      //   значения времени проверки
	LONGLONG AdrCoefForm;       //   коэффициенты нагрузки при формах
                              //   QuantityForm * QuantityPointTime
	LONGLONG AdrCoefFormMax;    //   max. значения коэффициентов при форме
	LONGLONG AdrTimeCoefFormMax;//   значения времени достижения максимума на форме
	
	WORD     NumIter;           //   номер итерации
	LONGLONG AdrForm1;          //   адресс первого  приближения форм
	LONGLONG AdrForm2;          //   адресс второго  приближения форм
	LONGLONG AdrFormR;          //   рабочий адресс  для режима прерывания
	double   Gamma;             //   коэффициент затухания
	double   MaxOfften;         //   максимальная учитываемая частота
	double   DeltaSpectr;       //   учитываются только частоты, не превышающие DeltaSpectr * 1-я частота
	
	WORD     piter;
	WORD     rkf;
	WORD     kft;
	double   osh;
	
	DWORD    QuantityWorkForce; //  число нагрузок в WORK файле
	WORD     MaskMass;
	
	DWORD    AdrHelpInf;        //   рабочий адресс  для вспомогательных величин
    BYTE     TypeSum;           //	 1 - сумма квадратов. Модули 19-21, 30, 50, 51
	                            //	 2 - сумма для импульса по Сорокину. Модули 22-23
	                            //	 3 - модуль комплексного числа. Модули 24, 28, 34
	                            //	 4 - московские нормы. 31.
	                            //	 5 - максимум во времени. 27, 42,  47.
	                            //   6 - армянские нормы .  52.
	                            //  11 - модуль 101, динамика во времени 
	BYTE     YesSum;            //   наличие  суммарных перемещений (усилий)
	WORD     QuantitySum;       //   число  суммарных перемещений (усилий)
	WORD     NumFixedStep;      //   для правильного определения номера загружения в вариации
	char     Res[70];
};

struct DYN_FORCE  {  long NumStep;  long NumNode;  BYTE Qn;  double d_7[12];  };

struct s_dok15
{
	short  ls_d15;
	short  mod_d15;
	short  kf_d15;
	short  nsq_d15;
	short  spr_d15;
	short  prt_d15;
	double zn_d15[100];
};


struct DYN_IMPULS_VALUE  {
	double Time;
	double Value;  
};

struct DYN_IMPULS  {
	int    Type;
	int    QuantityPoint;
	double Time;
	double Amp;
	double Area;
	DYN_IMPULS_VALUE * Imp;
};

struct DYN031 {
	double   Coeff;      // 0
	double   WindArea;   // 1  ветровой район
	double   TypeArea;   // 2  тип местности
	double   fi;         // 3
	double   resd;       // 4
	double   h;          // 5
	double   Gamma;      // 6  >1, < 0.3
	double   AllForm;    // 7 1 не учитывать, 0 учитывать
	double   res[10];
};

struct DATA_SNG {
	double   Correction;      //  Поправочный коэффициент. Используется,
	                          //    для конструкций п.2.12, когда он равен 1.2
	double   k1xy;            //  коэффициент, учитывающий неупругие деформации
	                          //     для горизонтальной составляющей по табл. 2.2.
	double   k1H;             //  коэффициент, учитывающий неупругие деформации
                              //     для вертикальной составляющей по табл. 2.2. и п.2.14
                              //     К табл. 2.2 добавлено значение 0.5
	double   k2;              //  коэффициент ответственности сооружений по табл. 2.3.
	double   TypeA;           //  Тип задания коэффициента сейсмичности
	double   A;               //  Коэффициент сесмичности, п.2.9.
	double   KA;              //  Поправочный множитель к А для верт. направления, п.2.14.
	                          //  По умолчанию принимается значение 0.7
	double   Ground;          //  Категория грунта:1 -2 -3 -4 - график
	double   CX, CY, CZ;      //  косинусы: CX с осью X; CY - с осью Y; CZ - с осью Z -
	                          //    задают направление действия поступательной сейсмической
	                          //    нагрузки. Вектор нормируется в программе.
	double   Res;
	double   YesMoment;       //  Признак уточненного расчета
	double   X0, Y0, Z0;      //  Координаты цента вращения.Задаются пользователем
	double   BX, BY, BZ;      //  Косинусы: BX с осью X; BY - с осью Y; BZ - с осью Z -
	                          //    задают направление действия  вращения сейсмической нагрузки.
	                          //    Вектор нормируется в программе.
};

struct DATA_Arm {
	double   Correction;      //  Поправочный коэффициент
	double   k0;              //  коэффициент грунтовых условий (табл.1.3)
	double   k1;              //  коэффициент, учитывающий допустимые повреждения
						   	  //    конструкций (табл.2.4)
	double   k2;              //  коэффициент ответственности сооружений по табл. 2.5
	double   A;               //  Коэффициент сесмичности, п.2.9.
	double   KA;              //  Поправочный множитель к А для верт. направления, п.2.14.
	                          //  По умолчанию принимается значение 0.7
	double   Ground;          //  Категория грунта:1 -2 -3 -4 - график
	double   CX, CY, CZ;      //  косинусы: CX с осью X; CY - с осью Y; CZ - с осью Z -
	                          //    задают направление действия поступательной сейсмической
	                          //    нагрузки. Вектор нормируется в программе.
	double   Res;
};

struct DATA_Atom {
	double   ke;              //  Коэффициент, учитывающий особые условия эксплуатации АС
	double   TypeGraf;        //  Тип графика коэффициента динамичности
							  //  0 - по рис.П3.1.
							  //  1 - единый для всех  направлений
							  //  2 - различный для всех направлений
	double   Dl;              //  логарифмический декремент колебаний
	double   Axy;             //  Максимальные ускорения грунта в горизонтальной плоскости
	double   KA;              //  Максимальные ускорения грунта в направлении Z
	double   CX, CY, CZ;      //  косинусы: CX с осью X; CY - с осью Y; CZ - с осью Z -
							  //    задают направление действия поступательной сейсмической
							  //    нагрузки. Вектор нормируется в программе.
};

struct SEISM_UKR_WORK 
{
	double Correct;           //   Значение коэффициента корректировки
	double k1;                //   Табл. 2.3. Номер строки
	double k2;                //   Табл. 2.4  Значение
	double Seism;             //   Сейсмичность 6-9
	double Map;               //   Номер строки Табл. 2.5 с 1.  
	double Ground;            //   Грунт 1-4
	double kg;                //   Табл. 2.6. Значение для грунта 4-й категории
	double Floor;             //   этажность
	double X;                 //   направление воздействия
	double Y;
	double Z;
	double TypeGrafic;        //   Тип задания графиков 0 - по ДБН, 1 - один график, 2 - 3-и графика
	double YesMoment;         //   учет приложения Г
	double B;                 //   минимальный размер в плане
	double X0;                //   координаты центра вращения
	double Y0;
	double Z0;
	double ax;                //   напрвление вращение 
	double ay;
	double az;
};

struct SEISM_SP_RF_WORK 
{
	double Correct;           //   Значение коэффициента корректировки
	double k1;                //   Табл. 3. Значение 
	double Seism;             //   Сейсмичность 7-9
	double Ground;            //   Грунт 1-3
	double kg;                //   Табл. 6. Задается только для грунта 4-й категории
	double X;                 //   направление воздействия
	double Y;
	double Z;
	double TypeGrafic;        //   Тип задания графиков 0 - по ДБН, 1 - один график, 2 - 3-и графика
	double YesMoment;         //   учет приложения Г
	double B;                 //   минимальный размер в плане
	double X0;                //   координаты центра вращения
	double Y0;
	double Z0;
	double ax;                //   напрвление вращение 
	double ay;
	double az;
};

struct SEISM_KAZ_2006_WORK 
{
	double Correct;           //   Значение коэффициента корректировки
	double k1;                //   Табл. 5.2. Номер строки 
	double k1z;               //   Значение 
	double k2;                //   Табл. 5.3 и 5.4. Номер строки 
	double k2z;               //   Значение 
	double Head;              //   Тип учета высоты: 0 - этажность, 1 - 1.8, 2 - 2.0
	double Floor;             //   Этажность >=5
	double ks;                //   Значение табл. 5.6
	double kg;                //   Номер строки табл. 5.7
	double Seism;             //   Сейсмичность 7-10
	double Ground;            //   Грунт 1-3
	double YesA;              //   ускорение по картам. Проект
	double ax;                //   ускорение
	double az;                //   ускорение
	double X;                 //   направление воздействия
	double Y;
	double Z;
	double TypeGrafic;        //   Тип задания графиков 0 - по ДБН, 1 - один график, 2 - 3-и графика
	double TypeQuantityForm;  //   Признак учета числа форм. 0 - по СНИП, 1 - все
	double P522;              //   Признак учета п.5.22, 0 - не учитывать
	double P523;              //   Признак учета п.5.23, 0 - не учитывать
	double P524;              //   Признак учета п.5.24, 0 - не учитывать
	double P525;              //   Признак учета п.5.25, 0 - не учитывать
};

struct SUM_DYN_DATA {
    double    QuantityChast;
    double  * Chast;
    int       QuantityPoint;
	double  * PointTime;
	double  * CoefForm;  //  QuantityPointTime * QuantityChast
	double  * CoefFormMax;
};

#pragma pack(pop)
#endif
