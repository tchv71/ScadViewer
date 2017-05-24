#ifndef S_DEFS8_FLAG_H
#define S_DEFS8_FLAG_H
#pragma pack(push, 1)

#define f    f8_x[0]
#define sz0  f8_x[1]
#define sy0  f8_x[2]
#define iu   f8_x[3]
#define iv   f8_x[4]
#define iuv  f8_x[5]
#define imax f8_x[6]
#define imin f8_x[7]
#define y0   f8_x[8]
#define z0   f8_x[9]
#define iy   f8_x[10]
#define iz   f8_x[11]
#define ff   f8_x[12]
#define b(i) f8_x[13 + 4 * i]
#define h(i) f8_x[13 + 4 * i + 1]
#define y(i) f8_x[13 + 4 * i + 2]
#define z(i) f8_x[13 + 4 * i + 3]

#pragma pack(pop)
#endif