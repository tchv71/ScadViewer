#include <stdafx.h>
#include <schema.h>

void DATA_LOAD::Delete(FORCE_GROUP &Group)
{
	   if ( Group.ForceList ) {
	      for ( WORD i=0; i<Group.QuantityForceList; i++ )
	         if ( Group.ForceList[i].Force ) MemoryFree(Group.ForceList[i].Force);
		   MemoryFree(Group.ForceList);  }
	   memset(&Group,0,sizeof(FORCE_GROUP));
}

EXPORT void DATA_LOAD::Delete(void)
{
	   Delete(ForceNode);
	   Delete(ForceFE);
	   Delete(ForceLoad);

	   if ( ForceValue ) {
	      for ( WORD i=0; i<QuantityForceValue; i++ )
		      if ( ForceValue[i].Value ) MemoryFree(ForceValue[i].Value);
	      MemoryFree(ForceValue);  }

	   Init();
}

EXPORT WORD DATA_LOAD::GetNumForceNode(WORD Num)
{
	return GetNumForce(ForceNode,Num);
}

EXPORT WORD DATA_LOAD::GetNumForceFE(WORD Num)
{
	return GetNumForce(ForceFE,Num);
}
EXPORT WORD DATA_LOAD::GetNumForceLoad(WORD Num)
{
	return GetNumForce(ForceLoad,Num);
}

WORD DATA_LOAD::GetNumForce(FORCE_GROUP &Group,WORD Num) {
	for ( WORD k=0; k<Group.QuantityForceList; k++ ) {
	   if ( Num != Group.ForceList[k].NumNodeFe ) continue;
	   return k + 1;  }
	return 0;  }

EXPORT void DATA_LOAD::DeleteForceNode(WORD Quantity, WORD *List, BYTE qw, BYTE qn)
{
	DeleteForce(ForceNode,Quantity,List,qw,qn);
}

EXPORT void DATA_LOAD::DeleteForceFE(WORD Quantity, WORD *List, BYTE qw, BYTE qn )
{
	DeleteForce(ForceFE,Quantity,List,qw,qn);
}
EXPORT void DATA_LOAD::DeleteForceLoad(WORD Quantity, WORD *List)
{
	DeleteForce(ForceLoad,Quantity,List);
}

void DATA_LOAD::DeleteForce(FORCE_GROUP &Group,WORD Quantity, WORD *List, BYTE qw, BYTE qn )
{
	   int i, j, n, k, m, l, iqw;
           FORCE_LIST *FrcL;
	   FORCE_TYPE *FrcT;

      m = Quantity;
      if ( List == NULL ) m = Group.QuantityForceList;

	   for ( i=0; i<m; i++ ) {
	       if ( List ) {
                 n = GetNumForce(Group,List[i]);
	         if ( n-- == 0 ) continue;  }
               else n = i;
	       FrcL = &Group.ForceList[n];
               if ( qw == 0xFF && qn == 0xFF ) FrcL->QuantityForce = 0;
               else {
                  for ( j=0,k=0; j<FrcL->QuantityForce; j++ ) {
	             FrcT = &FrcL->Force[j];
                     iqw = qw;  l = FrcT->Qw;
                     if ( qw == 8 ) {
                        iqw = iqw % 10;  l = l % 10;
                        }
                     if ( ( qw == 0xFF || iqw == l ) &&
                          ( qn == 0xFF || qn == FrcT->Qn ) ) continue;
                     if ( k++ < j )
	                SpaceCopy(&FrcL->Force[k-1],FrcT,sizeof(FORCE_TYPE));
                     }
                  FrcL->QuantityForce = k;
                  }
               if ( FrcL->QuantityForce == 0 && FrcL->Force ) {
		  MemoryFree(FrcL->Force);  FrcL->Force = NULL;	  }
	       }
	   Modify = 1;
}

EXPORT void DATA_LOAD::DeleteForceNode(WORD Num, WORD NumString )
{
	   DeleteForce(ForceNode,Num,NumString);
}

EXPORT void DATA_LOAD::DeleteForceFE(WORD Num, WORD NumString )
{
	   DeleteForce(ForceFE,Num,NumString);
}
EXPORT void DATA_LOAD::DeleteForceLoad(WORD Num, WORD NumString)
{
	   DeleteForce(ForceLoad,Num,NumString);
}

