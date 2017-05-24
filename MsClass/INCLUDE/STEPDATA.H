#ifndef STEP_DATA__H
#define STEP_DATA__H
#pragma pack(push, 1)

struct STEP_GROUP
{
       short NumLoad;
       short QuantityDelta;
       float Delta;
       BYTE  YesSave;
};

struct STEP_DOC
{
       short      Method;
       short      MaxIter;
       short      ClearBegin;
       short      QuantityGroup;
       STEP_GROUP Group[100];
};

struct STEP_LOAD
{
       BYTE       Clear;
       BYTE       YesSave;
       BYTE       Method;
       short      MaxIter;
       short      NumLoadStep;
       short      NumStep;
       short      NumLoadForce;
       float      Delta;
};

#pragma pack(pop)
#endif
