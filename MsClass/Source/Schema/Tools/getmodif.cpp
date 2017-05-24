#include <stdafx.h>
#include "schema.h"

EXPORT int SCHEMA::GetModify()
{
	int Mod = Modify, i;

   if ( memcmp(&Tree[171].TimeModify,&TimeNull,sizeof(FILETIME) ) == 0 ) Modify = 1;

	if ( _Rigid.Modify )         Mod = 1;
	if ( _Bound.GetModify() )    Mod = 1;
	if ( _Joint.GetModify() )    Mod = 1;
	if ( _Insert.GetModify() )   Mod = 1;
	if ( _Corner.GetModify() )   Mod = 1;
   if ( Mod ) {
      for ( i=171; i<=174; i++ ) SetTreeTime(i);
      Modify = 1;  }

	if ( _List[4].GetModify() || BitRead(ModifyAll,50) )  {   // str 34  doc15
      Mod = 1;  SetTreeTime(174);  }

   if ( UniteSchem.Quantity == 0 ) for ( i=0; i<_LoadList.Quantity; i++ )
	   if ( _LoadList.Inf[i].Load.Modify ) {
           if ( _LoadList.Inf[i].TypeDynamic ) SetTreeTime(174);
            _LoadList.Modify = 1;
            }
	if ( _LoadList.Modify ) {  SetTreeTime(172);  Mod = 1;  }

	if ( _List[0].GetModify() || _CornerNapr.GetModify() ) {
      Mod = 1;  SetTreeTime(173);
      return 3;  }

   for ( i=1; i<10; i++ ) if ( _List[i].Modify )  Mod = 1;

   for ( i=0; i<20; i++ )
      if ( BitRead(ModifyAll,i) ) {  Mod = 1;  SetTreeTime(180+i);  }

   for ( i=0; i<_LoadGroup.Quantity; i++ )
	   if ( _LoadGroup.Inf[i].Load.Modify )  _LoadGroup.Modify = 1;
        if ( _Load.GetModify() || _LoadGroup.Modify ) Mod = 1;
        if ( ModifyCalc ) Mod = 1;

   if ( Mod ) return 4;

   if ( _Contur.GetModify() )     Mod = 1;
   if ( _Steel.GetModify() )      Mod = 1;
   if ( _SteelUni.GetModify() )   Mod = 1;
   if ( _SteelRigid.GetModify() ) Mod = 1;
   if ( _Blocks.GetModify() )     
   {
	   Modify = 1;
	   Mod = 1;
   }

   if ( Mod ) {
      SetTreeTime(179);
      return 5;  }

   return Mod;

}