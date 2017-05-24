#include <stdafx.h>
#include <classwin.h>

EXPORT float LitTabl( float Arg, int Ind )
{

static float LitTablT[4][14] = {
//   Писаренко Г.С. и др. Справочник по сопротивлению материалов. С.238
 /* values n: */	{  1,      1.5,     1.75,    2,     2.5,    3,      4,
                           6,        8,     10,    1000 },
 /* values dtheta: */	{ 0.208,  0.231,  0.239,  0.246,  0.256,  0.267,  0.282,
                          0.299,  0.307,  0.313,  0.333  },
 /* values eta:	*/	{ 0.141,  0.196,  0.214,  0.229,  0.249,  0.263,  0.281,
                          0.299,  0.307,  0.313,  0.333  },
 /* values ksi: */	{ 1.0,    0.859,  0.820,  0.795,  0.766,  0.753,  0.745,
                          0.743,  0.742,  0.742,  0.743 }
                              };

        return Interpol(Arg,LitTablT[0],LitTablT[Ind],11);

}