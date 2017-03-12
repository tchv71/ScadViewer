#ifndef FE_DATA_H
#define FE_DATA_H
#pragma pack(push,8)

struct FE_DATA
{       
       void (*PutMsg)    (int...);
       void (*PutMsgFE)  (int Num,int NQ);

       void              * Calc;         //  класс CALCUL
       SCHEMA            * Schem;
       FORMAT            * FormatFE;

       RSN_STR           * LoadComb;
       RSN_STR           * LoadCombFull;

       FE_COORD          * CoordEl;
       WORD              * JointEl;
       WORD              * JointSystemEl;
       double            * RigidEl;
       long              * StepEl;
       FE_FORCE          * ForceEl;

       double              MKA[15*15];
       short               OrderMK;  
       double            * Matr;
       double            * MatrElem;          //   матрица до умножения на МЛ
       int                 NumElemMatrBuf;    //   рабочие поля для не вычисления равных матриц, следующих друг за другом
       BYTE              * EqualMatrElem;

       double            * Force;

       int                 LengthHelp;        //  специальные поля для работы КЭ ( полиномы и т.д. )
       void              * Help;

       short               QuantityPoint;     //  координаты точек выдачи усилий в графическом постпроцессоре
       double            * CoordX;

//     Данные для нелинейного процессора  
       void              * StepData;          //  Данные нелинейного шага, зависящие от типов КЭ

       double            * Displace;          // Приращения на шаге, итерации
       double            * Reak;              // Step

       double            * DisplaceFull;
       double            * DisplaceMG;
       double            * UsFull;
       double            * ReakFull;
       double            * Differ;            //  не варьируемое изменение нагрузки на шаге (например, одност. связи)
       double            * DifferVariation;   //  изменение нагрузки на итерации (например, ванты),
	                                          //  зависимое от выбора шага

       STEP_LOAD         * pSL;               // данные шага 
       int                 NumIter; 
       int                 EndIter;
       double              Epsilon;

       BYTE                QuantityInt;  //  Для вычисления усилий в середине элемента
       BYTE                WorkStress;  //  элемент отключен при вычислении преднапряжения
       BYTE                NoForceInsert;   // Не учитывать равномерно-распред. нагрузку на вставках в стержнях

       double            * DiagMatr;       //  Диагональные значения МЖ    

       double              RotorShell;
	   FILEWORK          * FilePoly; 
	   BYTE                EfforsDynamic;  //  при наличии динамики не добавлять преднапряжение
       BYTE                Res[11];
};

#pragma pack(pop)
#endif
