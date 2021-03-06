#ifndef STEEL_FLAG_H
#define STEEL_FLAG_H
#pragma pack(push,1)

#include "ClassWin.hpp"
//#include "profile.h"
#include "BaseClass.hpp"

#define MAX_STRING_STEEL_NAME  80

struct STEEL_DATA
{
	char   SteelMark[MAX_STRING_STEEL_NAME];  // ����� �����
	double Ry;                                // ��������� ������������� Ry
	double Koef_nad;                          // ����. ���������� �� ����������
	double Koef_usl_rab;                      // ����� ������� ������
	double Lim_gibk;                          // ���������� ��������
};

struct STEEL_ELEMENT
{
	BYTE   What_is;                  // 0 - �������������� ������� 1 - ������ ���������
	WORD   ContructionType;
	double Koef_RasLen_XoZ;          // ����. ����.����� � ��������� XoZ
	double Koef_RasLen_YoZ;          // ����. ����.����� � ��������� YoZ
	double Lim_gibkA;                // ���������� �������� ��� ������
	double Lim_gibkB;                // ���������� �������� ��� ������
	double Res[5];
	int    ResI[2]; 
	
};

struct STEEL_STR {
       LPSTR          Text;
       int            Quantity;
       int          * List;
       STEEL_DATA     Data;
       STEEL_ELEMENT  SteelEl;
};


class STEEL : public SCAD_BASE_CLASS
{
public:

	STEEL() {  Init();  }
  ~STEEL(void) {
     Destroy();  }

void           Init()  {
                  int Len = sizeof(STEEL_ELEMENT) + sizeof(STEEL_DATA);
                  SCAD_BASE_CLASS::Init(sizeof(STEEL_DATA),sizeof(STEEL_DATA),Len,Len,1,20);
                  LenData[0] = sizeof(int);   }

SCHEMA_EXPORT  int    Include( STEEL_ELEMENT &, STEEL_DATA &, int Qnt, int *Lst );
SCHEMA_EXPORT  void   Change( int NumPP, STEEL_ELEMENT &, STEEL_DATA &, int Qnt, int *Lst );

STEEL_STR  *   Get(int NumPP) { return (STEEL_STR *)SCAD_BASE_CLASS::GetObject(NumPP);  }
SCHEMA_EXPORT  void   GetSteel( int NumPP, STEEL_ELEMENT **, STEEL_DATA **, int &Qntt, int ** Lst );

int  SCHEMA_EXPORT    GetQuantityGroup(){ return Quantity;  }
SCHEMA_EXPORT  STEEL_DATA *  GetSteelData() { return (STEEL_DATA*)GetCommon();  }
void           SetSteelData( STEEL_DATA &SD ) { SetCommon(&SD);  };
SCHEMA_EXPORT  void   Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control );
SCHEMA_EXPORT  void   Export( FILEPRINT &);

void           ReadOld( FILEBASE &FilePrj, DOCUMENT &Doc );
};

#pragma pack(pop)
#endif
