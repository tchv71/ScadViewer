#include "windows.h"

class SCAD_NODE
{
public:

	  double x;
     double y;
     double z;
     int nNode;
     BYTE   Sel;

	  SCAD_NODE();                   // Constructor
     virtual ~SCAD_NODE();          // Destructor

     SCAD_NODE( const SCAD_NODE &Src); // Copy constuctor
     SCAD_NODE & operator =(const SCAD_NODE &Src);
     void Set(CK &Uz,double Precision,int n);
     bool operator >(const SCAD_NODE &Frst) const;
     bool operator <(const SCAD_NODE &Frst) const;
     bool operator ==(const SCAD_NODE &Frst)const;

private:

     double Prec;
};

