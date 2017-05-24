#include <stdafx.h>
#include "schema.h"

EXPORT void SCHEMA::ReadUnite(int NumPP)
{
         SCHEMA *pSCHM;

         if ( NumPP == 0 || NumPP > UniteSchem.Quantity ) return;
         if ( UniteSchem.NumSchemaLoad == NumPP ) return;

         UniteSchem.NumSchemaLoad = NumPP;
         pSCHM = (SCHEMA*)(UniteSchem.Inf[NumPP-1].Schem);
         pFormat = pSCHM->pFormat;
         Coord   = pSCHM->Coord;
         QuantityElem = pSCHM->QuantityElem;
         QuantityNode = pSCHM->QuantityNode;

//         DeleteHelp();
         ChangePosFile(*(SCHEMA*)(UniteSchem.Inf[0].Schem));

	      pSCHM->JointInFormat();
	      pSCHM->RigidInFormat();
	      pSCHM->InsertInFormat(_Insert);
	      pSCHM->InsertInFormat(_Corner);
	      pSCHM->InsertInFormat(_CornerNapr);

}

EXPORT void SCHEMA::DeleteUnite(int NumPP)
{
         int i, n;
         SCHEMA *pSCHM;
         LOAD_INF *LI, *LJ;
         UNITE_SCHEMA_INF *USI;

         if ( NumPP == 0 || NumPP > UniteSchem.Quantity ) return;
         if ( UniteSchem.Quantity == 1 ) {   Delete();  return;   }

         if ( UniteSchem.NumSchemaLoad == NumPP ) {
            if ( NumPP > 1 ) ReadUnite(NumPP-1);
            else {  ReadUnite(NumPP+1);  UniteSchem.NumSchemaLoad--;  }
            }

         USI = &UniteSchem.Inf[NumPP-1];
         pSCHM = (SCHEMA*)USI->Schem;
         n = pSCHM->_LoadList.Quantity;

         LI  = LJ = _LoadList.Inf;
         for ( i=0; i<_LoadList.Quantity; i++, LJ++ ) {
            if ( LJ->NumUnite == NumPP ) {
                 LJ->Load.Delete();
                 ZeroMemory(LJ,sizeof(LOAD_INF));
                 continue;   }
            if ( LJ->NumUnite > NumPP ) LJ->NumUnite--;
            if ( LJ > LI ) {
               memcpy(LI,LJ,sizeof(LOAD_INF));
               ZeroMemory(LJ,sizeof(LOAD_INF)); }
	         LI++; }
         _LoadList.Quantity -= n;

         if ( pSCHM ) pSCHM->Delete();

         for ( i=NumPP; i<UniteSchem.Quantity; i++ ) {
            USI = &UniteSchem.Inf[i-1];
            USI->Schem = UniteSchem.Inf[i].Schem;
            USI->NumLoadBegin = UniteSchem.Inf[i].NumLoadBegin - n;
            }
         ZeroMemory(&UniteSchem.Inf[--UniteSchem.Quantity],sizeof(UNITE_SCHEMA_INF));

         Modify = 1;
}

EXPORT int SCHEMA::Unite(LPSTR Name)
{
         SCHEMA *pSCHM;
         UNITE_SCHEMA_INF *Inf;
         LOAD_INF *LI, *pLI;
         int i, n, k, m;

         if ( UniteSchem.Quantity == 0 && ( QuantityElem || QuantityNode ) ) return 1;

         if ( access(Name,0) ) return 2;

         if ( strcmpup(ConstructionDataName("spr"),Name) == 0 ) return 4;

         for ( n=0; n<UniteSchem.Quantity; n++ )
            if ( strcmp(Name,((SCHEMA*)UniteSchem.Inf[n].Schem)->FileName) == 0 )
               return 3;

         if ( UniteSchem.Quantity == UniteSchem.QuantityAlloc ) {
            UniteSchem.QuantityAlloc += 10;
            Inf = (UNITE_SCHEMA_INF*)Memory(sizeof(UNITE_SCHEMA_INF),UniteSchem.QuantityAlloc);
            SpaceCopy(Inf,UniteSchem.Inf,sizeof(UNITE_SCHEMA_INF)*UniteSchem.Quantity);
            MemoryFree(UniteSchem.Inf);
            UniteSchem.Inf = Inf;
            }

         Inf = UniteSchem.Inf + UniteSchem.Quantity;
         Inf->Schem = Memory(sizeof(SCHEMA)+1);
         Inf->NumLoadBegin = _LoadList.Quantity + 1;
         pSCHM = (SCHEMA*)Inf->Schem;
         pSCHM->Init(hWND,hINST,WorkCatalog);
         pSCHM->Read(Name);

         if ( UniteSchem.Quantity ) for ( m=0; m<UniteSchem.Quantity; m++ ) {
            n = ((SCHEMA*)UniteSchem.Inf[m].Schem)->CompareSchem(*pSCHM,0);
            if ( n ) {
               pSCHM->Delete();
               MemoryFree(pSCHM);
               UniteSchem.Inf[UniteSchem.Quantity].Schem = NULL;
               return n;   }  }
         else memcpy(&TypeSystem,&pSCHM->TypeSystem,sizeof(TYPE_SYSTEM));

         k = pSCHM->_LoadList.Quantity;
         AddLoadInf(_LoadList,k);
         LI  = _LoadList.Inf + _LoadList.Quantity;
         pLI = &pSCHM->_LoadList.Inf[0];
         for ( i=0; i<k; i++ ) {
            LI->Load.Copy(pLI->Load);
            pLI->Load.Delete();
	         LI->TypeDynamic = pLI->TypeDynamic;
	         LI->YesWeight = pLI->YesWeight;
	         LI->NumUnite = UniteSchem.Quantity + 1;
	         LI->NumLoadUnite = i + 1;
            LI++;  pLI++;  }
         _LoadList.Quantity += k;

         ReadUnite(++UniteSchem.Quantity);

         if ( UniteSchem.MaxNode < pSCHM->QuantityNode || UniteSchem.MaxElem < pSCHM->QuantityElem )
            for ( i=0; i<UniteSchem.Quantity-1; i++ ) {
                pSCHM = (SCHEMA*)UniteSchem.Inf[i].Schem;
                pSCHM->AddZero(UniteSchem.MaxElem-pSCHM->QuantityElem,
                   UniteSchem.MaxNode-pSCHM->QuantityNode);
                }
         if ( pSCHM->QuantityElem < UniteSchem.MaxElem )
           UniteSchem.MaxElem = pSCHM->QuantityElem;
         if ( pSCHM->QuantityNode < UniteSchem.MaxNode )
           UniteSchem.MaxNode = pSCHM->QuantityNode;
         Modify = 1;
         return 0;

}

EXPORT LPSTR   SCHEMA::GetNameUnite(int NumPP)
{
        if ( NumPP == 0 && NumPP > UniteSchem.Quantity ) return NULL;
        return ((SCHEMA*)UniteSchem.Inf[NumPP-1].Schem)->FileName;
}

EXPORT SCHEMA * SCHEMA::GetSchemaUnite(int NumPP)
{
        if ( NumPP == 0 && NumPP > UniteSchem.Quantity ) return NULL;
        return (SCHEMA*)UniteSchem.Inf[NumPP-1].Schem;

}