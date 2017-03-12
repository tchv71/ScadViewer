#ifndef SCADHASP_H
#define SCADHASP_H

#include <windows.h>
#include <time.h>
#include "hasp.h"

#define MAX_CUSTOMER_NAME_HASP 71
/*
   Номера подсистем:
      0 - Нелинейность
      1 - Расчетные сочетани
      2 - Комбинации загружений
      3 - Устойчивость
      4 - Армирование
      5 - Документатор
      6 - Литера
      7 - Спектры
      8 - Фундамент
      9 - КРИСТАЛЛ
     10 - КОМЕТА
     11 - AutoCAD
     12 - Сечени
     13 - АРБАТ
     14 - Металл
     15 - Монолит
     16 - Сечения 2
     17 - Еврокод
     18 - Фермы
     19 - Основани
     20 - АЧХ
     21 - Вариации моделей
     22 - СЕЗАМ
     23 - FORUM
     24 - ВЕСТ
*/
extern struct SCADProtection
{
   WORD  ControlSum;    // контрольная сумма
   WORD  TRIALPeriod;   // длительность TRIAL периода в днях
   WORD  SCADMode;      // 0 - заказ; 1 - trial; 2 - полна
   time_t StartTrial;   // время начала trial периода
   time_t LastTrial;    // время последней активации SCAD,
   char  SubSystems[8]; // биты подсистем
                        // работающего в trial режиме
   char  Serial1[8];    // серийный номер 1
   char  Serial2[8];    // серийный номер 2
   char  Limit;         // 0 - 32000, 1 - Unlimited, 2 - Junior, 3 - 750x750
   char  Customer[MAX_CUSTOMER_NAME_HASP];   // название фирмы-покупател
   WORD  Version;       // Верси
} Protect;

#define SCADPASSWORD1   28455
#define SCADPASSWORD2   26190
#define SCADSeedCode1   1956
#define SCADSeedCode2   1987
#define PASSWORD        101

BOOL IsSCADHasp(void);
BOOL ReadSCADHasp(void);
void HASPError(int Status);
BOOL CALLBACK AskPasswordDlg(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK PayMeDlg(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
void UpdateHASP(void);
BOOL IsRgmEnabled(SCHEMA *Prj);
void  HASPDisconnect(void);

#endif
