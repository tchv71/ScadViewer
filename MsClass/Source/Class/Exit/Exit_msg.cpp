#include <stdafx.h>
#include <classwin.h>

void EXPORT ExitMessage( DWORD Type )
{
   int Num;

	switch(Type)
	{
		case EXCEPTION_ACCESS_VIOLATION:      // "Обращение к неверному адресу памяти"
         Num =  1;   break;
		case EXCEPTION_DATATYPE_MISALIGNMENT: //	"Нарушение выравнивания";
         Num =  2; 	break;
		case EXCEPTION_BREAKPOINT:            //  "Неверная точка останова";
         Num =  3;  	break;
		case EXCEPTION_SINGLE_STEP:           //  "Неверная трассировка";
         Num =  4;	break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: //  "Выход за границы массива";
         Num = 5;		break;
		case EXCEPTION_FLT_DENORMAL_OPERAND:  //  "Ненормализованное действительное число";
         Num = 6;		break;
		case EXCEPTION_FLT_INEXACT_RESULT:    //  "Ошибочный результат пловающей операции"
         Num = 7;		break;
		case EXCEPTION_FLT_INVALID_OPERATION: //  "Ошибка плавающей арифметики";
         Num = 8;		break;
		case EXCEPTION_FLT_OVERFLOW:          //  "Переполнение с плавающей точкой";
         Num = 9;		break;
		case EXCEPTION_FLT_STACK_CHECK:       //  "Переполнение стека(плавающая арифметика)";
         Num = 10;	break;
		case EXCEPTION_FLT_UNDERFLOW:         //  "Переполнение с плавающей точкой";
         Num = 11;	break;
		case EXCEPTION_INT_DIVIDE_BY_ZERO:    //  "Деление на нуль(целочисленное)";
         Num = 12;	break;
		case EXCEPTION_INT_OVERFLOW:          //  "Переполнение целочисленное";
         Num = 13;	break;
		case EXCEPTION_PRIV_INSTRUCTION:      //  "Привилегоированная операция";
         Num = 14;	break;
		case EXCEPTION_IN_PAGE_ERROR:         //  "Ошибка страницы";
         Num = 15;   break;
		case EXCEPTION_ILLEGAL_INSTRUCTION:   //  "Недопустимая инструкция";
         Num = 16;   break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION: // "Невозможно продолжить выполнение";
         Num = 17;	break;
		case EXCEPTION_STACK_OVERFLOW:        //  "Переполнение стека";
         Num = 18;	break;
		case EXCEPTION_INVALID_DISPOSITION:   //  "Exeption ERROR";
         Num = 19;	break;
		case EXCEPTION_GUARD_PAGE:            //  "Обращение к защищенной странице";
         Num = 20;	break;
		case EXCEPTION_INVALID_HANDLE:        //  "INVALID HANDLE";
         Num = 21;
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:    //  "Деление на 0";
         Num = 22;   break;
		default:                              //  "Некорректное завершение программы";
         CrashMessage();
         Num = 51;	break;
}
   CrashMessage(NULL,Num);
}