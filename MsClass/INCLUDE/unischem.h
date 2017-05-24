#ifndef UNITE_SCHEMA_FLAG_H
#define UNITE_SCHEMA_FLAG_H

#pragma pack(push, 1)
#include <schema.h>

struct UNITE_SCHEMA_INF
{
       void * Schem;
       FILE   Mark;
       WORD   NumLoadBegin;
};

struct UNITE_SCHEMA
{
    WORD   Quantity;
    WORD   QuantityAlloc;
    int    MaxElem;
    int    MaxNode;

    UNITE_SCHEMA_INF  *Inf;

    int    NumSchemaLoad;
};

#pragma pack(pop)
#endif