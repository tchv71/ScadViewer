#include <stdafx.h>
#include "schema.h"
#include "scadnode.hpp"
#include <vector>
#include <algorithm>

void  EXPORT DeleteNode(SCHEMA &Schem, float PrecesionCoincidence, BYTE Type=0 )
{
      Schem.DeleteNode(PrecesionCoincidence,Type);
}


void  EXPORT SCHEMA::DeleteNode( float PrecesionCoincidence, BYTE Type )
{
// Type != 0 - Удаление по фрагменту

	     CK *pCKI;
        int *NumNodeA, k, im;
        WORD *NumNode, n=0, i, j, n1, n2;
        FORMAT *pF;
        DATA_LOAD DL;
        SCAD_NODE Node;

	     std::vector<SCAD_NODE> VectNode(QuantityNode);
		  VectNode.erase(VectNode.begin(),VectNode.end());
        NumNodeA = (int*)Memory(QuantityNode+1,sizeof(int));

        for ( i=1; i<=QuantityNode; i++ ) {
           pCKI = &Coord[i-1];
           if ( Type ) if ( GetNodeBitFlag(i,5) == 0 ) continue;
           Node.Set(*pCKI,PrecesionCoincidence,i);
           VectNode.push_back(Node);
           n++;  }
        if ( n ) std::sort(VectNode.begin(),VectNode.end());
        else return;

        for ( i=0; i<n-2; i++ ) if ( VectNode[i] == VectNode[i+1] ) {
           n1 = VectNode[i].nNode;
           n2 = GetNodeBitFlag(n1,7);
           for ( j=i; j<n-2; j++ ) {
              if ( VectNode[j] == VectNode[j+1] ) {
                 k =  VectNode[j+1].nNode;
                 if ( k < n1 ) n1 = k;
                 k = GetNodeBitFlag(k,7);
                 if ( k != n2 ) n2 = 0;   }
              else break;  }
           for ( k=i; k<=j; k++ ) {
              im = VectNode[k].nNode;
              if ( im != n1 ) NumNodeA[im] = -n1;
              else if ( n2 == 0 ) ClearNodeFlag(n1,7);
              }
           i = j - 1;  }

        for ( i=1,n=0; i<=QuantityNode; i++ ) {
           if ( NumNodeA[i] == 0 ) NumNodeA[i] = ++n;
           if ( n <= i ) memcpy(&Coord[n],&Coord[i],sizeof(CK));
           }

        for ( i=1; i<=QuantityNode; i++ )
           if ( NumNodeA[i] < 0 ) NumNodeA[i] = NumNodeA[-NumNodeA[i]];

        NumNode = (WORD*)NumNodeA;
        for ( i=1; i<=QuantityNode; i++ ) NumNode[i] = NumNodeA[i];

	     if ( n < QuantityNode ) {

	        for ( i=0; i<QuantityElem; i++ ) {
	           pF = &pFormat[i];
	           if ( pF->pNode == NULL ) continue;
	           for ( j=0; j<pF->QuantityNode; j++ ) {
                 if ( pF->pNode[j] == 0 ) continue;
                 pF->pNode[j] = NumNode[pF->pNode[j]];
                 }  }

           for ( i=n+1; i<QuantityNode; i++ )
	           memset(&Coord[i],0,sizeof(CK));

          _Bound.Write(FilePrj,QuantityNode,n,NumNode);
          _List[4].Write(FilePrj,QuantityNode,n,NumNode);
          _List[7].Write(FilePrj,QuantityNode,n,NumNode);
          _List[8].Write(FilePrj,QuantityNode,n,NumNode);

          _Load.Compress(0,0,NULL,QuantityNode,n,NumNode,_LoadList.Quantity);
           DL.Copy(_Load);
           WriteLoad(FilePrj,_LoadList,6,0,NULL,QuantityNode,NumNode);
           WriteLoad(FilePrj,_LoadGroup,7,0,NULL,QuantityNode,NumNode);
           ReadLoadInf(_LoadList);
           ReadLoadInf(_LoadGroup);
          _Load.Copy(DL);
           DL.Delete();
           Modify = 1;
           QuantityNode = n;  }

        MemoryFree(NumNodeA);
}