EXPORT void DATA_LOAD::DeleteForceValue( FORCE_GROUP &Group, WORD Quantity, WORD *List, int Num )
{
	   int i, j, n, k, m;
           FORCE_LIST *FrcL;
	   FORCE_TYPE *FrcT;

           m = Quantity;
           if ( List == NULL ) m = Group.QuantityForceList;

	   for ( i=0; i<m; i++ ) {
	       if ( List ) {
                 n = GetNumForce(Group,List[i]);
	         if ( n-- == 0 ) continue;  }
               else n = i;
	       FrcL = &Group.ForceList[n];
               for ( j=0,k=0; j<FrcL->QuantityForce; j++ ) {
	          FrcT = &FrcL->Force[j];
                  if ( FrcT->NumForceValue != Num ) if ( k++ < j ) {
	             SpaceCopy(&FrcL->Force[k-1],FrcT,sizeof(FORCE_TYPE));
                     memset(FrcT,0,sizeof(FORCE_TYPE));
                     }  }
               if ( k != FrcL->QuantityForce ) {
                  FrcL->QuantityForce = k;
                  Modify = 1;  }
               if ( FrcL->QuantityForce == 0 && FrcL->Force ) {
		  MemoryFree(FrcL->Force);  FrcL->Force = NULL;	  }
	       }

}

EXPORT void DATA_LOAD::DeleteForceNodeValue( WORD Quantity, WORD *List, int Num )
{
           DeleteForceValue(ForceNode,Quantity,List,Num);
}

EXPORT void DATA_LOAD::DeleteForceFEValue( WORD Quantity, WORD *List, int Num )
{
           DeleteForceValue(ForceFE,Quantity,List,Num);
}

EXPORT void DATA_LOAD::DeleteForceNodeValue( int Num )
{
           DeleteForceValue(ForceNode,0,NULL,Num);
}

EXPORT void DATA_LOAD::DeleteForceFEValue( int Num )
{
           DeleteForceValue(ForceFE,0,NULL,Num);
}

void DATA_LOAD::DeleteForce(FORCE_GROUP &Group, WORD Num, WORD NumString )
{
	   WORD k, n;
	   FORCE_TYPE  *FrcT;
      FORCE_LIST *FrcL;

	   n = GetNumForce(Group,Num);
	   if ( n-- == 0 || NumString-- == 0 ) return;

	   FrcL = &Group.ForceList[n];
	   k = FrcL->QuantityForce;
	   if ( NumString >= k ) return;
	   FrcL->QuantityForce--;
	   if ( --k == 0 ) {
	      MemoryFree(FrcL->Force);
	      FrcL->Force = NULL;
	      return;  }
	   FrcT = (FORCE_TYPE*) Memory(k,sizeof(FORCE_TYPE));
	   SpaceCopy(FrcT,FrcL->Force,(DWORD)NumString*sizeof(FORCE_TYPE));
	   SpaceCopy(&FrcT[NumString],&Group.ForceList[n].Force[NumString+1],
			 (DWORD)(k-NumString)*sizeof(FORCE_TYPE));
	   MemoryFree(FrcL->Force);
	   FrcL->Force = FrcT;
	   Modify = 1;
}

EXPORT void DATA_LOAD::Include(WORD Num, BYTE Qw, BYTE Qn, WORD QntForceValue,float *ForceV) {
	   Include(Num,Qw,Qn,AddForceValue(QntForceValue,ForceV));
}

EXPORT void DATA_LOAD:: Include(WORD Quantity, WORD *List,BYTE Qw, BYTE Qn, WORD QntForceValue,float *ForceV) {
	   WORD i;
	   WORD n = AddForceValue(QntForceValue,ForceV);
	   for ( i=0; i<Quantity; i++ ) Include(List[i],Qw,Qn,n);
}

