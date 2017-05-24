#include <stdafx.h>
#include <schema.h>
#include "ScadNode.hpp"
#include <vector>
#include <algorithm>

EXPORT int  SCHEMA::AddSchema( ADD_SCHEMA_DATA &AddData, SCHEMA &AddSchm )
{
       WORD  i, j, k, m, n, Node[2], Qntt, im, l, n2;
       WORD  QuantityNodeOld;
       int n1, iRet=0;
       double mk[3][3], BegCK1[3], BegCK2[3];
       WORD         * NumNode;
	   int          * NumNodeA;
       WORD         * NumElem;
       WORD         * NumNodeElem;
       BYTE         * NumTypeRigid;
       WORD         * Lst, *LstNew, *NumSechName, *NumRgdName;
       FORMAT *pF1, *pF2;
       TYPE_DATA_SF *pSF;
       BYTE Type;
       CK pCK, qCK;
       FORCE_LIST *pFL;
       char s[MAX_LENGTH_NAME_LOAD+1], *pS;
       int YesForceEqNode;
       DATA_IN *DI;
       STEEL_LIST *SL;
       SCAD_NODE Nd;

       n = AddControl(AddData,AddSchm,BegCK1,BegCK2,mk);
       if ( n ) return n;

       YesForceEqNode = GetPrivateProfileInt("SCHEMA","ForceEqNode",0,GetPath("scad.ini"));

       QuantityNodeOld = QuantityNode;

       AddSchm._Rigid.Read();

       std::vector<SCAD_NODE> VectNode(QuantityNodeOld+AddSchm.QuantityNode);
	    VectNode.erase(VectNode.begin(),VectNode.end());

       NumElem   = (WORD*) Memory(AddSchm.QuantityElem+1,sizeof(WORD));
       NumNodeA  = (int*) Memory(QuantityNodeOld+AddSchm.QuantityNode+1,sizeof(int));
       NumNode   = (WORD*) Memory(AddSchm.QuantityNode+1,sizeof(WORD));
       NumTypeRigid = (BYTE*) Memory(AddSchm._Rigid.MaxNumRigid+1);

       if ( AddData.TypeCoincidence == 0 || AddData.MaskContact ) {
          for ( i=1; i<=QuantityNodeOld; i++ ) {
             Nd.Set(Coord[i-1],AddData.PrecesionCoincidence,i);
             VectNode.push_back(Nd);   }   }
       for ( i=0; i<AddSchm.QuantityNode; i++ ) {
	       qCK.x = AddSchm.Coord[i].x - BegCK2[0];
	       qCK.y = AddSchm.Coord[i].y - BegCK2[1];
	       qCK.z = AddSchm.Coord[i].z - BegCK2[2];
	       MultMatr((double*)mk,(double*)&qCK,-3,3,1,(double*)&pCK);
	       pCK.x += BegCK1[0];
	       pCK.y += BegCK1[1];
	       pCK.z += BegCK1[2];
	       pCK.Flag = AddSchm.Coord[i].Flag;
          Nd.Set(pCK,AddData.PrecesionCoincidence,i+QuantityNodeOld+1);
          if ( AddData.TypeCoincidence == 0 || AddData.MaskContact )
             VectNode.push_back(Nd);
          if ( AddData.TypeCoincidence || AddData.MaskContact ) {
//             if ( AddSchm.GetNodeBitFlag(i+1,7) ) continue;
             NumNode[i+1] = AddNode(pCK);
             if ( NumNode[i+1] == 0 ) {
                MemoryFree(NumNodeA);
                iRet = 4;  goto _30;   }
             }
          }

       if ( AddData.TypeCoincidence && AddData.MaskContact == 0 ) goto _10;

       std::sort(VectNode.begin(),VectNode.end());

       for ( i=0; i<QuantityNodeOld+AddSchm.QuantityNode; i++ ) {
          n1 = VectNode[i].nNode;   im = 1;
          for ( j=i; j<QuantityNodeOld+AddSchm.QuantityNode && ( VectNode[i] == VectNode[j] ); j++ ) {
             n2 = VectNode[j].nNode;
             if ( n2 < n1 ) n1 = n2;
             if ( n2 < QuantityNodeOld ) {  if ( GetNodeBitFlag(n2,7) == 0 ) im = 0;  }
             else {
                if ( AddSchm.GetNodeBitFlag(n2-QuantityNodeOld,7) == 0 ) im = 0;
                }  }
          if ( j == i + 1 ) continue;
          if ( im == 0 ) {
             if ( n1 < QuantityNodeOld ) ClearNodeFlag(n1,7);
             else AddSchm.ClearNodeFlag(n1-QuantityNodeOld,7);   }
          for ( l=i; l<j; l++ ) NumNodeA[VectNode[l].nNode] = -n1;
          }

       if ( AddData.MaskContact == 0 )  {
          for ( i=QuantityNodeOld+1; i<=QuantityNodeOld+AddSchm.QuantityNode; i++ )
//             if ( AddSchm.GetNodeBitFlag(i-QuantityNodeOld,7) ) continue;
             if ( NumNodeA[i] == 0 || -NumNodeA[i] > QuantityNodeOld ) {
                k = i - QuantityNodeOld - 1;
	             qCK.x = AddSchm.Coord[k].x - BegCK2[0];
	             qCK.y = AddSchm.Coord[k].y - BegCK2[1];
	             qCK.z = AddSchm.Coord[k].z - BegCK2[2];
	             MultMatr((double*)mk,(double*)&qCK,-3,3,1,(double*)&pCK);
	             pCK.x += BegCK1[0];
	             pCK.y += BegCK1[1];
	             pCK.z += BegCK1[2];
	             pCK.Flag = AddSchm.Coord[k].Flag;
                NumNodeA[i] = AddNode(pCK);
                if ( NumNodeA[i] == 0 ) {
                   MemoryFree(NumNodeA);
                   iRet = 4;  goto _30;   }
                }
          for ( i=QuantityNodeOld+1; i<=QuantityNodeOld+AddSchm.QuantityNode; i++ )
             if ( NumNodeA[i] < 0 ) {
                n1 = NumNodeA[i] = -NumNodeA[i];
                if ( n1 <= QuantityNodeOld && AddSchm.GetNodeBitFlag(i-QuantityNodeOld,7) == 0 )
                   SetNodeBitFlag(n1,3); //MP mark common nodes
                }
          for ( i=QuantityNodeOld+1; i<=QuantityNodeOld+AddSchm.QuantityNode; i++ )
             NumNode[i-QuantityNodeOld] = NumNodeA[i];
          }
       else {
          for ( i=QuantityNodeOld+1; i<=QuantityNodeOld+AddSchm.QuantityNode; i++ ) {
             if ( NumNodeA[i] == 0 || NumNode[i-QuantityNodeOld] == 0  ) continue;
             Node[0] = -NumNodeA[i];
             if ( Node[0] > QuantityNodeOld  ) continue;
             Node[1] = NumNode[i-QuantityNodeOld];
             if ( Node[1] <= QuantityNodeOld ) continue;
            _Bound.Include(0xF1,AddData.MaskContact,2,Node);
             }
          }

_10:   MemoryFree(NumNodeA);

       for ( i=0,Qntt=QuantityElem; i<AddSchm.QuantityElem; i++ ) {
          if ( AddSchm.GetBitFlag(i+1,7) && AddData.DeleteEqualElem != 2 ) continue;
	       pF2 = (FORMAT*)&AddSchm.pFormat[i];
	       NumNodeElem = (WORD*)Memory(pF2->QuantityNode+1,sizeof(WORD));
		   for (j=0; j<pF2->QuantityNode; j++){

     	        NumNodeElem[j] = NumNode[pF2->pNode[j]];
//if ( NumNodeElem[j] < 1 || NumNodeElem[j] > QuantityNode )Printf("aaaaaaaaaaaaaa");
		   }
          for ( j=0; j<Qntt; j++ ) {
	          if ( GetBitFlag(j+1,7) && AddData.DeleteEqualElem != 2  ) continue;
	          pF1 = (FORMAT*)&pFormat[j];
             if ( pF1->TypeElem > 1000 && pF2->TypeElem < 1000 ||
                  pF2->TypeElem > 1000 && pF1->TypeElem < 1000 ) continue;
	          n1 = ElemType(pF1->TypeElem);
	          if ( n1 == 0 || pF1->QuantityNode == 0 ) continue;
             if (AddData.DeleteEqualElem == 1 && pF1->QuantityNode == pF2->QuantityNode) {
//	            n2 = ElemType(pF2->TypeElem);
//	            if ( n1 != n2 ) continue;
  	             for (k=0; k<pF1->QuantityNode; k++) {
                   for (n=0; n<pF2->QuantityNode; n++)
		                if (pF1->pNode[k] == NumNodeElem[n])	goto _12;
                   goto _15;
_12:;              }
             NumElem[i+1] = j + 1;
             SetBitFlag(j+1,3); //MP mark common elements
             goto _20;	}
_15:;
           }
           NumTypeRigid[AddSchm._Rigid.GetRigidType(pF2->TypeRigid)] = 1;
           NumElem[i+1] = AddElemListNode(pF2->TypeElem,pF2->QuantityNode,NumNodeElem);
           if ( NumElem[i+1] == 0 ) {
               iRet = 5;  goto _30;   }
           pFormat[NumElem[i+1]-1].Flags = pF2->Flags;
_20:
	    MemoryFree(NumNodeElem);	}

       _SectionName.Read();
       _RigidName.Read();
       AddSchm._SectionName.Read();
       AddSchm._RigidName.Read();

       NumSechName = (WORD*)Memory(AddSchm._SectionName.Quantity+1,sizeof(WORD));
       NumRgdName = (WORD*)Memory(AddSchm._RigidName.Quantity+1,sizeof(WORD));
       LstNew = (WORD*)Memory(AddSchm.QuantityElem+1,sizeof(WORD));

       for ( i=0; i<AddSchm._SectionName.Quantity; i++ ) {
          DI = AddSchm._SectionName.Get(i+1);
          NumSechName[i+1] = _SectionName.Add(*DI);
          }

       for ( i=0; i<AddSchm._RigidName.Quantity; i++ ) {
          pS = AddSchm._RigidName.Get(i+1);
          NumRgdName[i+1] = _RigidName.Add(pS);
          }

       for ( i=1; i<=AddSchm._Rigid.GetQuantityRigid(); i++ ) {
	       if ( NumTypeRigid[i] == 0 ) continue;
	       AddSchm._Rigid.GetRigid(i,n,Type,m,&pSF,k,&Lst);
	       for ( j=0; j<m; j++ ) {
             if ( strcmpup((char*)&pSF[j],"NAME") == 0 ) {  j++;  continue; }
             if ( strcmpup((char*)&pSF[j],"NT") == 0 && j < m - 1 ) {
                n = pSF[j+1].d + 0.01;
                if ( n < 0 || n > AddSchm._SectionName.Quantity ) n = 0;
                pSF[j+1].d = NumSechName[n]+0.00001;  break;  }
             if ( strcmpup((char*)&pSF[j],"NMRGD") == 0 && j < m - 1 ) {
                n = pSF[j+1].d + 0.01;
                if ( n < 0 || n > AddSchm._RigidName.Quantity ) n = 0;
                pSF[j+1].d = NumRgdName[n]+0.00001;
                break;  }
             }
	       for ( j=0; j<k; j++ ) {
             if ( Lst[j] <= AddSchm.QuantityElem ) LstNew[j] = NumElem[Lst[j]];
             else LstNew[j] = 0;
             }
	       _Rigid.Include(Type,m,pSF,k,LstNew);
	       }
      _Rigid.Write(FilePrj,QuantityElem);
       RigidInFormat();

 /* Добавление шаpниpов  */
       _Joint.Add(AddSchm._Joint,AddSchm.QuantityElem,NumElem);
       _Joint.Write(FilePrj,QuantityElem);
       JointInFormat();
       AddSchm._Joint.Delete();
       _Joint.Delete();

  /* Добавление жесткиx вставок  */
       _Insert.Add(AddSchm._Insert,AddSchm.QuantityElem,NumElem);
       _Insert.Write(FilePrj,QuantityElem);
       InsertInFormat(_Insert);
       AddSchm._Insert.Delete();
       _Insert.Delete();

  /* Добавление углов чистого вpащения  */
       _Corner.Add(AddSchm._Corner,AddSchm.QuantityElem,NumElem);
       _Corner.Write(FilePrj,QuantityElem);
       InsertInFormat(_Corner);
       AddSchm._Corner.Delete();
       _Corner.Delete();

  /* Добавление систем кооpдинат вычисления усилий  */
       _CornerNapr.Add(AddSchm._CornerNapr,AddSchm.QuantityElem,NumElem);
       _CornerNapr.Write(FilePrj,QuantityElem);
       InsertInFormat(_CornerNapr);
       AddSchm._CornerNapr.Delete();
       _CornerNapr.Delete();

       for ( i=0; i<10; i++ ) {
	       if ( i == 4 || i == 7 || i == 8 ) {
	          _List[i].Add(AddSchm._List[i],AddSchm.QuantityNode,NumNode);
	          _List[i].Write(FilePrj,QuantityNode);  }
          else {
             _List[i].Add(AddSchm._List[i],AddSchm.QuantityElem,NumElem);
             _List[i].Write(FilePrj,QuantityElem);  }
	       AddSchm._List[i].Delete();
	      _List[i].Delete();  }

       _Bound.Add(AddSchm._Bound,AddSchm.QuantityNode,NumNode);
       _Bound.Write(FilePrj,QuantityNode);
       AddSchm._Bound.Delete();
       _Bound.Delete();

       _Contur.Add(AddSchm._Contur,AddSchm.QuantityNode,NumNode);
       _Contur.Write(FilePrj,QuantityNode);
       AddSchm._Contur.Delete();
       _Contur.Delete();

       for ( i=1; i<=AddSchm._Steel.GetQuantityGroup();  i++ ) {
          SL = AddSchm._Steel.GetSteel(i);
          for ( j=0; j<SL->Quantity;  j++ ) {
             k = SL->List[j];
             if ( k && k <= AddSchm.QuantityElem ) SL->List[j] = NumElem[k];
             else SL->List[j] = 0;
             }
          n = _Steel.Include(SL->SteelEl,SL->Data,SL->Quantity,SL->List);
          if ( SL->Text ) _Steel.SetText(SL->Text,n);
          }

       _SteelUni.Add(AddSchm._SteelUni,AddSchm.QuantityElem,NumElem);
       _SteelUni.Write(FilePrj,QuantityElem);
       AddSchm._SteelUni.Delete();
       _SteelUni.Delete();

       for ( i=1; i<=AddSchm._SteelRigid.GetQuantityRigid(); i++ ) {
	       AddSchm._SteelRigid.GetRigid(i,n,Type,m,&pSF,k,&Lst);
	       for ( j=0; j<m; j++ ) {
             if ( strcmpup((char*)&pSF[j],"NAME") == 0 ) {  j++;  continue; }
             if ( strcmpup((char*)&pSF[j],"NT") == 0 && j < m - 1 ) {
                n = pSF[j+1].d + 0.01;
                pSF[j+1].d = NumSechName[n]+0.00001;  break;  }
             if ( strcmpup((char*)&pSF[j],"NMRGD") == 0 && j < m - 1 ) {
                n = pSF[j+1].d + 0.01;
                if ( n && n <= AddSchm._RigidName.Quantity ) pSF[j+1].d = NumRgdName[n]+0.00001;
                else pSF[j+1].d = 0;
                break;  }
             }
	       for ( j=0; j<k; j++ ) {
             if ( Lst[j] <= AddSchm.QuantityElem ) LstNew[j] = NumElem[Lst[j]];
             else LstNew[j] = 0;
             }
	       _SteelRigid.Include(Type,m,pSF,k,LstNew);
	       }
      _SteelRigid.Write(FilePrj,QuantityElem);
       AddSchm._SteelRigid.Delete();
      _SteelRigid.Delete();

       MemoryFree(LstNew);
       MemoryFree(NumSechName);
       MemoryFree(NumRgdName);

       if ( AddData.AddEfforsGroup ) {

	       DATA_LOAD Ld;
	      _Load.Delete();

	       for ( i=1; i<=AddSchm._LoadList.Quantity; i++ ) {

	          AddSchm.ReadLoad(Ld,AddSchm._LoadList,i);
            _Load.Delete();

	          for ( j=0; j<Ld.ForceNode.QuantityForceList; j++ ) {
		          pFL = &Ld.ForceNode.ForceList[j];
		          pFL->NumNodeFe = NumNode[pFL->NumNodeFe];
		          if ( pFL->NumNodeFe <= QuantityNodeOld && YesForceEqNode == 0 ) pFL->NumNodeFe = 0;
		          }
	          for ( j=0; j<Ld.ForceFE.QuantityForceList; j++ ) {
		          pFL = &Ld.ForceFE.ForceList[j];
		          pFL->NumNodeFe = NumElem[pFL->NumNodeFe];
		          }

	          if ( AddData.AddEfforsGroup == 1 ) {
		          if ( i<= _LoadList.Quantity ) ReadLoad(i);
		          else strncpy(_Load.Name,Ld.Name,MAX_LENGTH_NAME_LOAD);
		         _Load.Add(Ld);
		          WriteLoad(i,_Load.Name);   }

	          if ( AddData.AddEfforsGroup == 2 ) {
		          strncpy(s,AddSchm.Name,MAX_LENGTH_NAME_LOAD);
		          strncat(s,".",MAX_LENGTH_NAME_LOAD);
		          strncat(s,Ld.Name,MAX_LENGTH_NAME_LOAD);
		          s[MAX_LENGTH_NAME_LOAD] = 0;
		         _Load.Add(Ld);
		          strcpy(_Load.Name,s);
		          WriteLoadGroup(s);   }

	          }  }

       _Load.Delete();

       _List[8].Include(0,0,AddSchm.QuantityNode,NumNode);
       _List[8].Write(FilePrj,QuantityNode);
       _List[8].Delete();

       _List[9].Include(0,0,AddSchm.QuantityElem,NumElem);
       _List[9].Write(FilePrj,QuantityElem);
       _List[9].Delete();

_30:   MemoryFree(NumTypeRigid);
       MemoryFree(NumElem);
       MemoryFree(NumNode);

       return iRet;

}






















