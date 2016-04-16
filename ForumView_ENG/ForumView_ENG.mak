# Microsoft Developer Studio Generated NMAKE File, Based on ForumView_ENG.dsp
!IF "$(CFG)" == ""
CFG=ForumView_ENG - Win32 Debug11
!MESSAGE No configuration specified. Defaulting to ForumView_ENG - Win32 Debug11.
!ENDIF 

!IF "$(CFG)" != "ForumView_ENG - Win32 Release" && "$(CFG)" != "ForumView_ENG - Win32 Debug" && "$(CFG)" != "ForumView_ENG - Win32 Debug11" && "$(CFG)" != "ForumView_ENG - Win32 Release11"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ForumView_ENG.mak" CFG="ForumView_ENG - Win32 Debug11"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ForumView_ENG - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ForumView_ENG - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ForumView_ENG - Win32 Debug11" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ForumView_ENG - Win32 Release11" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ForumView_ENG - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\Release\ForumView_ENG.dll"


CLEAN :
	-@erase "$(INTDIR)\FV_Eng.res"
	-@erase "$(OUTDIR)\ForumView_ENG.exp"
	-@erase "..\Release\ForumView_ENG.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FORUMVIEW_ENG_EXPORTS" /Fp"$(INTDIR)\ForumView_ENG.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FV_Eng.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ForumView_ENG.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\ForumView_ENG.pdb" /machine:I386 /out:"../Release/ForumView_ENG.dll" /implib:"$(OUTDIR)\ForumView_ENG.lib" /NOENTRY 
LINK32_OBJS= \
	"$(INTDIR)\FV_Eng.res"

"..\Release\ForumView_ENG.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ForumView_ENG - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\Debug\ForumView_ENG.dll"


CLEAN :
	-@erase "$(INTDIR)\FV_Eng.res"
	-@erase "$(OUTDIR)\ForumView_ENG.exp"
	-@erase "$(OUTDIR)\ForumView_ENG.pdb"
	-@erase "..\Debug\ForumView_ENG.dll"
	-@erase "..\Debug\ForumView_ENG.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FORUMVIEW_ENG_EXPORTS" /Fp"$(INTDIR)\ForumView_ENG.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FV_Eng.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ForumView_ENG.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\ForumView_ENG.pdb" /debug /machine:I386 /out:"../Debug/ForumView_ENG.dll" /implib:"$(OUTDIR)\ForumView_ENG.lib" /pdbtype:sept /NOENTRY 
LINK32_OBJS= \
	"$(INTDIR)\FV_Eng.res"

"..\Debug\ForumView_ENG.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ForumView_ENG - Win32 Debug11"

OUTDIR=.\Debug11
INTDIR=.\Debug11

ALL : "..\Debug11\ForumView_ENG.dll"


CLEAN :
	-@erase "$(OUTDIR)\ForumView_ENG.exp"
	-@erase "$(OUTDIR)\ForumView_ENG.pdb"
	-@erase "..\Debug11\ForumView_ENG.dll"
	-@erase "..\Debug11\ForumView_ENG.ilk"
	-@erase ".\Debug\FV_Eng.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FORUMVIEW_ENG_EXPORTS" /Fp"$(INTDIR)\ForumView_ENG.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"Debug/FV_Eng.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ForumView_ENG.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\ForumView_ENG.pdb" /debug /machine:I386 /out:"../Debug11/ForumView_ENG.dll" /implib:"$(OUTDIR)\ForumView_ENG.lib" /pdbtype:sept /NOENTRY 
LINK32_OBJS= \
	".\Debug\FV_Eng.res"

"..\Debug11\ForumView_ENG.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ForumView_ENG - Win32 Release11"

OUTDIR=.\Release11
INTDIR=.\Release11

ALL : "..\Release11\ForumView_ENG.dll"


CLEAN :
	-@erase "$(OUTDIR)\ForumView_ENG.exp"
	-@erase "..\Release11\ForumView_ENG.dll"
	-@erase ".\Release\FV_Eng.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FORUMVIEW_ENG_EXPORTS" /Fp"$(INTDIR)\ForumView_ENG.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"Release/FV_Eng.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ForumView_ENG.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\ForumView_ENG.pdb" /machine:I386 /out:"../Release11/ForumView_ENG.dll" /implib:"$(OUTDIR)\ForumView_ENG.lib" /NOENTRY 
LINK32_OBJS= \
	".\Release\FV_Eng.res"

"..\Release11\ForumView_ENG.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ForumView_ENG.dep")
!INCLUDE "ForumView_ENG.dep"
!ELSE 
!MESSAGE Warning: cannot find "ForumView_ENG.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ForumView_ENG - Win32 Release" || "$(CFG)" == "ForumView_ENG - Win32 Debug" || "$(CFG)" == "ForumView_ENG - Win32 Debug11" || "$(CFG)" == "ForumView_ENG - Win32 Release11"
SOURCE=.\ForumView_ENG.rc

!IF  "$(CFG)" == "ForumView_ENG - Win32 Release"


"$(INTDIR)\FV_Eng.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\FV_Eng.res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "ForumView_ENG - Win32 Debug"


"$(INTDIR)\FV_Eng.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\FV_Eng.res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "ForumView_ENG - Win32 Debug11"


".\Debug\FV_Eng.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x419 /fo"Debug/FV_Eng.res" /d "_DEBUG" /d "SCAD11" $(SOURCE)


!ELSEIF  "$(CFG)" == "ForumView_ENG - Win32 Release11"


".\Release\FV_Eng.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x419 /fo"Release/FV_Eng.res" /d "NDEBUG" /d "SCAD11" $(SOURCE)


!ENDIF 


!ENDIF 

