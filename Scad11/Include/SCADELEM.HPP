#ifndef SCAD_ELEM_FLAG_H
#define SCAD_ELEM_FLAG_H

#pragma pack(push,1)

class SCAD_ELEM
{
public:
     int      NumElem; 
	 SCHEMA * Schem;
	 WORD   * TypeJoint;
	 BYTE     EqualTypeElem;
	 BYTE     EqualRigid;

	 SCAD_ELEM();                   // Constructor
     virtual ~SCAD_ELEM();          // Destructor

     SCAD_ELEM( const SCAD_ELEM &Src); // Copy constuctor
     SCAD_ELEM & operator =(const SCAD_ELEM &Src);
     void Set( int Num, SCHEMA *pS, BYTE ET, BYTE ER, WORD *TJ );
     bool operator >(const SCAD_ELEM &Frst) const;
     bool operator <(const SCAD_ELEM &Frst) const;
     bool operator ==(const SCAD_ELEM &Frst)const;

};

#pragma pack(pop)

#endif
