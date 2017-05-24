#include <stdafx.h>
#include <classwin.h>
#include <inp_rgd.h>

UG **RigidCornerUG() {

	static UG UgRod[] = { "F",  'F', 1, "FR",  'R', 1, "FK",  'K', 3, "FD",  'D', 3,
		"FS",  'S', 3,  //  аналогично К с поворотом на 90
		"FG",  'G', 3,  //  аналогично D с поворотом на 90
		""  };
	static UG UgPl[]  = { "EX", 'X', 3, "EXM", 'M', 2, "EXT", 'T', 3, "FI",  'F', 1, "FIR", 'R', 1, ""  };
	static UG UgVl[]  = { "EX", 'X', 6, "EXM", 'M', 6, "FI",  'F', 3, "FIR", 'R', 3,
		"EZ", 'Z', 6,  //  цилиндр. Задаются две точки
		"ES", 'S', 6,  //  сфер. Задаются две точки
		"EV", 'V', 6,  //  цилиндр. Задаются точка и направление
		"EW", 'W', 6,  //  сфер. Задаются точка и направление
		""  };
	static UG *Ug[] = {  UgRod, UgPl, UgVl };
	return Ug;
}

BYTE RigidCorner(BYTE TypeRigid, LPCSTR Type ) {

     UG **Ug = RigidCornerUG();
     if ( TypeRigid && TypeRigid < 4 )
	for ( WORD k=0; Ug[TypeRigid-1][k].name[0]; k++ )
	   if ( strcmp(Type,Ug[TypeRigid-1][k].name) == 0 )
	      return 16 * TypeRigid + k;
     return 0;
}

EXPORT UG * RigidCorner(BYTE TypeCorner )
{
     UG **Ug = RigidCornerUG();
     if ( TypeCorner < 16 ) return &Ug[0][TypeCorner];
     return &Ug[TypeCorner/16-1][TypeCorner%16];
}

UG **RigidCornerNaprUG() {

	static UG UgPl[]  = { "XN", 'X', 3, "XNM", 'M', 2, "XNT", 'T', 3, "AL",  'F', 1, "ALR", 'R', 1, ""  };
	static UG UgVl[]  = { "XN", 'X', 6, "XNM", 'M', 6, "AL",  'F', 3, "ALR", 'R', 3,
		"XZ", 'Z', 6,  //  цилиндр. Задаются две точки
		"XS", 'S', 6,  //  сфер. Задаются две точки
		"XV", 'V', 6,  //  цилиндр. Задаются точка и направление
		"XW", 'W', 6,  //  сфер. Задаются точка и направление
		""  };
	static UG *Ug[] = {  UgPl, UgVl };
	return Ug;
}

BYTE RigidCornerNapr(BYTE TypeRigid, LPCSTR Type ) {

     UG **Ug = RigidCornerNaprUG();
     if ( TypeRigid > 1 && TypeRigid < 4 )
	for ( WORD k=0; Ug[TypeRigid-2][k].name[0]; k++ )
	   if ( strcmp(Type,Ug[TypeRigid-2][k].name) == 0 )
	      return 16 * TypeRigid + k;
     return 0;
}

EXPORT UG * RigidCornerNapr(BYTE TypeCorner )
{
     UG **Ug = RigidCornerNaprUG();
     if ( TypeCorner < 32 ) return &Ug[0][TypeCorner];
     return &Ug[TypeCorner/16-2][TypeCorner%16];
}