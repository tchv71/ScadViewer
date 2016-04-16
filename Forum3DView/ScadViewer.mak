# Microsoft Developer Studio Generated NMAKE File, Based on ScadViewer.dsp
!IF "$(CFG)" == ""
CFG=ScadViewer - Win32 Debug11
!MESSAGE No configuration specified. Defaulting to ScadViewer - Win32 Debug11.
!ENDIF 

!IF "$(CFG)" != "ScadViewer - Win32 Release" && "$(CFG)" != "ScadViewer - Win32 Debug" && "$(CFG)" != "ScadViewer - Win32 Debug11" && "$(CFG)" != "ScadViewer - Win32 Release11"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ScadViewer.mak" CFG="ScadViewer - Win32 Debug11"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ScadViewer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ScadViewer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ScadViewer - Win32 Debug11" (based on "Win32 (x86) Application")
!MESSAGE "ScadViewer - Win32 Release11" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ScadViewer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\hlp\ScfExplorer.hm" "$(OUTDIR)\ScfExplorer.exe"

!ELSE 

ALL : "Forum3DView - Win32 Release" ".\hlp\ScfExplorer.hm" "$(OUTDIR)\ScfExplorer.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Forum3DView - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ScadViewer.obj"
	-@erase "$(INTDIR)\ScadViewer.pch"
	-@erase "$(INTDIR)\ScadViewer.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ScfExplorer.exe"
	-@erase "hlp\ScfExplorer.hm"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MD /W3 /GX /O2 /I "..\msclass\include" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\ScadViewer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ScadViewer.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ScadViewer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib Version.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ScfExplorer.pdb" /machine:I386 /out:"$(OUTDIR)\ScfExplorer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ScadViewer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ScadViewer.res" \
	".\Forum3DView\Release\Forum3DView.lib"

"$(OUTDIR)\ScfExplorer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\hlp\ScfExplorer.hm" "$(OUTDIR)\ScfExplorer.exe" "$(OUTDIR)\ScadViewer.bsc"

!ELSE 

ALL : "Forum3DView - Win32 Debug" ".\hlp\ScfExplorer.hm" "$(OUTDIR)\ScfExplorer.exe" "$(OUTDIR)\ScadViewer.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Forum3DView - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ScadViewer.obj"
	-@erase "$(INTDIR)\ScadViewer.pch"
	-@erase "$(INTDIR)\ScadViewer.res"
	-@erase "$(INTDIR)\ScadViewer.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ScadViewer.bsc"
	-@erase "$(OUTDIR)\ScfExplorer.exe"
	-@erase "$(OUTDIR)\ScfExplorer.ilk"
	-@erase "$(OUTDIR)\ScfExplorer.pdb"
	-@erase "hlp\ScfExplorer.hm"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\msclass\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ScadViewer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ScadViewer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ScadViewer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ScadViewer.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ScadViewer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib Version.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ScfExplorer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ScfExplorer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ScadViewer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ScadViewer.res" \
	".\Forum3DView\Debug\Forum3DView.lib"

"$(OUTDIR)\ScfExplorer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug11"

OUTDIR=.\Debug11
INTDIR=.\obj\Debug11
# Begin Custom Macros
OutDir=.\Debug11
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\hlp\ScfExplorer.hm" "$(OUTDIR)\ScfExplorer.exe" "$(OUTDIR)\ScadViewer.bsc"

!ELSE 

ALL : "Forum3DView - Win32 Debug11" ".\hlp\ScfExplorer.hm" "$(OUTDIR)\ScfExplorer.exe" "$(OUTDIR)\ScadViewer.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Forum3DView - Win32 Debug11CLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ScadViewer.obj"
	-@erase "$(INTDIR)\ScadViewer.pch"
	-@erase "$(INTDIR)\ScadViewer.res"
	-@erase "$(INTDIR)\ScadViewer.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ScadViewer.bsc"
	-@erase "$(OUTDIR)\ScfExplorer.exe"
	-@erase "$(OUTDIR)\ScfExplorer.ilk"
	-@erase "$(OUTDIR)\ScfExplorer.pdb"
	-@erase "hlp\ScfExplorer.hm"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\msclass\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ScadViewer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ScadViewer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ScadViewer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ScadViewer.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ScadViewer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib Version.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ScfExplorer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ScfExplorer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ScadViewer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ScadViewer.res" \
	".\Forum3DView\Debug11\Forum3DView.lib"

"$(OUTDIR)\ScfExplorer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Release11"

OUTDIR=.\Release11
INTDIR=.\obj\Release11
# Begin Custom Macros
OutDir=.\Release11
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\hlp\ScfExplorer.hm" "$(OUTDIR)\ScfExplorer.exe"

