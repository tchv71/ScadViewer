#pragma pack(push,1)
  struct   D3MG   {
     char ptg[4];    /* Признак =   "**MG**"          */
     BYTE  ksw;      /* Число степеней свободы узла   */
     BYTE  nsw[15];  /* Номера степеней свободы узла  */
     BYTE  mk;       /* Тип матрицы косинусов         */
     short  kmg;      /* Число чисел в MG              */
     char type;      /* Тип файла: 'Z' - расширение .aez в текстовом виде
				   'M' - расширение .aem в виде F04.*     */
     char name[MAXPATH];  /* Имя файла                     */
     double mg[1];    /* Матрица жесткости, если есть  */
     };

#define  MGPTG     pd3mg->ptg
#define  MGKSW     pd3mg->ksw
#define  MGNSW(i)  pd3mg->nsw[i]
#define  MGMK      pd3mg->mk
#define  MGKMG     pd3mg->kmg
#define  MGTYPE    pd3mg->type
#define  MGNAME    pd3mg->name
#define  MGMG(i)   pd3mg->mg[i]
#pragma pack(pop)

