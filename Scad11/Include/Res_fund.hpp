#ifndef RESULT_FUND_FLAG_H
#define RESULT_FUND_FLAG_H
#pragma pack(push,1)

#include <result.hpp>

class RESULT_FUND : RESULT
{
public:
       FILEWORK      FileFund;
       FILEWORK      FileFundComb;
       double      * Force;
       int           NumStrTableLoad;

       RESULT_FUND()  {   memset(this,0,sizeof(RESULT_FUND));  }
      ~RESULT_FUND()  {   Delete(); }

RESULT_EXPORT  void     Init();
RESULT_EXPORT  int      Init( RESULT & );
RESULT_EXPORT  void     Delete();
RESULT_EXPORT  int      GetForce( int NumStrTable, BYTE Type);
RESULT_EXPORT  double * GetForceNode( int NumStrTabl, int NumNode );
RESULT_EXPORT  double * GetForceNodeIn( int NumNode );
RESULT_EXPORT  double * GetFullForceNode( int NumNode, BYTE *MaskLoad, BYTE Type );
RESULT_EXPORT  void     SetUnitsOut(UNITS Un[]) { RESULT::SetUnitsOut(Un);  };

};

#pragma pack(pop)
#endif
