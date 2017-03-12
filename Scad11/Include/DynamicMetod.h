#ifndef DYNAMIC_METOD_FLAG_H
#define DYNAMIC_METOD_FLAG_H

struct  DYNAMIC_METOD
{
       BYTE    TypeMetod;     // 0 -  Итерации подпространств,
                               // 1 -  наискорейшего спуска, 2 - Ланцош
        BYTE    YesDiapazon;   // 1 - Yes  Запрещен для сейсмики
        BYTE    YesProcMass;   // 1 - Yes (только для сейсмики)
                               // При отметке взять вначале умалчиваемые значения
                               // из ini файла. Секция [ScadCalcul],
                               // параметр DynamicProcMass   90, 90, 75
        BYTE    ResByte[3];    //     резерв
        double  MinD;          //  значения диапазона
        double  MaxD;
        double  ProcentX;      // только для сейсмики
        double  ProcentY;
        double  ProcentZ;
        double  Shift;        //  сдвиг при вычислении собственных частот для модуля 100
                              //  добавить в окно "модальный анализ". По умолчанию - 0.
        int     BlockSizeLanzos;        //  из ini файла. Секция [ScadCalcul],
                                        //  параметр BlockSizeLanzos, по умолчанию 3.
        int     MaxNumberLanzosVector;  //  из ini файла. Секция [ScadCalcul],
                                        //  параметр MaxNumberLanzos, по умолчанию 150.
        int     NumberIntervalLanzos;   //  из ini файла. Секция [ScadCalcul],
                                        //  параметр NumberIntervalLanzos, по умолчанию 20.

        int     ResI;
        double  Res[10];
};

#endif