EXPORT void DATA_LOAD::Include(WORD Num, BYTE Qw, BYTE Qn, WORD NumForceValue)
{
	   FORCE_GROUP *Group;
	   WORD k, m;
	   FORCE_TYPE  *FrcT;
           FORCE_LIST  *FrcL;

	   if ( Qw > 3 ) Group = &ForceFE;
	   else Group = &ForceNode;
	   if ( Qw == 4 && Qn == 3 ) Group = &ForceLoad;

	   k = GetNumForce(*Group,Num);
	   if ( k-- == 0 ) k = AddForceList(*Group,500) - 1;
	   FrcL = &Group->ForceList[k];
	   FrcL->NumNodeFe = Num;
	   m = FrcL->QuantityForce++;
	   FrcT = (FORCE_TYPE*) Memory(m+1,sizeof(FORCE_TYPE));
	   if ( FrcL->Force ) {
	      SpaceCopy(FrcT,FrcL->Force,(DWORD)m*sizeof(FORCE_TYPE));
	      MemoryFree(FrcL->Force);  }
	   FrcL->Force = FrcT;
	   FrcT = FrcT + m;
	   FrcT->Qw = Qw;
	   FrcT->Qn = Qn;
	   FrcT->NumForceValue = NumForceValue;
	   Modify = 1;

}

WORD    DATA_LOAD::AddForceList(FORCE_GROUP &Group, WORD Qntt)
{
          FORCE_LIST *FrcL;
	  if ( Group.QuantityForceList++ == Group.QuantityAllocForceList ) {
	     Group.QuantityAllocForceList += Qntt;
	     FrcL = (FORCE_LIST *)Memory(Group.QuantityAllocForceList,sizeof(FORCE_LIST));
	     if ( Group.ForceList ) {
		SpaceCopy(FrcL,Group.ForceList,(DWORD)(Group.QuantityForceList-1)*sizeof(FORCE_LIST));
		MemoryFree(Group.ForceList);  }
	     Group.ForceList = FrcL;
	     }
          Modify = 1;
	  return Group.QuantityForceList;
}

DWORD    DATA_LOAD::AddForceValue()
{
          FORCE_VALUE *FrcV;
	  if ( QuantityForceValue++ == QuantityAllocForceValue ) {
	     QuantityAllocForceValue += 100;
	     FrcV = (FORCE_VALUE *)Memory(QuantityAllocForceValue,sizeof(FORCE_VALUE));
	     if ( ForceValue ) {
		SpaceCopy(FrcV,ForceValue,(DWORD)(QuantityForceValue-1)*sizeof(FORCE_VALUE));
		MemoryFree(ForceValue);  }
	     ForceValue = FrcV;
	     }
	  return QuantityForceValue;
}

EXPORT WORD DATA_LOAD::AddForceValue(WORD QntForceValue,float *ForceV)
{
	return AddForceValue(1,QntForceValue,ForceV);
}

WORD    DATA_LOAD::AddForceValue(BYTE Type, WORD QntForceValue,float *ForceV )
{
	 WORD k = QuantityForceValue;
	 WORD  i, n;
	 float *f, *q;
         FORCE_VALUE  *FrcV;

	 if ( Type ) for ( k=0; k<QuantityForceValue; k++ ) {
	    n = ForceValue[k].QuantityValue;
	    if ( n != QntForceValue ) continue;
	    f = ForceValue[k].Value;
	    q = ForceV;
	    for ( i=0; i<n; i++, f++, q++ )
	       if ( fabs( *f - *q ) > 0.00001 * ( fabs(*f) + fabs(*q) ) )  goto _10;
	    break;
_10:;       }

	 if ( k == QuantityForceValue ) {
	    AddForceValue();
	    FrcV = &ForceValue[k];
	    FrcV->QuantityValue = QntForceValue;
	    if ( QntForceValue ) {
	       FrcV->Value = (float*)Memory(QntForceValue,sizeof(float));
	       memcpy(FrcV->Value,ForceV,QntForceValue*sizeof(float));
	       }  }
	 Modify = 1;
	 return k + 1;
}

EXPORT void DATA_LOAD::ChangeForceValueNode(WORD NumPP, WORD NumString, WORD QntForceValue,float *ForceV )
{
	 ChangeForceValue(ForceNode,NumPP,NumString,QntForceValue,ForceV);
}

