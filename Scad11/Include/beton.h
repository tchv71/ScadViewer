#ifndef BETON_FLAG_H
#define BETON_FLAG_H

#define MAX_PROJECT_NAME 128
#define MAX_CONSTRUCTION_NAME 	     40
#define MAX_NODE_NAME 	              40
#define NODE_SENCETIVE   	            3
#define MAX_QUANTITY_GRAF_FILE_NODE    4
#define MAX_COMPANY_NAME 		        40
#define MAX_CUSTOMER_NAME 		        40
#define MAX_OBJECT_NAME 		        40
#define MAX_GROUP_NAME               256     // 40
#define MAX_KSTR                     100

struct  ARMATUR_DATA
{
	float ProtectA1;           /*  Protection layout A1        */
	float ProtectA2;           /*  Protection layout A2        */
	float Length_XZ;           /*  Calc. length XoZ            */
	float Length_YZ;           /*  Calc. length YoZ            */
	float Excent_Y;            /*  Random. execentrisity in Y1 */
	float Excent_Z;            /*  Random. execentrisity in Z1 */
	short TypModul;            /*  The Type of reinforce modul */
	DWORD IniTresk;            /*  Flag of calculation of tresk*/
	float SeismNorm;           /*  The coeffisient of seismic for normal sections */
	float SeismIncl;           /*  The coeffisient of seismic for inclan. sections*/
	DWORD StaticDef;           /*  Static definition flag      */

	/****************** Beton *****************************/
	short BetonClass;
	short BetonVid;
	short BetonMark;
	short BetonZapol;
	short BetonCond;
	short BetonGb2;
	float BetonRezKoef;
	short BetonTverd;
	float BetonTverKoef;
	/****************** Reinforce *************************/
	short ArmatClassPro;
	short ArmatClassPop;
	float ArmatProKoef;
	float ArmatPopKoef;
	/*********************  *********************/
	float ArmProcMax;  // max % armirovaniya

	DWORD NewData; // priznak novix dannix         // ArmatDiamPop;  //
	float KoefLength_XZ; // Koef. Calc. length XoZ      ArmatSquerOt
	float KoefLength_YZ; // Koef. Calc. length YoZ      ArmatAngleOt
	DWORD IniLength;     // flag 1-length, 0-koef short ArmatDiamMin,ArmatDiamMax
	short ArmatVid;
	/*********************Tresk****************************/
	short TreskCateg;
	short TreskCondEx;
	short TreskBetonVlag;
	short TreskVlaga;
	float TreskShort;
	float TreskLong;
	short TreskArmPro;
	short TreskArmPop;
	float TreskProtect;
	/*********************Proverka Zadan Arm****************************/
	DWORD IniZadAr;            /*  Flag of Proverka Zadan Arm*/
   short QuanZadAr;
   float ArmPr[MAX_KSTR][9];
   /******************** New  Data ***********************************/
	float ProtectA3;           /*  Protection layout A3        */
	float ProtectA4;           /*  Protection layout A4        */
   DWORD TreskOsob;
   DWORD TreskSeis;
   DWORD ArmatAuto;           // при расчете по прочности выбирать к-во стержней
                              // 0- автоматически; 1- от минимального (2шт.) до максим.)
   float ArmatStep;           // при заданном шаге арматурных стержней (cм)
   WORD  ArmatNDiam;        // номер строки в combobox cоответствующий максим. диам. в строках
   WORD  Rez; // ArmatMaxDiam;      // значение максим. диаметра в мм
   float rezerv[11];          // резерв
};

struct  ARMATUR_DATA0
{
	float ProtectA1;           /*  Protection layout A1        */
	float ProtectA2;           /*  Protection layout A2        */
	float Length_XZ;           /*  Calc. length XoZ            */
	float Length_YZ;           /*  Calc. length YoZ            */
	float Excent_Y;            /*  Random. execentrisity in Y1 */
	float Excent_Z;            /*  Random. execentrisity in Z1 */
	short TypModul;            /*  The Type of reinforce modul */
	DWORD IniTresk;            /*  Flag of calculation of tresk*/
	float SeismNorm;           /*  The coeffisient of seismic for normal sections */
	float SeismIncl;           /*  The coeffisient of seismic for inclan. sections*/
	DWORD StaticDef;           /*  Static definition flag      */

	/****************** Beton *****************************/
	short BetonClass;
	short BetonVid;
	short BetonMark;
	short BetonZapol;
	short BetonCond;
	short BetonGb2;
	float BetonRezKoef;
	short BetonTverd;
	float BetonTverKoef;
	/****************** Reinforce *************************/
	short ArmatClassPro;
	short ArmatClassPop;
	float ArmatProKoef;
	float ArmatPopKoef;
	/*********************  *********************/
	float ArmProcMax;  // max % armirovaniya

