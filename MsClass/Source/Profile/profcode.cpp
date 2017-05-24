#include <stdafx.h>
#include "profile.h"

void  PROFILE:: Code(LPCSTR NameInput, LPCSTR NameOutput ) {

      FILEBASE Out;
      FILETEXT Inp, InpSection;

      int  i, LenBuf, l;
      char buf[513], iRet=0, iRS, c, Word[40];
      BYTE knt, Type[512];
      SECTION sect;
      char drive[MAXDRIVE];
      char dir[MAXDIR];
      char file[MAXFILE];
      char ext[MAXEXT];
      DWORD PosFile, Len, CurrentPos;
      float f;
      UNITS UG;

      Out.Open(NameOutput,"rw");
      Inp.Open(NameInput,"r");

      Out.Write("**PRFL**",8);
      Out.Write(this,20);

      for ( i=0; ; i++ ) {
         if ( ReadProfString(Inp,buf,LenBuf) ) {
            iRet = 1;  goto _10;  }
         if ( buf[0] == '#' ) break;
         Out.StringWrite(buf);
         }
      QuantityLanguage = i;
      if ( QuantityLanguage < 1 ) {
	      Printf("Ошибки в числе языков");
         iRet = 1;  goto _10;  }

      for ( i=0; i<MAX_QUANTITY_GRAF+4; i++ ) {
         if ( ReadProfWord(Inp,buf,l)  ) {
            iRet = 1;  goto _10;  }
         if ( buf[0] == '#' ) break;
         strncpy(UG.Name,buf,10);
         if ( ReadProfWord(Inp,buf,l)  ) {
            iRet = 1;  goto _10;  }
         UG.coef = CharDouble(buf,knt);
         if ( knt || UG.coef < 0 ) {
            Printf("Ошибка в %d коэффициенте системы единиц",i+1);
            iRet = 2;  goto _10;  }
         if ( i == 0 ) TypeBase = UG.coef + 0.1;
         if ( i == 1 ) E = UG.coef;
         if ( i == 2 ) nu = UG.coef;
         if ( i == 3 ) ro = UG.coef;
         if ( i < 4 ) continue;
         Out.Write(&UG,sizeof(UNITS));
         }
      QuantityTypeGraf = i - 4;

      for ( ; ; ) {

         if ( ReadProfString(Inp,buf,LenBuf) ) break;
         if ( buf[0] == '#' ) break;
	 memset(&sect,0,sizeof(sect));  iRS = 0;
         PosFile = Out.GetLength();
         QuantityTypeSection++;
         Out.Write(&sect,16);

	 InpSection.Close();
	 InpSection.Open(buf,"r");
	 fnsplit(buf,drive,dir,file,ext);
	 strncpy(sect.NameFile,file,8);

    CurrentPos = 0;
	 if ( ReadProfString(InpSection,buf,LenBuf) ) {
	    Printf("Отсутствует тип сечения в файле: %s",InpSection.GetFileName());
            iRet = 3;  continue;  }

         Separate(buf,LenBuf,CurrentPos," ",Word);
         sect.Group = CharLong(Word,knt);
         if ( knt ) {
            Printf("Ошибка в типе сечения в файле: %s ",InpSection.GetFileName());
            iRet = 3;   continue;  }
         Separate(buf,LenBuf,CurrentPos," ",Word);
         sect.TypeInGroup = CharLong(Word,knt);
         if ( knt ) {
            Printf("Ошибка в характеристике типа сечения в файле: %s ",InpSection.GetFileName());
            iRet = 3;   continue;  }

         for ( i=0; ; i++ ) {
            if ( ReadProfString(InpSection,buf,LenBuf) ) {
               Printf("Ошибка в имени сечения в файле: %s ",InpSection.GetFileName());
               iRS = iRet = 3;  break;  }
            if ( buf[0] == '#' ) {
               if ( i != QuantityLanguage ) {
                  Printf("Число наименований сечения не соответствует числу языков в файле: %s ",
                     InpSection.GetFileName());
                  iRS = iRet = 3;   }
                  break;  }
            Out.StringWrite(buf);   }
         if ( iRS ) continue;

         for ( i=0; ; i++ ) {
            if ( ReadProfWord(InpSection,buf,l) ) {  iRS = 3;  break;  }
            if ( buf[0] == '#' || i == MAX_QUANTITY_GRAF ) break;
            Type[i] = CharLong(buf,knt);
            if ( knt ) { iRS = 3;  break;  }
            }
         if ( iRS || i == 0 || i > QuantityTypeGraf  ) {
            Printf("Ошибка в типах граф в файле : %s",InpSection.GetFileName());
            iRet = 3;    continue;   }
         Out.Write(Type,i);
         sect.QuantityGraf = i;

         Len = Out.GetLength();
         for ( i=0; ; i++ ) {
            if ( ReadProfWord(InpSection,buf,l) ) {  iRS = 3;  break;  }
            if ( buf[0] == '#' || i == sect.QuantityGraf ) break;
            Out.Write(buf,strlen(buf)+1);   }
         if ( iRS || i == sect.QuantityGraf  ) {
            Printf("Ошибка в именах граф в файле : %s",InpSection.GetFileName());
            iRet = 3;    continue;   }
         Out.Write("",1);
         sect.LengthNamePrint = Out.GetLength() - Len;

         memset(Type,0,sizeof(Type));
         for ( i=0; ; i++ ) {
            if ( ReadProfWord(InpSection,buf,l) ) {  iRS = 3;  break;  }
            if ( buf[0] == '#' || i == sect.QuantityGraf ) break;
            Type[i] = CharLong(buf,knt);
            if ( knt ) { iRS = 3;  break;  }
            }
         if ( iRS ) {
            Printf("Ошибка в признаках печати граф в файле : %s",InpSection.GetFileName());
            iRet = 3;    continue;   }
         Out.Write(Type,sect.QuantityGraf);

         for ( ; ; ) {

             c =  ReadProfWord(InpSection,buf,l);
             if ( c == -1 || buf[0] == '#' ) break;
             buf[MAX_STRING_NAME-1] = 0;
             sect.QuantityString++;
             Out.StringWrite(buf);

             for ( i=1; i<sect.QuantityGraf; i++ ) {
                if ( InpSection.ReadWord(buf,l) ) {
                   Printf("Ошибка в cтроке %hd в файле/n %s",sect.QuantityString,InpSection.GetFileName());
                   iRet = 2;  goto _10;  }
                f = CharDouble(buf,knt);
                if ( knt ) {
                    Printf("Ошибка в cтроке %hd в файле/n %s",sect.QuantityString,InpSection.GetFileName());
                   iRet = 2;   }
                Out.Write(&f,sizeof(float));  }
             }

         Out.Write(&sect,16,PosFile);
	 InpSection.Close();	 }

      Out.Write(&QuantityLanguage,20,8);


_10:  if ( iRet ) {
         if ( iRet == 1 ) Printf("Ошибки в файле %s",NameInput);
         Out.Delete();   }

      Inp.Close();
      Out.Close();

}