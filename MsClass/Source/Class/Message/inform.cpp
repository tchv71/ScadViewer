#include <stdafx.h>
#include "inform.h"
#include "crash.h"

EXPORT void INFORM::Init() {
		 if ( this ) memset(this,0,sizeof(INFORM));
		 }

EXPORT int  INFORM::Init(LPCSTR NameFile, int Num ){
		 int QuantityInform;
		 if ( this == NULL ) return 1;
		 Init();
		 FileWork.Open(NameFile,"r");
		 FileWork.Read(&MinNumInform,3*sizeof(WORD)+sizeof(long),0ul);
		 QuantityInform = MaxNumInform - MinNumInform + 1;
		 Access = (ACCESS*)Memory(QuantityInform,sizeof(ACCESS));
		 FileWork.Read(Access,QuantityInform*(long)sizeof(ACCESS),PosAccess);
		 Inform.Point = (LPSTR)Memory(MaxLength+2);
		 Inform.Text  = Inform.Point + 1;
         NumBase = Num;
		 return 0;
}

EXPORT void INFORM::Delete() {
		 if ( this == NULL ) return;
		 FileWork.Close();
		 if ( Access ) MemoryFree(Access);
		 if ( Inform.Point )   MemoryFree(Inform.Point);
		 Init();
}

EXPORT TEXT_INFORM FAR * INFORM::Load(int NumInform) {

		 int i, Num;

         NumInform += NumBase;
		 if ( this == NULL || Access == NULL ) Error("Not load Inform",NumInform);

		 Inform.QuantityString = 0;
//       memset(Inform.Text,0,MaxLength);

		 if ( NumInform < MinNumInform ||  NumInform > MaxNumInform )
	     Error("Error in the Number of Information",NumInform);

		 Num = NumInform - MinNumInform;
		 if ( Access[Num].Pos == 0 )
	     Error("There is not Information Number",NumInform);

		 FileWork.Read(Inform.Point,Access[Num].Length,Access[Num].Pos);
         for ( i=0; i<Access[Num].Length; i++ ) {
			 Inform.Point[i] += 256UL - ( Access[Num].Pos + i ) % 256;
			 if ( Inform.Point[i] == 0 ) Inform.QuantityString++;
	  }
		 Inform.Type = Inform.Point[0];
		 Inform.Length = (WORD)(Access[Num].Length - 1);

		 return &Inform;

}

EXPORT void  INFORM::Error(LPCSTR Text,long Num) {
		char Txt[12];
		sprintf(Txt,"%ld",Num);
		CrashFull("Class INFORM, file :",FileWork.GetFileName(),Text,Txt,NULL);
}

EXPORT int  INFORM::InformIn(int Num) {
     Num += NumBase;
	  if ( Num < MinNumInform || Num > MaxNumInform ) return 1;
    if ( Access[Num-MinNumInform].Pos == 0 ) return 1;
	 return 0;  }