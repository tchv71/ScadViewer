#include "stdafx.h"
#include <schema.h>

#include "FORUMFORCE.hpp"

EXPORT int FORUM_FORCE::DeleteTypeConstr( int NumPP )
{
    int i, j, k;
    OBJECT_LIST_STR *pOLS;
    FORUM_FORCE_STR *pFS;

	for ( i=1; i<=ListElem.Quantity; i++ ) {
        pOLS = ListElem.Get(i);
	    if ( pOLS->Mask == NumPP ) return 0; 
	}
    
    k = GetNumTimeForce(NumPP);
    if ( k )  TimeForce.Delete(k);
	
	for ( i=1; i<=ConstantForce.Quantity; i++ ) {
        pFS = GetConstantForce(i);
        for ( j=0,k=0; j<pFS->Quantity; j++ )
			if ( pFS->NumConstr[j] != NumPP ) pFS->NumConstr[k++] = pFS->NumConstr[j]; 
        pFS->Quantity = k; 	}

	TypeConstr.Delete(NumPP);

	return 1;
}

EXPORT  int    FORUM_FORCE::GetTypeElem( int NumElem )
{
    int i, j, k=0;
    OBJECT_LIST_STR *pOLS;

	for ( i=1; i<=ListElem.Quantity; i++ ) {
        pOLS = ListElem.Get(i);
        for ( j=0; j<pOLS->Quantity; j++ )
			if ( pOLS->List[j] == NumElem ) k = pOLS->Mask; 
	}
	return k;
}

EXPORT  void    FORUM_FORCE::GetTypeListElem( int Type, int &Qnt, int **List  )
{
    int i;
    OBJECT_LIST_STR *pOLS;
    Qnt = 0;

	for ( i=1; i<=ListElem.Quantity; i++ ) {
        pOLS = ListElem.Get(i);
		if ( pOLS->Mask == Type ) {   
			Qnt   = pOLS->Quantity;
			*List = pOLS->List;
			return; }
	}
}

EXPORT  int   FORUM_FORCE::AddConstantForce( LPSTR Ident, FORUM_FORCE_STR &FS )
{
    return ConstantForce.AddObject(&FS.StandartForce,Ident,FS.Quantity,FS.NumConstr); 
}

EXPORT  void  FORUM_FORCE::ChangeConstantForce( int NumPP, LPSTR Ident, FORUM_FORCE_STR &FS )
{
    ConstantForce.ChangeObject(NumPP,&FS.StandartForce,Ident,FS.Quantity,FS.NumConstr); 
}

EXPORT  void  FORUM_FORCE::ChangeConstantForceListConstr( int NumPP, int Qnt, int *List )
{
    ConstantForce.ChangeComponent(NumPP,1,Qnt,List);
}

EXPORT  int   FORUM_FORCE::AddTimeForce( int NumConstr, FORUM_FORCE_STR &FS )
{
    FS.NumNameConstr = NumConstr;
    return TimeForce.AddObject(&FS.StandartForce,"",FS.Quantity,FS.NumConstr); 
}

EXPORT int FORUM_FORCE::GetNumTimeForce( int NumConstr )
{
    int i;
    FORUM_FORCE_STR *pFS;

	for ( i=1; i<=TimeForce.Quantity; i++ ) {
        pFS = GetTimeForce(i);
		if ( pFS->NumNameConstr == NumConstr ) return i;
	}

    return 0; 
}

EXPORT void FORUM_FORCE::ChangeTimeForce( int NumPP, FORUM_FORCE_STR &FS )
{
    TimeForce.ChangeObject(NumPP,&FS.StandartForce,"",FS.Quantity,FS.NumConstr); 
}


EXPORT void FORUM_FORCE::Compress(int QuantityOld, int * NewNum )
{
    ListElem.CompressObject(1,0,1,1,QuantityOld,NewNum,1,1,NULL);
}

EXPORT  void   FORUM_FORCE::Read( FILEBASE &Input, DOCUMENT & Doc)
{
    DOCUMENT  Work;
    Delete(); 
    if ( Doc.PosFile == 0 ) return;
    Input.Read(&Common,sizeof(FORUM_FORCE_COMMON),Doc.PosFile); 
    memcpy(&Work,&Doc,sizeof(DOCUMENT));
	Work.PosFile += sizeof(FORUM_FORCE_COMMON);
	TypeConstr.Read(Input,Work);
	Work.PosFile = Input.GetPosRead();
    ListElem.Read(Input,Work);
	Work.PosFile = Input.GetPosRead();
    ConstantForce.Read(Input,Work);
	Work.PosFile = Input.GetPosRead();
    TimeForce.Read(Input,Work);
}

EXPORT  void   FORUM_FORCE::Write( FILEBASE &Output, DOCUMENT &Doc )
{
    DOCUMENT  Work;
    Doc.PosFile = Output.GetLength(); 
    if ( ConstantForce.Quantity == 0 ) {
       ZeroMemory(&Doc,sizeof(DOCUMENT));
	   return;	} 
	Output.Write(&Common,sizeof(FORUM_FORCE_COMMON)); 
	TypeConstr.Write(Output,Work);
    ListElem.Write(Output,Work);
    ConstantForce.Write(Output,Work);
    TimeForce.Write(Output,Work);
    Doc.Length = Output.GetLength() - Doc.PosFile; 
}

EXPORT  void   FORUM_FORCE::Copy( FORUM_FORCE &FF )
{
    Delete();
    memcpy(&Common,&FF.Common,sizeof(FORUM_FORCE_COMMON)); 
    ListElem.Copy(&FF.ListElem);
    ConstantForce.Copy(&FF.ConstantForce);
    TimeForce.Copy(&FF.TimeForce);
}

EXPORT  void   FORUM_FORCE::AddListElem( int NumConstr, int Qnt, int Num[] )
{
    int i;
    OBJECT_LIST_STR *pOLS;
//    Qnt = 0;

	for ( i=1; i<=ListElem.Quantity; i++ ) {
        pOLS = ListElem.Get(i);
		if ( pOLS->Mask == NumConstr ) {   
           ListElem.ChangeList(i,Qnt,Num,1);
		   return;   } 
	}

    ListElem.Include(0,NumConstr,Qnt,Num);

}

EXPORT  void   FORUM_FORCE::DeleteListElem( int Qnt, int Num[] )
{
    ListElem.Clear(Qnt,Num);
    ListElem.CompressObject(1,0,1,1,0,NULL,1,1,NULL);
}