EXPORT void DATA_LOAD::ChangeForceValueFE(  WORD NumPP, WORD NumString, WORD QntForceValue,float *ForceV )
{
	 ChangeForceValue(ForceFE,NumPP,NumString,QntForceValue,ForceV);
}
EXPORT void DATA_LOAD::ChangeForceValueLoad(  WORD NumPP, WORD NumString, WORD QntForceValue,float *ForceV )
{
	 ChangeForceValue(ForceLoad,NumPP,NumString,QntForceValue,ForceV);
}

void DATA_LOAD::ChangeForceValue(FORCE_GROUP &Group, WORD NumPP,  WORD NumString,
		       WORD QntForceValue, float *ForceV )
{
	   FORCE_TYPE  *FrcT;
	   WORD n;
           FORCE_LIST  *FrcL;

	   if ( NumPP == 0 || NumPP > Group.QuantityForceList || NumString-- == 0 ) return;
	   else {
		FrcL = &Group.ForceList[NumPP];
		if ( FrcL->QuantityForce <= NumString ) return;
		else FrcT = &FrcL->Force[NumString];
		}

	   n = AddForceValue(QntForceValue,ForceV);
	   if ( n != FrcT->NumForceValue ) Modify = 1;
	   FrcT->NumForceValue = n;
}

EXPORT FORCE_LIST * DATA_LOAD::GetForceNode(WORD NumPP)
{
	   return GetForce(ForceNode,NumPP);
}

EXPORT FORCE_LIST * DATA_LOAD::GetForceFE(WORD NumPP)
{
	   return GetForce(ForceFE,NumPP);
}
EXPORT FORCE_LIST * DATA_LOAD::GetForceLoad(WORD NumPP)
{
	   return GetForce(ForceLoad,NumPP);
}

FORCE_LIST * DATA_LOAD::GetForce(FORCE_GROUP &Group, WORD NumPP)
{
	   if ( NumPP == 0 || NumPP > Group.QuantityForceList ) return NULL;
	   return &Group.ForceList[NumPP-1];
}

EXPORT WORD DATA_LOAD::GetQuantityForceNode(WORD NumPP)
{
	   return GetQuantityForce(ForceNode,NumPP);
}

EXPORT WORD DATA_LOAD::GetQuantityForceFE(WORD NumPP)
{
	   return GetQuantityForce(ForceFE,NumPP);
}
EXPORT WORD DATA_LOAD::GetQuantityForceLoad(WORD NumPP)
{
	   return GetQuantityForce(ForceLoad,NumPP);
}

WORD DATA_LOAD::GetQuantityForce(FORCE_GROUP &Group, WORD NumPP)
{
	   if ( NumPP == 0 || NumPP > Group.QuantityForceList ) return 0;
	   return Group.ForceList[NumPP-1].QuantityForce;
}

EXPORT FORCE_TYPE * DATA_LOAD::GetForceNode(WORD NumPP, WORD NumString )
{
	   return GetForce(ForceNode,NumPP,NumString);
}

EXPORT FORCE_TYPE * DATA_LOAD::GetForceFE(WORD NumPP, WORD NumString )
{
	   return GetForce(ForceFE,NumPP,NumString);
}

EXPORT FORCE_TYPE * DATA_LOAD::GetForceLoad(WORD NumPP, WORD NumString )
{
	   return GetForce(ForceLoad,NumPP,NumString);
}

EXPORT void DATA_LOAD::GetForceNode(WORD NumPP, WORD NumString, WORD &Num,
		 BYTE &Qw, BYTE &Qn, WORD &QnttValue, float **Value)
{
	   GetForce(ForceNode,NumPP,NumString,Num,Qw,Qn,QnttValue,Value);
}

EXPORT void DATA_LOAD::GetForceFE(WORD NumPP, WORD NumString, WORD &Num,
		 BYTE &Qw, BYTE &Qn, WORD &QnttValue, float **Value)
{
	   GetForce(ForceFE,NumPP,NumString,Num,Qw,Qn,QnttValue,Value);
}
EXPORT void DATA_LOAD::GetForceLoad(WORD NumPP, WORD NumString, WORD &Num,
		 BYTE &Qw, BYTE &Qn, WORD &QnttValue, float **Value)
{
	   GetForce(ForceLoad,NumPP,NumString,Num,Qw,Qn,QnttValue,Value);
}

