#ifndef VK_POLY_FLAG_H
#define VK_POLY_FLAG_H
#pragma pack(push,1)

class VK_POLY:  MEMORY
{
public :
	  int Order;
      double *Coef;

       VK_POLY() {  Coef = NULL;  Order = 0;  };
      ~VK_POLY() {  Delete(); };

void    CLASS_EXPORT   Init( int OrderIn, double *CoefIn=NULL );
void    CLASS_EXPORT   Init( VK_POLY &P );

void    CLASS_EXPORT   Delete();
void    CLASS_EXPORT   Add( double a1, VK_POLY &P1, double a2, VK_POLY &P2 );
void    CLASS_EXPORT   Add( double a, VK_POLY &P );
void    CLASS_EXPORT   Mult( VK_POLY &P1, VK_POLY &P2 );
void    CLASS_EXPORT   Mult( VK_POLY &P );
void    CLASS_EXPORT   Mult( double Q );
void    CLASS_EXPORT   Dif( int Step, VK_POLY &P );

double  CLASS_EXPORT   Value( double x );
double  CLASS_EXPORT   ValueDif( double x );

VK_POLY & operator = ( VK_POLY &P ) {  Init(P);  return *this;	}

};

#pragma pack(pop)
#endif


