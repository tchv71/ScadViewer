#ifndef ARMATUR_FLAG_HPP
#define ARMATUR_FLAG_HPP
#pragma pack(push,1)

//#define MAX_CONSTRUCTION_NAME 	        40
//#define MAX_NODE_NAME 	              40
//#define NODE_SENCETIVE   	            3
//#define MAX_QUANTITY_GRAF_FILE_NODE    4
//#define MAX_COMPANY_NAME 		        40
//#define MAX_CUSTOMER_NAME 		        40
//#define MAX_OBJECT_NAME 		        40
//#define MAX_GROUP_NAME               256     // 40

#define MAX_KSTR                     100

#include "classwin.hpp"
#include "beton.h"
//#include "baseclass.hpp"

 /* структура документа 11 (минимальное армирование)*/

struct  ARMATUR_MINIMUM
{
        double  NumSech;      //   номер последнего сечения с заданным мин. ар-ем
        double  AreaAs1;      //   площадь заданной аpматуpы AS1
        double  AreaAs2;      //   площадь заданной аpматуpы AS2
        double  AreaAs3;      //   площадь заданной аpматуpы AS3
        double  AreaAs4;      //   площадь заданной аpматуpы AS4
        double  AreaClampFZ;  //   площадь заданных хомутов FZ
        double  StepClampFZ;  //   шаг хомутов FZ
        double  AreaClampFY;  //   площадь заданных хомутов FY
        double  StepClampFY;  //   шаг хомутов FY
        double  Res[2];       //
};

struct  ARMATUR_DATA_STR
{
//     группа
       BYTE              Modul;           // номер модуля
       BYTE              Type;            // статически определимые(1) или неопределимые(0)
       BYTE              CrackResisting;   // Данные по трещиноустойчивости 0 - нет, 1 - есть
       BYTE              MinArmatur;      // Данные по минимальной арматуре. 0 - нет, 1 - есть
       BYTE              YesExpert;       //  Данные по экспертизе 0 - нет, 1 - есть
       BYTE              YesLengthOfFactor;  //  расчетная длина, 0 - Length, 1 - Factor
       BYTE              ResByte[2];

       double            Range[4];        // расстояние до центра тяжести арматуры
       double            EffectiveLength[2];  //  расчетная длина
       double            FactorEffectiveLength[2];  //  коэффициент расчетной длины
       double            Displacement[2]; //  случайный эксцентриситет
       double            SeismFactor[2];  //  коэффициенты учета сейсмического воздействия
       double            ResD[2];

//     бетон
       BYTE              TypeBeton;       //  вид бетона, порядковый номер диалога
       BYTE              ConditionsHardening; // условия твердения, порядковый номер диалога
       BYTE              Filler;          // заполнитель, порядковый номер диалога
       BYTE              ResByte2;        //
       char              ClassBeton[16];  //  класс бетона
       char              SortBeton[16];   //  марка бетона по средней плотности
       double            FactorHardening; // коэффициент условий твердения
       double            FactorForce;     // коэффициент учета нагрузок длительного действия
       double            FactorTotal;     // результирующий коэффициент
       double            ResD2[2];

//     арматура
       char              ClassArm[2][16]; // класс продольной и поперечной арматуры
       double            FactorWork[2];   // коэффициентs условий работы продольной и поперечной арматуры
       double            MaxDiam;         // макс. диаметр углового стержня
       double            MaxProcent;      // макс.процент армирования
       double            ResD3[2];

//     трещиностойкость
       BYTE              Category;       // категория трещиностойкости
       BYTE              ConditionsOperation;  // условия эксплуатации, порядковый номер диалога
       BYTE              RegimeBeton;    // режим влажности бетона, порядковый номер диалога
       BYTE              Dampness;       // влажность воздуха, порядковый номер диалога
       BYTE              YesSeicmRSU;    //  Учитывать РСУ с сейсмикой
       BYTE              Res3[3];
       double            DiamRod[2];     // диаметры стержней
       double            WidthCrack[2];  //   ширина раскрытия трещин
       double            Interval;       //   Расстояние до крайноего ряда
       double            ResD4[2];
};

struct ARMATUR_STR {

       LPSTR             Text;

       int               Quantity;
       int             * List;
       int               QuantityStr;
       ARMATUR_MINIMUM * ArmaturMin;

//     группа
       ARMATUR_DATA_STR  Data;
};

class   ARMATURA : public SCAD_BASE_CLASS
{
public:

    ARMATURA()      {  Init();    }
   ~ARMATURA(void)  {  Destroy();  }

void Init()  {
         SCAD_BASE_CLASS::Init(0,0,sizeof(ARMATUR_DATA_STR),sizeof(ARMATUR_DATA_STR),2,10);
         LenData[0] = sizeof(int);
         LenData[1] = sizeof(ARMATUR_MINIMUM);
         }

inline   ARMATUR_STR  * GetGroup( int n ) {  return (ARMATUR_STR *)GetObject(n); };
void    SCHEMA_EXPORT   GetTextGroup( int Num, LPSTR Buf, int MaxLenText );

int     SCHEMA_EXPORT   Include( LPSTR Text, ARMATUR_DATA_STR &Data, int Qnt, int * Lst,  int QntAM, ARMATUR_MINIMUM *);

void     SCHEMA_EXPORT  Change( int Num, LPSTR Text, ARMATUR_DATA_STR &, int Qnt,int *Lst, int QntAM, ARMATUR_MINIMUM  * );
void     SCHEMA_EXPORT  ChangeData( int Num, ARMATUR_DATA_STR &GroupData);

void     SCHEMA_EXPORT  Compress( int QntOld, int NewNumber[] );

void     SCHEMA_EXPORT  Add( ARMATURA &, int Quantity, int NumNew[] );

void     SCHEMA_EXPORT  Export( int NumDoc, FILEPRINT &Work );
void     SCHEMA_EXPORT  Print( void *Inp, int NumDoc, int NumHead );

void     SCHEMA_EXPORT  ConvertInOld( BETON & );
void     SCHEMA_EXPORT  ConvertBeton( BETON & );
void     SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control );

void     SCHEMA_EXPORT  WriteOld( FILEBASE &FilePrj, DOCUMENT &Doc );

};

#pragma pack(pop)
#endif