void DATA_LOAD::GetForce(FORCE_GROUP &Group, WORD NumPP, WORD NumString,
		 WORD &Num, BYTE &Qw, BYTE &Qn, WORD &QnttValue, float **Value)
{
	   FORCE_TYPE  *FrcT = GetForce(Group,NumPP,NumString);
           FORCE_LIST  *FrcL;
           FORCE_VALUE *FrcV;
	   Num = 0;
           if ( FrcT == NULL ) return;
	   FrcL = &Group.ForceList[NumPP-1];
	   Num  = FrcL->NumNodeFe;
	   Qw   = FrcT->Qw;
	   Qn   = FrcT->Qn;
	   FrcV = &ForceValue[FrcT->NumForceValue-1];
	   QnttValue = FrcV->QuantityValue;
	   *Value = FrcV->Value;
}

FORCE_TYPE * DATA_LOAD::GetForce(FORCE_GROUP &Group, WORD NumPP, WORD NumString )
{
           FORCE_LIST  *FrcL;
	   if ( NumPP == 0 || NumPP > Group.QuantityForceList ) return NULL;
	   FrcL = &Group.ForceList[NumPP-1];
	   if ( NumString == 0 || FrcL->QuantityForce < NumString ) return NULL;
	   return &FrcL->Force[NumString-1];
}

void DATA_LOAD::Copy(FORCE_GROUP &FrcGrpInp,FORCE_GROUP &FrcGrpOut)
{
	   Delete(FrcGrpOut);
	   if ( FrcGrpInp.QuantityForceList == 0 ) return;
	   FrcGrpOut.QuantityForceList = FrcGrpOut.QuantityAllocForceList =
	      FrcGrpInp.QuantityForceList;
	   FrcGrpOut.ForceList =
	      (FORCE_LIST*)Memory(FrcGrpInp.QuantityForceList,sizeof(FORCE_LIST));
	   for ( WORD i=0; i<FrcGrpInp.QuantityForceList; i++ ) {
	      memcpy(&FrcGrpOut.ForceList[i],&FrcGrpInp.ForceList[i],2*sizeof(WORD));
	      FrcGrpOut.ForceList[i].Force =
		 (FORCE_TYPE*)Memory(FrcGrpInp.ForceList[i].QuantityForce,sizeof(FORCE_TYPE));
	      SpaceCopy(FrcGrpOut.ForceList[i].Force,FrcGrpInp.ForceList[i].Force,
		   FrcGrpInp.ForceList[i].QuantityForce*(DWORD)sizeof(FORCE_TYPE));
	      }
}

EXPORT void DATA_LOAD::Copy(DATA_LOAD &DtLd)
{
/*   copy in   */
	   WORD i;
      FORCE_VALUE *Inp, *Out;

	   Delete();
	   strcpy(Name,DtLd.Name);

	   Copy(DtLd.ForceNode,ForceNode);
	   Copy(DtLd.ForceFE,ForceFE);
	   Copy(DtLd.ForceLoad,ForceLoad);

	   if (  DtLd.QuantityForceValue == 0 ) return;
	   QuantityForceValue = QuantityAllocForceValue = DtLd.QuantityForceValue;
	   ForceValue =
	      (FORCE_VALUE*)Memory(DtLd.QuantityForceValue,sizeof(FORCE_VALUE));
	   for ( i=0; i<DtLd.QuantityForceValue; i++ ) {
	      Inp = &DtLd.ForceValue[i];  Out = &ForceValue[i];
	      Out->QuantityValue = Inp->QuantityValue;
	      Out->Value = (float*)Memory(Inp->QuantityValue,sizeof(float));
	      memcpy(Out->Value,Inp->Value,Inp->QuantityValue*sizeof(float));
	      }
}

