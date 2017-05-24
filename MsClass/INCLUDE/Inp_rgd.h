#ifndef INFRGD_FLAG_H
#define INFRGD_FLAG_H

#pragma pack(push, 1)
struct INFRGD {
			 char *f_rgd;
			 WORD k_rgd;
			 char  i_rgd;  };

#define F_RGD(i)  infrgd[i].f_rgd
#define K_RGD(i)  infrgd[i].k_rgd
#define I_RGD(i)  infrgd[i].i_rgd

#define RF_RGD    infrab->f_rgd
#define RK_RGD    infrab->k_rgd
#define RI_RGD    infrab->i_rgd

#define CF(I)  f[(I)].b
#define FH(I)  f[(I)].d

      struct UG {  char name[4], p, i;  };
#define UGNAME(i) ug[i].name
#define UGP(i)    ug[i].p
#define UGI(i)    ug[i].i

UG **RigidCornerUG();
BYTE RigidCorner(BYTE TypeRigid, LPCSTR Type );
EXPORT UG * RigidCorner(BYTE TypeCorner);
UG **RigidCornerNaprUG();
BYTE RigidCornerNapr(BYTE TypeRigid, LPCSTR Type );
EXPORT UG * RigidCornerNapr(BYTE TypeCorner);

#pragma pack(pop)
#endif