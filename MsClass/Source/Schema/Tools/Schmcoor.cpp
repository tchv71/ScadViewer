#include <stdafx.h>
#include "schema.h"

EXPORT void SCHEMA::SetCoordX(WORD NumNode,double x) {
     if ( --NumNode < QuantityNode ) Coord[NumNode].x = x;
     if ( Video.QuantityElemBody ) DeleteLookBody();
     Modify = 1;
     }
EXPORT void SCHEMA::SetCoordY(WORD NumNode,double y) {
     if ( --NumNode < QuantityNode ) Coord[NumNode].y = y;
     if ( Video.QuantityElemBody ) DeleteLookBody();
     Modify = 1;
     }
EXPORT void SCHEMA::SetCoordZ(WORD NumNode,double z) {
     if ( --NumNode < QuantityNode ) Coord[NumNode].z = z;
     if ( Video.QuantityElemBody ) DeleteLookBody();
     Modify = 1;
     };

EXPORT CK * SCHEMA::GetCoord(int NumNode)
{
	 if ( NumNode ) {
	    if ( NumNode <= QuantityNode ) return &Coord[NumNode-1];
	    else if ( NumNode <= QuantityNode + Video.QuantityNodeBody )
	       return &Video.Coord[NumNode-QuantityNode-1];
	   }
	 return NULL;
}

EXPORT double SCHEMA::GetCoordX(int NumNode) {
	 CK *pCK = (CK*)GetCoord(NumNode);
	 if ( pCK ) return pCK->x;
	 return 0;
}

EXPORT double SCHEMA::GetCoordY(int NumNode) {
	 CK *pCK = (CK*)GetCoord(NumNode);
	 if ( pCK ) return pCK->y;
	 return 0;
}

EXPORT double SCHEMA::GetCoordZ(int NumNode) {
	 CK *pCK = (CK*)GetCoord(NumNode);
	 if ( pCK ) return pCK->z;
	 return 0;
}

EXPORT GrafCK * SCHEMA::GetGrafCoord(int NumNode)
{
	 if ( NumNode ) {
	    if ( NumNode <= QuantityNode ) return &GrafCoord[NumNode-1];
	    else if ( NumNode <= QuantityNode + Video.QuantityNodeBody )
	       return &Video.GrafCoord[NumNode-QuantityNode-1];
	   }
	 return NULL;
}

EXPORT int SCHEMA::GetGrafCoordX(int NumNode) {
	 GrafCK *pCK = (GrafCK*)GetGrafCoord(NumNode);
	 if ( pCK ) return pCK->x;
	 return 0;
}

EXPORT int SCHEMA::GetGrafCoordY(int NumNode) {
	 GrafCK *pCK = (GrafCK*)GetGrafCoord(NumNode);
	 if ( pCK ) return pCK->y;
	 return 0;
}

EXPORT void  SCHEMA::SetGrafCoordX(int NumNode,int x) {
	 GrafCK *pCK = (GrafCK*)GetGrafCoord(NumNode);
	 if ( pCK ) pCK->x = x;
}

EXPORT void SCHEMA::SetGrafCoordY(int NumNode,int y) {
	 GrafCK *pCK = (GrafCK*)GetGrafCoord(NumNode);
	 if ( pCK ) pCK->y = y;
}