EXPORT void DATA_LOAD::Add(DATA_LOAD &DtLd, BYTE MaskQw)
{
           WORD *NumValue, i;
           FORCE_VALUE  *FrcVl;
	   if ( DtLd.QuantityForceValue == 0 ) return;
	   NumValue = (WORD*)Memory(DtLd.QuantityForceValue+1,sizeof(WORD));
	   for ( i=0; i<DtLd.QuantityForceValue; i++ ) {
	       FrcVl = &DtLd.ForceValue[i];
	       NumValue[i] = AddForceValue(1,FrcVl->QuantityValue,FrcVl->Value);
	       }
	   if ( MaskQw < 4 || MaskQw == 0xFF ) Add(NumValue,DtLd.ForceNode,MaskQw);
	   if ( MaskQw > 3 || MaskQw == 0xFF ) Add(NumValue,DtLd.ForceFE,MaskQw);
	   MemoryFree(NumValue);
           Modify = 1;
}

void DATA_LOAD::Add(WORD *NumValue,FORCE_GROUP &FrcGrpInp,BYTE MaskQw )
{
	   WORD i, j;
           FORCE_LIST  *FrcLst;
	   FORCE_TYPE  *FrcTp;

	   for ( i=0; i<FrcGrpInp.QuantityForceList; i++ ) {
	       FrcLst = &FrcGrpInp.ForceList[i];
               if ( FrcLst->NumNodeFe == 0 ) continue;
	       for ( j=0; j<FrcLst->QuantityForce; j++ ) {
		  FrcTp = &FrcLst->Force[j];
		  if ( MaskQw == 0xFF || FrcTp->Qw == MaskQw )
		     Include(FrcLst->NumNodeFe,FrcTp->Qw,FrcTp->Qn,NumValue[FrcTp->NumForceValue-1]);
		  }   }
           Modify = 1;
}

void DATA_LOAD::Compress(WORD QntFE, WORD QntNode, WORD QnttLoad)
{
	   BYTE *YesForceLd;
	   WORD *NumForceLd, i, l=0;
	   FORCE_VALUE *pFV;

	   YesForceLd = (BYTE*)Memory(QuantityForceValue+1);
	   NumForceLd = (WORD*)Memory(QuantityForceValue+1,sizeof(WORD));
	   YesForceValue(ForceNode,QntNode,YesForceLd);
	   YesForceValue(ForceFE,QntFE,YesForceLd);
	   YesForceValue(ForceLoad,QnttLoad,YesForceLd);

	   for ( i=1; i<=QuantityForceValue; i++ ) {
	      pFV = (FORCE_VALUE*)&ForceValue[i-1];
	      if ( YesForceLd[i] ) {
		      if ( l < i - 1 ) {
		         memcpy(&ForceValue[l],pFV,sizeof(FORCE_VALUE));
		         memset(pFV,0,sizeof(FORCE_VALUE));  }
	         NumForceLd[i] = ++l;  }
	      else if ( pFV->Value ) {
	         MemoryFree(pFV->Value);
	         memset(pFV,0,sizeof(FORCE_VALUE));  }
	      }
	   QuantityForceValue = l;

	   Compress(ForceNode,QntNode,NumForceLd);
	   Compress(ForceFE,QntFE,NumForceLd);
	   Compress(ForceLoad,QnttLoad,NumForceLd);

	   MemoryFree(YesForceLd);
	   MemoryFree(NumForceLd);
}

void DATA_LOAD::Compress( WORD QuantytiElemOld, WORD QntFE,   WORD * NumElem,
        WORD QuantytiNodeOld, WORD QntNode, WORD * NumNode, WORD QnttLoad )
{
	   Compress(ForceFE,QuantytiElemOld,QntFE,NumElem);
	   Compress(ForceNode,QuantytiNodeOld,QntNode,NumNode);
	   Compress(QntFE,QntNode,QnttLoad);
}

void DATA_LOAD::Compress( FORCE_GROUP &Group, WORD QuantityOld, WORD Qnt,  WORD * Num )
{
	   int i, n;
      FORCE_LIST *FrcL;

	   if ( Num == NULL ) return;
      FrcL = Group.ForceList;
	   for ( i=0; i<Group.QuantityForceList; i++, FrcL++ ) {
	      n = FrcL->NumNodeFe;
	      if (  n > QuantityOld ) {  FrcL->NumNodeFe = 0;  continue;   }
	      FrcL->NumNodeFe = Num[n];   }
      Compress(Group,Qnt,NULL);

}

