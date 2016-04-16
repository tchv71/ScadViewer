# Microsoft Developer Studio Generated NMAKE File, Based on OglIso.dsp
!IF "$(CFG)" == ""
CFG=OglIso - Win32 Debug11
!MESSAGE No configuration specified. Defaulting to OglIso - Win32 Debug11.
!ENDIF 

!IF "$(CFG)" != "OglIso - Win32 Release" && "$(CFG)" != "OglIso - Win32 Debug" && "$(CFG)" != "OglIso - Win32 Debug11" && "$(CFG)" != "OglIso - Win32 Release11"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OglIso.mak" CFG="OglIso - Win32 Debug11"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OglIso - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OglIso - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OglIso - Win32 Debug11" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OglIso - Win32 Release11" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "OglIso - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\OglIso.dll"

!ELSE 

ALL : "Forum3DView - Win32 Release" "$(OUTDIR)\OglIso.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Forum3DView - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\OglIso.obj"
	-@erase "$(INTDIR)\OglIso.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OglIso.dll"
	-@erase "$(OUTDIR)\OglIso.exp"
	-@erase "$(OUTDIR)\OglIso.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OGLISO_EXPORTS" /Fp"$(INTDIR)\OglIso.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OglIso.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\OglIso.pdb" /machine:I386 /def:".\OglIso.def" /out:"$(OUTDIR)\OglIso.dll" /implib:"$(OUTDIR)\OglIso.lib" 
DEF_FILE= \
	".\OglIso.def"
LINK32_OBJS= \
	"$(INTDIR)\OglIso.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\Forum3DView\Release\Forum3DView.lib"

"$(OUTDIR)\OglIso.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OglIso - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\OglIso.dll"

!ELSE 

ALL : "Forum3DView - Win32 Debug" "$(OUTDIR)\OglIso.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Forum3DView - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\OglIso.obj"
	-@erase "$(INTDIR)\OglIso.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OglIso.dll"
	-@erase "$(OUTDIR)\OglIso.exp"
	-@erase "$(OUTDIR)\OglIso.ilk"
	-@erase "$(OUTDIR)\OglIso.lib"
	-@erase "$(OUTDIR)\OglIso.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OGLISO_EXPORTS" /Fp"$(INTDIR)\OglIso.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OglIso.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\OglIso.pdb" /debug /machine:I386 /def:".\OglIso.def" /out:"$(OUTDIR)\OglIso.dll" /implib:"$(OUTDIR)\OglIso.lib" /pdbtype:sept 
DEF_FILE= \
	".\OglIso.def"
LINK32_OBJS= \
	"$(INTDIR)\OglIso.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\Forum3DView\Debug\Forum3DView.lib"

"$(OUTDIR)\OglIso.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OglIso - Win32 Debug11"

OUTDIR=.\Debug11
INTDIR=.\Debug11
# Begin Custom Macros
OutDir=.\Debug11
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\Debug11\SCADOglIso.dll" "$(OUTDIR)\OglIso.bsc"

!ELSE 

ALL : "Forum3DView - Win32 Debug11" "..\Debug11\SCADOglIso.dll" "$(OUTDIR)\OglIso.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Forum3DView - Win32 Debug11CLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\OglIso.obj"
	-@erase "$(INTDIR)\OglIso.pch"
	-@erase "$(INTDIR)\OglIso.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OglIso.bsc"
	-@erase "$(OUTDIR)\SCADOglIso.exp"
	-@erase "$(OUTDIR)\SCADOglIso.lib"
	-@erase "$(OUTDIR)\SCADOglIso.pdb"
	-@erase "..\Debug11\SCADOglIso.dll"
	-@erase "..\Debug11\SCADOglIso.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\Scad11\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OGLISO_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\OglIso.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OglIso.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\OglIso.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\OglIso.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\SCADOglIso.pdb" /debug /machine:I386 /def:".\OglIso.def" /out:"..\Debug11/SCADOglIso.dll" /implib:"$(OUTDIR)\SCADOglIso.lib" /pdbtype:sept 
DEF_FILE= \
	".\OglIso.def"
LINK32_OBJS= \
	"$(INTDIR)\OglIso.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\Forum3DView\Debug11\Forum3DView.lib"

"..\Debug11\SCADOglIso.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OglIso - Win32 Release11"