!ELSE 

ALL : "Forum3DView - Win32 Release11" ".\hlp\ScfExplorer.hm" "$(OUTDIR)\ScfExplorer.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Forum3DView - Win32 Release11CLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ScadViewer.obj"
	-@erase "$(INTDIR)\ScadViewer.pch"
	-@erase "$(INTDIR)\ScadViewer.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ScfExplorer.exe"
	-@erase "hlp\ScfExplorer.hm"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MD /W3 /GX /O2 /I "..\msclass\include" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\ScadViewer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ScadViewer.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ScadViewer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib Version.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ScfExplorer.pdb" /machine:I386 /out:"$(OUTDIR)\ScfExplorer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ScadViewer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ScadViewer.res" \
	".\Forum3DView\Release11\Forum3DView.lib"

"$(OUTDIR)\ScfExplorer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ScadViewer.dep")
!INCLUDE "ScadViewer.dep"
!ELSE 
!MESSAGE Warning: cannot find "ScadViewer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ScadViewer - Win32 Release" || "$(CFG)" == "ScadViewer - Win32 Debug" || "$(CFG)" == "ScadViewer - Win32 Debug11" || "$(CFG)" == "ScadViewer - Win32 Release11"
SOURCE=.\ScadViewer.cpp

!IF  "$(CFG)" == "ScadViewer - Win32 Release"


"$(INTDIR)\ScadViewer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ScadViewer.pch"


!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug"


"$(INTDIR)\ScadViewer.obj"	"$(INTDIR)\ScadViewer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ScadViewer.pch"


!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug11"


"$(INTDIR)\ScadViewer.obj"	"$(INTDIR)\ScadViewer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ScadViewer.pch"


!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Release11"


"$(INTDIR)\ScadViewer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ScadViewer.pch"


!ENDIF 

SOURCE=.\ScadViewer.rc

!IF  "$(CFG)" == "ScadViewer - Win32 Release"


"$(INTDIR)\ScadViewer.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\ScadViewer.res" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug"


"$(INTDIR)\ScadViewer.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x419 /fo"$(INTDIR)\ScadViewer.res" /d "_DEBUG" /d "SCAD11" $(SOURCE)


!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug11"


"$(INTDIR)\ScadViewer.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x419 /fo"$(INTDIR)\ScadViewer.res" /d "_DEBUG" /d "SCAD11" $(SOURCE)


!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Release11"


"$(INTDIR)\ScadViewer.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\ScadViewer.res" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ScadViewer - Win32 Release"

CPP_SWITCHES=/nologo /Zp1 /MD /W3 /GX /O2 /I "..\msclass\include" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\ScadViewer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ScadViewer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug"

CPP_SWITCHES=/nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\msclass\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ScadViewer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ScadViewer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug11"

CPP_SWITCHES=/nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\msclass\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ScadViewer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ScadViewer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Release11"

CPP_SWITCHES=/nologo /Zp1 /MD /W3 /GX /O2 /I "..\msclass\include" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\ScadViewer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ScadViewer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Resource.h

!IF  "$(CFG)" == "ScadViewer - Win32 Release"

TargetName=ScfExplorer
InputPath=.\Resource.h

".\hlp\ScfExplorer.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
<< 
	

!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug"

TargetName=ScfExplorer
InputPath=.\Resource.h

".\hlp\ScfExplorer.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
<< 
	

!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug11"

TargetName=ScfExplorer
InputPath=.\Resource.h

".\hlp\ScfExplorer.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
<< 
	

!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Release11"

TargetName=ScfExplorer
InputPath=.\Resource.h

".\hlp\ScfExplorer.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
<< 
	

!ENDIF 

!IF  "$(CFG)" == "ScadViewer - Win32 Release"

"Forum3DView - Win32 Release" : 
   cd ".\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Release" 
   cd ".."

"Forum3DView - Win32 ReleaseCLEAN" : 
   cd ".\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug"

"Forum3DView - Win32 Debug" : 
   cd ".\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Debug" 
   cd ".."

"Forum3DView - Win32 DebugCLEAN" : 
   cd ".\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Debug11"

"Forum3DView - Win32 Debug11" : 
   cd ".\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Debug11" 
   cd ".."

"Forum3DView - Win32 Debug11CLEAN" : 
   cd ".\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Debug11" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "ScadViewer - Win32 Release11"

"Forum3DView - Win32 Release11" : 
   cd ".\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Release11" 
   cd ".."

"Forum3DView - Win32 Release11CLEAN" : 
   cd ".\Forum3DView"
   $(MAKE) /$(MAKEFLAGS) /F .\Forum3DView.mak CFG="Forum3DView - Win32 Release11" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 


!ENDIF 