void DATA_LOAD::Compress(FORCE_GROUP &Group, WORD Qnt, WORD *NumForceLd)
{
	   int k, n, l;
      FORCE_LIST *FrcL;

	   for ( k=0,l=0; k<Group.QuantityForceList; k++ ) {
	      FrcL = &Group.ForceList[k];
	      if ( FrcL->NumNodeFe == 0 || FrcL->NumNodeFe > Qnt ) {
		      if ( FrcL->Force ) {
		         MemoryFree(FrcL->Force);
		         memset(FrcL,0,sizeof(FORCE_LIST));  }
            continue;  }
	      if ( FrcL->QuantityForce == 0 ) continue;
         if ( NumForceLd ) for ( n=0; n<FrcL->QuantityForce; n++ )
	         FrcL->Force[n].NumForceValue = NumForceLd[FrcL->Force[n].NumForceValue];
         if ( l < k ) {
            memcpy(&Group.ForceList[l],FrcL,sizeof(FORCE_LIST));
            memset(FrcL,0,sizeof(FORCE_LIST));   }
         l++;  }
	   Group.QuantityForceList = l;
}

void DATA_LOAD::YesForceValue(FORCE_GROUP &Group, WORD Qnt, BYTE *YesForceLd)
{
	   WORD k, n;
      FORCE_LIST *FrcL;
	   for ( k=0; k<Group.QuantityForceList; k++ ) {
	      FrcL = &Group.ForceList[k];
	      if ( FrcL->NumNodeFe > Qnt ) continue;
	      for ( n=0; n<FrcL->QuantityForce; n++ )
		      YesForceLd[FrcL->Force[n].NumForceValue] = 1;
	      }
}


EXPORT void DATA_LOAD::ClearForceNode(WORD NumNode)
{
     ClearForce(NumNode,ForceNode);
}

EXPORT void DATA_LOAD::ClearForceFE(WORD NumFE)
{
     ClearForce(NumFE,ForceFE);
}

EXPORT void DATA_LOAD::ClearForceLoad(WORD NumLoad)
{
     ClearForce(NumLoad,ForceLoad);
}

void DATA_LOAD::ClearForce(WORD Num,FORCE_GROUP &FrcGrp)
{
     WORD i, n = GetNumForce(FrcGrp,Num);
     if ( n-- == 0 ) return;
	  if ( FrcGrp.ForceList[n].Force ) MemoryFree(FrcGrp.ForceList[n].Force);
     for ( i=n; i<FrcGrp.QuantityForceList-1; i++ )
        memcpy(&FrcGrp.ForceList[i],&FrcGrp.ForceList[i+1],sizeof(FORCE_LIST));
     memset(&FrcGrp.ForceList[--FrcGrp.QuantityForceList],0,sizeof(FORCE_LIST));
     Modify = 1;
}

void DATA_LOAD::ClearForce( WORD Num, WORD NumString, FORCE_GROUP &FrcGrp)
{
	  WORD i;
	  FORCE_LIST *FrcLst = GetForce(FrcGrp,GetNumForce(FrcGrp,Num));
	  if ( FrcLst == NULL ) return;
	  if ( FrcLst->QuantityForce == 0 || NumString == 0 || NumString > FrcLst->QuantityForce )
	     return;
	  if ( FrcLst->QuantityForce == 1 ) {
	     ClearForce(Num,FrcGrp);
	     return;  }
	  for ( i=NumString; i<FrcLst->QuantityForce; i++ )
	     SpaceCopy(&FrcLst->Force[i-1],&FrcLst->Force[i],sizeof(FORCE_TYPE));
	  FrcLst->QuantityForce--;
          Modify = 1;
}

EXPORT void  DATA_LOAD::ClearForceNode(WORD NumNode, WORD NumString )
{
	    ClearForce(NumNode,NumString,ForceNode);
}

EXPORT void  DATA_LOAD::ClearForceFE(WORD NumFE, WORD NumString )
{
	    ClearForce(NumFE,NumString,ForceFE);
}

EXPORT void  DATA_LOAD::ClearForceLoad(WORD NumLoad, WORD NumString )
{
	    ClearForce(NumLoad,NumString,ForceLoad);
}