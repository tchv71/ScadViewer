#include <stdafx.h>
#include "schema.h"

EXPORT void SCHEMA::Delete(void)
{
	 WORD i;
    SCHEMA *pSCHM;

	 if ( this == NULL ) return;

    if ( UniteSchem.Quantity ) {
       if ( UniteSchem.Inf ) {
          for ( i=0; i<UniteSchem.Quantity; i++ ) {
             pSCHM = (SCHEMA*)UniteSchem.Inf[i].Schem;
             if ( pSCHM ) {  pSCHM->Delete();  MemoryFree(pSCHM);  }
             }
          MemoryFree(UniteSchem.Inf);
          }
       pFormat = NULL;  Coord = NULL;
       }

	 if ( pFormat != NULL ) {
	    for ( i=0; i<QuantityElem; i++ )
	       if ( pFormat[i].pNode != NULL ) MemoryFree(pFormat[i].pNode);
	    MemoryFree(pFormat);  pFormat = NULL;   }
	 if ( Coord ) {  MemoryFree(Coord);  Coord = NULL;  }

    DeleteHelp();

	 if ( Data )  {  MemoryFree(Data);   Data = NULL;  }

	 _Load.Delete();
	 ClearLoad(_LoadList);
	 ClearLoad(_LoadGroup);

	 _Bound.Delete();
	 _Joint.Delete();
	 _Rigid.Delete();
    _SectionName.Delete();
    _RigidName.Delete();
	 _Insert.Delete();
	 _Corner.Delete();
	 _CornerNapr.Delete();
	 _Contur.Delete();
	 _Steel.Delete();
	 _SteelUni.Delete();
     _Blocks.Delete();
     _ConstructionPos.Delete();


	 for ( i=0; i<10; i++ )	_List[i].Delete();

	 _ProfileIn.Delete();

	 FilePrj.Close();
	 Print.Close();
	 if ( FileNameWork[0] && strcmp(FileNameWork,FileName) )
		 if ( access(FileNameWork,0) == 0 ) remove(FileNameWork);

	 DeleteLookBody();

	 memset(this,0,sizeof(SCHEMA));
}

void SCHEMA::DeleteHelp(void)
{
	       if ( GrafCoord != NULL ) {
	          MemoryFree(GrafCoord);  GrafCoord = NULL;  }
	       if ( DCoord ) {  MemoryFree(DCoord);  DCoord = NULL;  }
	          if ( DGrafCoord != NULL ) {
	          MemoryFree(DGrafCoord);  DGrafCoord = NULL;  }
	       if ( MaskNode.Mask ) {
	          MemoryFree(MaskNode.Mask);  MaskNode.Mask = NULL;  }
	       if ( MaskFE.Mask ) {
	          MemoryFree(MaskFE.Mask);  MaskFE.Mask = NULL;  }
}


EXPORT void SCHEMA::DeleteLookBody()
{
	 if ( this == NULL ) return;
	 BYTE Fragm = Video.FragmParam;
	 if ( Video.ElemBody  ) MemoryFree(Video.ElemBody);
	 if ( Video.Order     ) MemoryFree(Video.Order);
	 if ( Video.MaskElem  ) MemoryFree(Video.MaskElem );
	 if ( Video.MaskFragm ) MemoryFree(Video.MaskFragm);
	 if ( Video.Coord     ) MemoryFree(Video.Coord    );
	 if ( Video.GrafCoord ) MemoryFree(Video.GrafCoord );

	 memset(&Video,0,sizeof(Video));
         Video.FragmParam = Fragm;
}