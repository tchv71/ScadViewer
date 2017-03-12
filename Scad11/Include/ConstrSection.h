#ifndef CONSTR_SECTION_FLAG_H
#define CONSTR_SECTION_FLAG_H

// profile database structure
#define MAX_PROFILE_NAME 20

struct PDB 
{
   short   ID;
   char    NAME[MAX_PROFILE_NAME];

   char    FilePRF[9];
   char    SectionFile[9];
   WORD    SecNo;
   long    Reserv;
   
   short   SHAPE_TYPE;
   double  H;
   double  B;
   double  EA;
   double  ES;
   double  RA;
   double  RS;
   double  SX;
   double  IX;
   double  IY;
   double  IZ;
   double  VY;
   double  VPY;
   double  VZ;
   double  VPZ;
};

struct SectionPart
{
   struct  PDB PDB;
   double  x;
   double  y;
   double  Angle;
   int	   Mirror;
};

#define MAX_PARTS 50

struct SectionData
{
   short   nParts;
   struct  SectionPart Parts[MAX_PARTS];
};

#endif