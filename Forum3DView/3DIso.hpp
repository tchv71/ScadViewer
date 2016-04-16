// Прототипы для Презентационной графики отображения изополей

#ifndef _3DISO_HPP
#define _3DISO_HPP
#pragma pack(push,1)
enum eTypeData
{
	Iso_Nothing=0,	// ничего не отображать только схема
	Iso_Disp,		// перемешщения
	Iso_Nap,		// поля напряжений
	Iso_Nap_Flat,	// поля напряжений ("клеёнка")
	Iso_Arm,		// Поля арматуры
	Iso_Lit,		// Поля главных/эквивалентных напряжения
	Iso_Energy		// Поля энергии
};

struct TypeInformationOnSchema
{
	BYTE NumFactor; // Оцифровка фактора
	BYTE NumElem;   // Нумерация элементов
	BYTE NumNode;   // Нумерация узлов
	BYTE OutSupport;// Отображение связей
	BYTE OutNode;   // Отображение узлов
}; // 1 - отображать

enum EIntegralFunc
{
	EIF_AVG,
	EIF_MIN,
	EIF_MAX,
	EIF_MAXMIN
};

//HWND __declspec(dllimport) OGL_3DIso(RESULT *Res, // Указатель на класс результатов
//									 int NPr,     // Номер правой части
//									 struct DefMapInfo *Scale, // Указатель на цветовую шкалу 
//									 eTypeData TypeData, // Тип отображаемой информации
//									 int TypeFactor,     // Вид отображаемой информации (зависит от типа)
//									 struct TypeInformationOnSchema *TypeInfo, // Тип информации отображаемой на схеме
//									 HWND hWndParent    // Родительское окно
//									 );
#define OGL_SETFACTOR 0x500 // Установка отображаемого фактора для текущего типа информации 
							// WPARAM  - TypeFactor, LPARAM 0
#define OGL_SETSCALE  0x501 // Установка шкалы WPARAM - 0 LPARAM struct *DefMapInfo
#define OGL_SETTYPEDATA 0x502 // Установка типа отображаемой информации
							  // WPARAM - eTypeData TypeData, LPARAM 0
#define OGL_SETOUTINFO 0x503  // Установка типа информации отображаемой на схеме
							  // WPARAM - 0 LPARAM 	struct *TypeInformationOnSchema

#pragma pack(pop,1)

#endif