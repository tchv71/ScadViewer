#ifndef S_GAUSS_FLAG_H
#define S_GAUSS_FLAG_H
#pragma pack(push,1)

#define MAX_MATR_COS_ORDER 9*9

struct EQUATION_STR
{
	long  NumBeg;                  // начальный номер коэффициента уравнения
	long  NumEnd;                  // конечный номер коэффициента уравнения
//	long  Pos;                     // номер коэффициента уравнения в списке
	long  DeltaPos;                // разность номера и позиции коэффициента уравнения NumBeg
};

struct EQUATION
{
   long         Length;           // длина данных уравнения
   long         QuantityStr;      // число структур EQUATION_STR ( > 0 )
   long         QuantityDbl;      // число коэффициентов, хранящихся в уравнении
   long         PosDouble;        // позиция коэффициентов
   long         Except;           // номер последнего исключенного уравнения
   long         PosStr;           // номер структуры EQUATION_STR, с которой начинается
                                  //    обработка уравнений, не вошедших в блок
	char         gis;              // =1 - геометрическая изменяемость
	char         Zero;             // =1 - все числа уравнения равны нулю. Корректируется
                                  //      на прямои ходе
   char         Res[2];           //
	double       mim;              // Минимум на диагонали
   EQUATION_STR Str[1];           // В Str[0].NumBeg находится всегда номер уравнения
                                  // В Str[QuantityStr-1].NumEnd - номер последнего столбца
};

struct GAUSS_WORK  {
	long   NumBegin;
	long   NumEnd;
   long   Res[3];
   BYTE * Zero;
   BYTE * GIS;
};

#pragma pack(pop)
#endif
