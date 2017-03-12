#ifndef TABLE_LOAD_FLAG_H
#define TABLE_LOAD_FLAG_H
#pragma pack(push,1)

struct  LOAD_NAME {
		 short ls;
		 short ngs;
		 char s[1000];
		 };

struct TABLE_LOAD {
		 BYTE  TypeInf;
		 WORD  TypeLoad;
		 WORD  NumLoad;
		 WORD  NumSchemUnite;     //  номер задачи вариации 
		 WORD  NumLoadSchemUnite; //  номер загружения в задаче вариации 
		 WORD  NumStep;           //  Шаг для нелинейного процесса 
		 WORD  NumFixedStep;      // номер п/п сохранения в шаговом процессе 
		 WORD  QuantityForm;
		 WORD  NumForm;
		 LONGLONG Pos;
		 LPSTR Name;
		 };

#pragma pack(pop)
#endif