	float ArmatDiamPop;  //  	DWORD NewData; // priznak novix dannix
	float KoefLength_XZ; // Koef. Calc. length XoZ      ArmatSquerOt
	float KoefLength_YZ; // Koef. Calc. length YoZ      ArmatAngleOt
	DWORD IniLength;     // flag 1-length, 0-koef short ArmatDiamMin,ArmatDiamMax
	short ArmatVid;
	/*********************Tresk****************************/
	short TreskCateg;
	short TreskCondEx;
	short TreskBetonVlag;
	short TreskVlaga;
	float TreskShort;
	float TreskLong;
	short TreskArmPro;
	short TreskArmPop;
	float TreskProtect;
	/*********************Proverka Zadan Arm****************************/
	DWORD IniZadAr;            /*  Flag of Proverka Zadan Arm*/
   short QuanZadAr;
   float ArmPr[MAX_KSTR][9];
};

struct  ARMATUR_NEWDATA
  {
	float ProtectA3;           /*  Protection layout A3        */
	float ProtectA4;           /*  Protection layout A4        */
   DWORD TreskOsob;
   DWORD TreskSeis;
   DWORD ArmatAuto;           // при расчете по прочности выбирать к-во стержней
                              // 0- автоматически; 1- от минимального (2шт.) до максим.)
   float ArmatStep;           // при заданном шаге арматурных стержней (cм)
   WORD  ArmatNDiam;        // номер строки в combobox cоответствующий максим. диам. в строках
   WORD  Rez;  // ArmatMaxDiam;      // значение максим. диаметра в мм
   float rezerv[11];          // резерв  (было float [16],  14 )
  };

   struct GROUP_LIST
{
	char         Name[MAX_GROUP_NAME]; /*  name of group               */
	ARMATUR_DATA Data;
	WORD        Quantity;  // к-во элементов группы
	WORD  * List;          // массив с номерами  Ё группы (по к-ву элементов группы)
	LPSTR        Text;     // строка char со списком элементов
};


class   BETON : private MEMORY
{
private :

	char 	          Name[MAX_PROJECT_NAME+1]; /*  name of project             */
	char 	          Company[MAX_COMPANY_NAME+1];
	char 	          Customer[MAX_CUSTOMER_NAME+1];
	char 	          Object[MAX_OBJECT_NAME+1];

	WORD              QuantityGroup;
	WORD              QuantityAllocGroup;
	GROUP_LIST  * Group;

	BYTE              Modify;

	void              Add();
public:

	BETON() {  Init();  }
	void Init() {   memset(this,0,sizeof(BETON));  }

		 ~BETON(void) {	Delete(); }
	void Delete();

	void     SetName(LPCSTR s);
inline  LPSTR    GetName() {  return Name;  }

	void     SetCompany(LPCSTR s);
inline  LPSTR    GetCompany() {  return Company;  }

	void     SetCustomer(LPCSTR s);
inline  LPSTR    GetCustomer() {  return Customer;  }

	void     SetObject(LPCSTR s);
inline  LPSTR    GetObject() {  return Object;  }

GROUP_LIST     * GetGroup(WORD n);
	int      GetGroup(WORD Num, ARMATUR_DATA *GroupData, LPSTR Text );
inline  WORD    GetQuantGroup() {  return QuantityGroup;  }

	void     SetModify(BYTE s) {Modify = s;};
inline  BYTE    GetModify() {  return Modify;  }

	LPCSTR   GetGroupName(WORD Num);
	void     SetGroupName(LPCSTR Name,WORD Num);

	WORD 	   IncludeGroup(GROUP_LIST * );
	WORD     IncludeGroup(ARMATUR_DATA &, LPCSTR Text, WORD Qnt, WORD  *Lst );

	void 	   DeleteGroup(GROUP_LIST * );
	void     DeleteGroup(WORD Num);
	void     DeleteGr(WORD Num);

	void     ChangeGroup(WORD,GROUP_LIST * );
	int      Change(WORD Num, ARMATUR_DATA &, LPCSTR Text, WORD Qnt,WORD *Lst );
   int      ChangeData(WORD Num, ARMATUR_DATA &GroupData);

	LPSTR    GetText(WORD Num);
	void     SetText(LPSTR Text,WORD Num);

   void     Write( FILEBASE &Work, DOCUMENT &Doc );
   int  	Read( FILEBASE &Work, DOCUMENT &Doc, LPSTR Bpr );

   void     Compress( WORD QntOld, WORD NewNumber[] );

};

	void     GroupCopy(GROUP_LIST*,GROUP_LIST*);

#endif