OUTDIR=.\Release11
INTDIR=.\Release11

!IF "$(RECURSE)" == "0" 

ALL : "..\Release11\SCADOglIso.dll"

!ELSE 

ALL : "Forum3DView - Win32 Release11" "..\Release11\SCADOglIso.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Forum3DView - Win32 Release11CLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\OglIso.obj"
	-@erase "$(INTDIR)\OglIso.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SCADOglIso.exp"
	-@erase "$(OUTDIR)\SCADOglIso.lib"
	-@erase "..\Release11\SCADOglIso.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\Scad11\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OGLISO_EXPORTS" /Fp"$(INTDIR)\OglIso.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OglIso.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\SCADOglIso.pdb" /machine:I386 /def:".\OglIso.def" /out:"..\Release11/SCADOglIso.dll" /implib:"$(OUTDIR)\SCADOglIso.lib" 
DEF_FILE= \
	".\OglIso.def"
LINK32_OBJS= \
	"$(INTDIR)\OglIso.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\Forum3DView\Release11\Forum3DView.lib"

"..\Release11\SCADOglIso.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("OglIso.dep")
!INCLUDE "OglIso.dep"
!ELSE 
!MESSAGE Warning: cannot find "OglIso.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OglIso - Win32 Release" || "$(CFG)" == "OglIso - Win32 Debug" || "$(CFG)" == "OglIso - Win32 Debug11" || "$(CFG)" == "OglIso - Win32 Release11"
SOURCE=.\OglIso.cpp

!IF  "$(CFG)" == "OglIso - Win32 Release"


"$(INTDIR)\OglIso.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OglIso.pch"


!ELSEIF  "$(CFG)" == "OglIso - Win32 Debug"


"$(INTDIR)\OglIso.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OglIso.pch"


!ELSEIF  "$(CFG)" == "OglIso - Win32 Debug11"


"$(INTDIR)\OglIso.obj"	"$(INTDIR)\OglIso.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OglIso.pch"


!ELSEIF  "$(CFG)" == "OglIso - Win32 Release11"


"$(INTDIR)\OglIso.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OglIso.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "OglIso - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OGLISO_EXPORTS" /Fp"$(INTDIR)\OglIso.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OglIso.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OglIso - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OGLISO_EXPORTS" /Fp"$(INTDIR)\OglIso.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OglIso.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OglIso - Win32 Debug11"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\Scad11\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OGLISO_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\OglIso.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\OglIso.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OglIso - Win32 Release11"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\Scad11\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OGLISO_EXPORTS" /Fp"$(INTDIR)\OglIso.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OglIso.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "OglIso - Win32 Release"

"Forum3DView - Win32 Release" : 
   cd "\work\Projects\ScadSoft\FORUMVIEW\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Release" 
   cd "..\OglIso"

"Forum3DView - Win32 ReleaseCLEAN" : 
   cd "\work\Projects\ScadSoft\FORUMVIEW\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Release" RECURSE=1 CLEAN 
   cd "..\OglIso"

!ELSEIF  "$(CFG)" == "OglIso - Win32 Debug"

"Forum3DView - Win32 Debug" : 
   cd "\work\Projects\ScadSoft\FORUMVIEW\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Debug" 
   cd "..\OglIso"

"Forum3DView - Win32 DebugCLEAN" : 
   cd "\work\Projects\ScadSoft\FORUMVIEW\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\OglIso"

!ELSEIF  "$(CFG)" == "OglIso - Win32 Debug11"

"Forum3DView - Win32 Debug11" : 
   cd "\work\Projects\ScadSoft\FORUMVIEW\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Debug11" 
   cd "..\OglIso"

"Forum3DView - Win32 Debug11CLEAN" : 
   cd "\work\Projects\ScadSoft\FORUMVIEW\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Debug11" RECURSE=1 CLEAN 
   cd "..\OglIso"

!ELSEIF  "$(CFG)" == "OglIso - Win32 Release11"

"Forum3DView - Win32 Release11" : 
   cd "\work\Projects\ScadSoft\FORUMVIEW\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Release11" 
   cd "..\OglIso"

"Forum3DView - Win32 Release11CLEAN" : 
   cd "\work\Projects\ScadSoft\FORUMVIEW\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Release11" RECURSE=1 CLEAN 
   cd "..\OglIso"

!ENDIF 


!ENDIF 

