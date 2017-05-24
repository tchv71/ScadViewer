#ifndef AMPLITUDE_FLAG_H
#define AMPLITUDE_FLAG_H

// Режим - 4
// Вход: файл .F15 в начале которого заголовок AMPLITUDE
// Выход: файл .F15 в котором после заголовка AMPLITUDE следуют графики,
//               позиции которых указаны в Pos для соответствующего узла
//               по задействованным направлениям
#pragma pack(push, 1)
struct AMPLITUDE
{
   WORD   NumLoadDyn;
   WORD   NumLoadGroup;
   WORD   QuantityNode;    //  <= 10
   WORD   NumNode[10];
   double Depl;     // коэффициент внутреннего трения
   double MinChast;
   double MaxChast;
   double DeltaChast;

// выход
   long   QuantityPoint;
   long   QuantityChast;
   DWORD  PosChast;
   DWORD  Pos[10][3];
};
#pragma pack(pop)
#endif

