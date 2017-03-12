#ifndef PROFILE_FULL_FLAG_H
#define PROFILE_FULL_FLAG_H
#pragma pack(push,1)

struct STRING_PROFILE
{
         int              Group;
         int              GroupS;

         int              QuantityData;

         int              QuantityGeom;
         double         * Geom;

         WORD             NumSection;
         WORD             NumString;
         char             NameBase[MAXPATH];
         char             FileSection[16];
         char             NameSection[MAX_SECTION_NAME];
         char             NameString[MAX_STRING_NAME];

         float E;
         float nu;
         float ro;

         float b;
         float h;
         float s;
         float t;
         float g;   // расстояние между спаренными уголками
         float d;
         float R;
         float r;
         float hs;
         float Gamma;  //  угол наклона полок

         float x0;
         float y0;
         float xm;
         float Alfa;
         float TanAlfa;

         float Ix;
         float Wx;
         float ix;
         float Sx;

         float Iy;
         float Wy;
         float iy;
         float Sy;

         float Ixy;

         float Ix1;
         float Wx1;
         float Sx1;
         float ix1;

         float Iy1;
         float Wy1;
         float Sy1;
         float iy1;

         float Wplx;
         float Wply;

         float A;
         float nA;
         float P;

         float JX;
         float JY;
         float Ikr;
	         float IFx;
         float IFy;
         float Iom;

         float x1;
         float x2;
         float y1;
         float y2;

         float Riska[10];
         float BoltMaxDiam[10];
         float PosBolt[10];

         float n1;
         float n2;

         float WxMin;
         float WxMax;
         float WyMin;
         float WyMax;

         char  Mask;
         short TypeInGroup;

         char  TypeConstr;   //   тип соединения для конструктора
         float Delta;        //   зазор соединения или размер по Z
         float Betta;        //   размер по Y для 4-х уголков
         float IkrConstr;    //

         float Res[16];

};

#pragma pack(pop)
#endif
