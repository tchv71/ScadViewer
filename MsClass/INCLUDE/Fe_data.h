#ifndef FE_DATA_H
#define FE_DATA_H
#pragma pack(push, 1)

struct FE_DATA
{       

       void              * Calc;
       long                OrderSys;

       void (*PutMsg)    (int...);
       void (*PutMsgFE)  (int Num,int NQ);
       void (*PutMsgStep)(int Num...);

       SCHEMA            * Schem;
       FORMAT            * FormatFE;
       LOAD_LIST         * LoadFE;
       LOAD_COMBINATION  * LoadComb;
       LOAD_COMBINATION  * LoadCombFull;

       FE_COORD          * CoordEl;
       WORD              * JointEl;
       double            * RigidEl;
       long              * StepEl;
       FE_FORCE          * ForceEl;
       double            * ForceValue;

       double            * Matr;
       double              MKA[15*15];
       short               OrderMK;  

       double            * Force;

       double            * Displace;       // Iteration Step
       double            * Reak;           // Step
       double            * Us;             // Step 

       short               QuantityPoint;  // for LN Rod
       double            * CoordX;

       LPSTR               AddFormat;
       STEP_LOAD         * pSL;
       short               NumIter; 

       double            * DisplaceFull;
       double            * UsFull;
       double            * ReakFull;
       double            * Differ;
       double            * DifferForce;

       double              Epsilon;
       BYTE                EndIter;

       void              * Value2;
       void              * Value3;

       BYTE                TypeEfforsLayer;
};
#pragma pack(pop)

#endif
