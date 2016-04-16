# Microsoft Developer Studio Generated NMAKE File, Based on Forum3DView.dsp
!IF "$(CFG)" == ""
CFG=Forum3DView - Win32 Debug11
!MESSAGE No configuration specified. Defaulting to Forum3DView - Win32 Debug11.
!ENDIF 

!IF "$(CFG)" != "Forum3DView - Win32 Release" && "$(CFG)" != "Forum3DView - Win32 Debug" && "$(CFG)" != "Forum3DView - Win32 Debug11" && "$(CFG)" != "Forum3DView - Win32 Release11"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Forum3DView.mak" CFG="Forum3DView - Win32 Debug11"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Forum3DView - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Forum3DView - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Forum3DView - Win32 Debug11" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Forum3DView - Win32 Release11" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Forum3DView - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\Release\Forum3DView.dll"

!ELSE 

ALL : "MsClass - Win32 Release" "..\Release\Forum3DView.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"MsClass - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\BmpSaveDlg.obj"
	-@erase "$(INTDIR)\CameraDialogBar.obj"
	-@erase "$(INTDIR)\ColorButton.obj"
	-@erase "$(INTDIR)\ColourPopup.obj"
	-@erase "$(INTDIR)\Cutter.obj"
	-@erase "$(INTDIR)\DepthDialogBar.obj"
	-@erase "$(INTDIR)\DibGlRenderer.obj"
	-@erase "$(INTDIR)\DirChangeListener.obj"
	-@erase "$(INTDIR)\DockFolderWnd.obj"
	-@erase "$(INTDIR)\ExportDXF.obj"
	-@erase "$(INTDIR)\FileProc.obj"
	-@erase "$(INTDIR)\FolderListCtrl.obj"
	-@erase "$(INTDIR)\FolderTreeDockingWnd.obj"
	-@erase "$(INTDIR)\Forum3DView.obj"
	-@erase "$(INTDIR)\Forum3DView.pch"
	-@erase "$(INTDIR)\Forum3DView.res"
	-@erase "$(INTDIR)\ForumViewGeometry.obj"
	-@erase "$(INTDIR)\GLDraw.obj"
	-@erase "$(INTDIR)\GLRenderer.obj"
	-@erase "$(INTDIR)\IsoViewerFrame.obj"
	-@erase "$(INTDIR)\IsoViewGeometry.obj"
	-@erase "$(INTDIR)\MainScadViewerFrame.obj"
	-@erase "$(INTDIR)\MouseManipulatorWnd.obj"
	-@erase "$(INTDIR)\NumEdit.obj"
	-@erase "$(INTDIR)\OptionsGeneral.obj"
	-@erase "$(INTDIR)\OptionsMaterial.obj"
	-@erase "$(INTDIR)\OptionsRtf.obj"
	-@erase "$(INTDIR)\PropertiesCtrl.obj"
	-@erase "$(INTDIR)\Renderer.obj"
	-@erase "$(INTDIR)\ResultsDlg.obj"
	-@erase "$(INTDIR)\Rotate.obj"
	-@erase "$(INTDIR)\SCAD3DMdlSettings.obj"
	-@erase "$(INTDIR)\SCADDefProj.obj"
	-@erase "$(INTDIR)\SCADFolderTreeCtrl.obj"
	-@erase "$(INTDIR)\SCADTwoPartBtn.obj"
	-@erase "$(INTDIR)\ScadViewerDoc.obj"
	-@erase "$(INTDIR)\ScadViewerFrm.obj"
	-@erase "$(INTDIR)\SCADViewerStatBar.obj"
	-@erase "$(INTDIR)\ScadViewerView.obj"
	-@erase "$(INTDIR)\SettingManager.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SvGluTesselator.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\View3DBox.obj"
	-@erase "$(INTDIR)\ViewerOptions.obj"
	-@erase "$(INTDIR)\ViewGeometry.obj"
	-@erase "$(INTDIR)\ViewLib.obj"
	-@erase "$(OUTDIR)\Forum3DView.exp"
	-@erase "$(OUTDIR)\Forum3DView.lib"
	-@erase "..\Release\Forum3DView.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MD /W3 /GX /O2 /I "..\..\msclass\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /Fp"$(INTDIR)\Forum3DView.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\Forum3DView.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Forum3DView.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Forum3DView.pdb" /machine:I386 /def:".\Forum3DView.def" /out:"../Release/Forum3DView.dll" /implib:"$(OUTDIR)\Forum3DView.lib" 
DEF_FILE= \
	".\Forum3DView.def"
LINK32_OBJS= \
	"$(INTDIR)\BmpSaveDlg.obj" \
	"$(INTDIR)\CameraDialogBar.obj" \
	"$(INTDIR)\ColorButton.obj" \
	"$(INTDIR)\ColourPopup.obj" \
	"$(INTDIR)\Cutter.obj" \
	"$(INTDIR)\DepthDialogBar.obj" \
	"$(INTDIR)\DibGlRenderer.obj" \
	"$(INTDIR)\DirChangeListener.obj" \
	"$(INTDIR)\DockFolderWnd.obj" \
	"$(INTDIR)\ExportDXF.obj" \
	"$(INTDIR)\FileProc.obj" \
	"$(INTDIR)\FolderListCtrl.obj" \
	"$(INTDIR)\FolderTreeDockingWnd.obj" \
	"$(INTDIR)\Forum3DView.obj" \
	"$(INTDIR)\ForumViewGeometry.obj" \
	"$(INTDIR)\GLDraw.obj" \
	"$(INTDIR)\GLRenderer.obj" \
	"$(INTDIR)\IsoViewerFrame.obj" \
	"$(INTDIR)\IsoViewGeometry.obj" \
	"$(INTDIR)\MainScadViewerFrame.obj" \
	"$(INTDIR)\MouseManipulatorWnd.obj" \
	"$(INTDIR)\NumEdit.obj" \
	"$(INTDIR)\OptionsGeneral.obj" \
	"$(INTDIR)\OptionsMaterial.obj" \
	"$(INTDIR)\OptionsRtf.obj" \
	"$(INTDIR)\PropertiesCtrl.obj" \
	"$(INTDIR)\Renderer.obj" \
	"$(INTDIR)\ResultsDlg.obj" \
	"$(INTDIR)\Rotate.obj" \
	"$(INTDIR)\SCAD3DMdlSettings.obj" \
	"$(INTDIR)\SCADDefProj.obj" \
	"$(INTDIR)\SCADFolderTreeCtrl.obj" \
	"$(INTDIR)\SCADTwoPartBtn.obj" \
	"$(INTDIR)\ScadViewerDoc.obj" \
	"$(INTDIR)\ScadViewerFrm.obj" \
	"$(INTDIR)\SCADViewerStatBar.obj" \
	"$(INTDIR)\ScadViewerView.obj" \
	"$(INTDIR)\SettingManager.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SvGluTesselator.obj" \
	"$(INTDIR)\View3DBox.obj" \
	"$(INTDIR)\ViewerOptions.obj" \
	"$(INTDIR)\ViewGeometry.obj" \
	"$(INTDIR)\ViewLib.obj" \
	"$(INTDIR)\Forum3DView.res" \
	"..\..\..\..\..\work\Projects\ScadSoft\msclass\Release\MsClass.lib"

"..\Release\Forum3DView.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : "..\Debug\Forum3DView.dll"

!ELSE 

ALL : "MsClass - Win32 Debug" "..\Debug\Forum3DView.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"MsClass - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\BmpSaveDlg.obj"
	-@erase "$(INTDIR)\CameraDialogBar.obj"
	-@erase "$(INTDIR)\ColorButton.obj"
	-@erase "$(INTDIR)\ColourPopup.obj"
	-@erase "$(INTDIR)\Cutter.obj"
	-@erase "$(INTDIR)\DepthDialogBar.obj"
	-@erase "$(INTDIR)\DibGlRenderer.obj"
	-@erase "$(INTDIR)\DirChangeListener.obj"
	-@erase "$(INTDIR)\DockFolderWnd.obj"
	-@erase "$(INTDIR)\ExportDXF.obj"
	-@erase "$(INTDIR)\FileProc.obj"
	-@erase "$(INTDIR)\FolderListCtrl.obj"
	-@erase "$(INTDIR)\FolderTreeDockingWnd.obj"
	-@erase "$(INTDIR)\Forum3DView.obj"
	-@erase "$(INTDIR)\Forum3DView.pch"
	-@erase "$(INTDIR)\Forum3DView.res"
	-@erase "$(INTDIR)\ForumViewGeometry.obj"
	-@erase "$(INTDIR)\GLDraw.obj"
	-@erase "$(INTDIR)\GLRenderer.obj"
	-@erase "$(INTDIR)\IsoViewerFrame.obj"
	-@erase "$(INTDIR)\IsoViewGeometry.obj"
	-@erase "$(INTDIR)\MainScadViewerFrame.obj"
	-@erase "$(INTDIR)\MouseManipulatorWnd.obj"
	-@erase "$(INTDIR)\NumEdit.obj"
	-@erase "$(INTDIR)\OptionsGeneral.obj"
	-@erase "$(INTDIR)\OptionsMaterial.obj"
	-@erase "$(INTDIR)\OptionsRtf.obj"
	-@erase "$(INTDIR)\PropertiesCtrl.obj"
	-@erase "$(INTDIR)\Renderer.obj"
	-@erase "$(INTDIR)\ResultsDlg.obj"
	-@erase "$(INTDIR)\Rotate.obj"
	-@erase "$(INTDIR)\SCAD3DMdlSettings.obj"
	-@erase "$(INTDIR)\SCADDefProj.obj"
	-@erase "$(INTDIR)\SCADFolderTreeCtrl.obj"
	-@erase "$(INTDIR)\SCADTwoPartBtn.obj"
	-@erase "$(INTDIR)\ScadViewerDoc.obj"
	-@erase "$(INTDIR)\ScadViewerFrm.obj"
	-@erase "$(INTDIR)\SCADViewerStatBar.obj"
	-@erase "$(INTDIR)\ScadViewerView.obj"
	-@erase "$(INTDIR)\SettingManager.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SvGluTesselator.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\View3DBox.obj"
	-@erase "$(INTDIR)\ViewerOptions.obj"
	-@erase "$(INTDIR)\ViewGeometry.obj"
	-@erase "$(INTDIR)\ViewLib.obj"
	-@erase "$(OUTDIR)\Forum3DView.exp"
	-@erase "$(OUTDIR)\Forum3DView.lib"
	-@erase "$(OUTDIR)\Forum3DView.pdb"
	-@erase "..\Debug\Forum3DView.dll"
	-@erase "..\Debug\Forum3DView.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\msclass\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /Fp"$(INTDIR)\Forum3DView.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\Forum3DView.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Forum3DView.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Forum3DView.pdb" /debug /machine:I386 /def:".\Forum3DView.def" /out:"../Debug/Forum3DView.dll" /implib:"$(OUTDIR)\Forum3DView.lib" /pdbtype:sept 
DEF_FILE= \
	".\Forum3DView.def"
LINK32_OBJS= \
	"$(INTDIR)\BmpSaveDlg.obj" \
	"$(INTDIR)\CameraDialogBar.obj" \
	"$(INTDIR)\ColorButton.obj" \
	"$(INTDIR)\ColourPopup.obj" \
	"$(INTDIR)\Cutter.obj" \
	"$(INTDIR)\DepthDialogBar.obj" \
	"$(INTDIR)\DibGlRenderer.obj" \
	"$(INTDIR)\DirChangeListener.obj" \
	"$(INTDIR)\DockFolderWnd.obj" \
	"$(INTDIR)\ExportDXF.obj" \
	"$(INTDIR)\FileProc.obj" \
	"$(INTDIR)\FolderListCtrl.obj" \
	"$(INTDIR)\FolderTreeDockingWnd.obj" \
	"$(INTDIR)\Forum3DView.obj" \
	"$(INTDIR)\ForumViewGeometry.obj" \
	"$(INTDIR)\GLDraw.obj" \
	"$(INTDIR)\GLRenderer.obj" \
	"$(INTDIR)\IsoViewerFrame.obj" \
	"$(INTDIR)\IsoViewGeometry.obj" \
	"$(INTDIR)\MainScadViewerFrame.obj" \
	"$(INTDIR)\MouseManipulatorWnd.obj" \
	"$(INTDIR)\NumEdit.obj" \
	"$(INTDIR)\OptionsGeneral.obj" \
	"$(INTDIR)\OptionsMaterial.obj" \
	"$(INTDIR)\OptionsRtf.obj" \
	"$(INTDIR)\PropertiesCtrl.obj" \
	"$(INTDIR)\Renderer.obj" \
	"$(INTDIR)\ResultsDlg.obj" \
	"$(INTDIR)\Rotate.obj" \
	"$(INTDIR)\SCAD3DMdlSettings.obj" \
	"$(INTDIR)\SCADDefProj.obj" \
	"$(INTDIR)\SCADFolderTreeCtrl.obj" \
	"$(INTDIR)\SCADTwoPartBtn.obj" \
	"$(INTDIR)\ScadViewerDoc.obj" \
	"$(INTDIR)\ScadViewerFrm.obj" \
	"$(INTDIR)\SCADViewerStatBar.obj" \
	"$(INTDIR)\ScadViewerView.obj" \
	"$(INTDIR)\SettingManager.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SvGluTesselator.obj" \
	"$(INTDIR)\View3DBox.obj" \
	"$(INTDIR)\ViewerOptions.obj" \
	"$(INTDIR)\ViewGeometry.obj" \
	"$(INTDIR)\ViewLib.obj" \
	"$(INTDIR)\Forum3DView.res" \
	"..\..\..\..\..\work\Projects\ScadSoft\ForumView\Debug\MsClass.lib"

"..\Debug\Forum3DView.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug11"

OUTDIR=.\Debug11
INTDIR=.\Debug11

!IF "$(RECURSE)" == "0" 

ALL : "..\Debug11\Forum3DView.dll"

!ELSE 

ALL : "..\Debug11\Forum3DView.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\BmpSaveDlg.obj"
	-@erase "$(INTDIR)\CameraDialogBar.obj"
	-@erase "$(INTDIR)\ColorButton.obj"
	-@erase "$(INTDIR)\ColourPopup.obj"
	-@erase "$(INTDIR)\Cutter.obj"
	-@erase "$(INTDIR)\DepthDialogBar.obj"
	-@erase "$(INTDIR)\DibGlRenderer.obj"
	-@erase "$(INTDIR)\DirChangeListener.obj"
	-@erase "$(INTDIR)\DockFolderWnd.obj"
	-@erase "$(INTDIR)\ExportDXF.obj"
	-@erase "$(INTDIR)\FileProc.obj"
	-@erase "$(INTDIR)\FolderListCtrl.obj"
	-@erase "$(INTDIR)\FolderTreeDockingWnd.obj"
	-@erase "$(INTDIR)\Forum3DView.obj"
	-@erase "$(INTDIR)\Forum3DView.pch"
	-@erase "$(INTDIR)\Forum3DView.res"
	-@erase "$(INTDIR)\ForumViewGeometry.obj"
	-@erase "$(INTDIR)\GLDraw.obj"
	-@erase "$(INTDIR)\GLRenderer.obj"
	-@erase "$(INTDIR)\IsoViewerFrame.obj"
	-@erase "$(INTDIR)\IsoViewGeometry.obj"
	-@erase "$(INTDIR)\MainScadViewerFrame.obj"
	-@erase "$(INTDIR)\MouseManipulatorWnd.obj"
	-@erase "$(INTDIR)\NumEdit.obj"
	-@erase "$(INTDIR)\OptionsGeneral.obj"
	-@erase "$(INTDIR)\OptionsMaterial.obj"
	-@erase "$(INTDIR)\OptionsRtf.obj"
	-@erase "$(INTDIR)\PropertiesCtrl.obj"
	-@erase "$(INTDIR)\Renderer.obj"
	-@erase "$(INTDIR)\ResultsDlg.obj"
	-@erase "$(INTDIR)\Rotate.obj"
	-@erase "$(INTDIR)\SCAD3DMdlSettings.obj"
	-@erase "$(INTDIR)\SCADDefProj.obj"
	-@erase "$(INTDIR)\SCADFolderTreeCtrl.obj"
	-@erase "$(INTDIR)\SCADTwoPartBtn.obj"
	-@erase "$(INTDIR)\ScadViewerDoc.obj"
	-@erase "$(INTDIR)\ScadViewerFrm.obj"
	-@erase "$(INTDIR)\SCADViewerStatBar.obj"
	-@erase "$(INTDIR)\ScadViewerView.obj"
	-@erase "$(INTDIR)\SettingManager.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SvGluTesselator.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\View3DBox.obj"
	-@erase "$(INTDIR)\ViewerOptions.obj"
	-@erase "$(INTDIR)\ViewGeometry.obj"
	-@erase "$(INTDIR)\ViewLib.obj"
	-@erase "$(OUTDIR)\Forum3DView.exp"
	-@erase "$(OUTDIR)\Forum3DView.lib"
	-@erase "$(OUTDIR)\Forum3DView.pdb"
	-@erase "..\Debug11\Forum3DView.dll"
	-@erase "..\Debug11\Forum3DView.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\Scad11\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "SCAD11" /Fp"$(INTDIR)\Forum3DView.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\Forum3DView.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Forum3DView.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib Schema.lib Profile.lib ClassHelp.lib Result.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Forum3DView.pdb" /debug /machine:I386 /def:".\Forum3DView.def" /out:"../Debug11/Forum3DView.dll" /implib:"$(OUTDIR)\Forum3DView.lib" /pdbtype:sept /libpath:"..\..\Scad11\lib" 
DEF_FILE= \
	".\Forum3DView.def"
LINK32_OBJS= \
	"$(INTDIR)\BmpSaveDlg.obj" \
	"$(INTDIR)\CameraDialogBar.obj" \
	"$(INTDIR)\ColorButton.obj" \
	"$(INTDIR)\ColourPopup.obj" \
	"$(INTDIR)\Cutter.obj" \
	"$(INTDIR)\DepthDialogBar.obj" \
	"$(INTDIR)\DibGlRenderer.obj" \
	"$(INTDIR)\DirChangeListener.obj" \
	"$(INTDIR)\DockFolderWnd.obj" \
	"$(INTDIR)\ExportDXF.obj" \
	"$(INTDIR)\FileProc.obj" \
	"$(INTDIR)\FolderListCtrl.obj" \
	"$(INTDIR)\FolderTreeDockingWnd.obj" \
	"$(INTDIR)\Forum3DView.obj" \
	"$(INTDIR)\ForumViewGeometry.obj" \
	"$(INTDIR)\GLDraw.obj" \
	"$(INTDIR)\GLRenderer.obj" \
	"$(INTDIR)\IsoViewerFrame.obj" \
	"$(INTDIR)\IsoViewGeometry.obj" \
	"$(INTDIR)\MainScadViewerFrame.obj" \
	"$(INTDIR)\MouseManipulatorWnd.obj" \
	"$(INTDIR)\NumEdit.obj" \
	"$(INTDIR)\OptionsGeneral.obj" \
	"$(INTDIR)\OptionsMaterial.obj" \
	"$(INTDIR)\OptionsRtf.obj" \
	"$(INTDIR)\PropertiesCtrl.obj" \
	"$(INTDIR)\Renderer.obj" \
	"$(INTDIR)\ResultsDlg.obj" \
	"$(INTDIR)\Rotate.obj" \
	"$(INTDIR)\SCAD3DMdlSettings.obj" \
	"$(INTDIR)\SCADDefProj.obj" \
	"$(INTDIR)\SCADFolderTreeCtrl.obj" \
	"$(INTDIR)\SCADTwoPartBtn.obj" \
	"$(INTDIR)\ScadViewerDoc.obj" \
	"$(INTDIR)\ScadViewerFrm.obj" \
	"$(INTDIR)\SCADViewerStatBar.obj" \
	"$(INTDIR)\ScadViewerView.obj" \
	"$(INTDIR)\SettingManager.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SvGluTesselator.obj" \
	"$(INTDIR)\View3DBox.obj" \
	"$(INTDIR)\ViewerOptions.obj" \
	"$(INTDIR)\ViewGeometry.obj" \
	"$(INTDIR)\ViewLib.obj" \
	"$(INTDIR)\Forum3DView.res"

"..\Debug11\Forum3DView.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11"

OUTDIR=.\Release11
INTDIR=.\Release11

!IF "$(RECURSE)" == "0" 

ALL : "..\Release11\Forum3DView.dll"

!ELSE 

ALL : "..\Release11\Forum3DView.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\BmpSaveDlg.obj"
	-@erase "$(INTDIR)\CameraDialogBar.obj"
	-@erase "$(INTDIR)\ColorButton.obj"
	-@erase "$(INTDIR)\ColourPopup.obj"
	-@erase "$(INTDIR)\Cutter.obj"
	-@erase "$(INTDIR)\DepthDialogBar.obj"
	-@erase "$(INTDIR)\DibGlRenderer.obj"
	-@erase "$(INTDIR)\DirChangeListener.obj"
	-@erase "$(INTDIR)\DockFolderWnd.obj"
	-@erase "$(INTDIR)\ExportDXF.obj"
	-@erase "$(INTDIR)\FileProc.obj"
	-@erase "$(INTDIR)\FolderListCtrl.obj"
	-@erase "$(INTDIR)\FolderTreeDockingWnd.obj"
	-@erase "$(INTDIR)\Forum3DView.obj"
	-@erase "$(INTDIR)\Forum3DView.pch"
	-@erase "$(INTDIR)\Forum3DView.res"
	-@erase "$(INTDIR)\ForumViewGeometry.obj"
	-@erase "$(INTDIR)\GLDraw.obj"
	-@erase "$(INTDIR)\GLRenderer.obj"
	-@erase "$(INTDIR)\IsoViewerFrame.obj"
	-@erase "$(INTDIR)\IsoViewGeometry.obj"
	-@erase "$(INTDIR)\MainScadViewerFrame.obj"
	-@erase "$(INTDIR)\MouseManipulatorWnd.obj"
	-@erase "$(INTDIR)\NumEdit.obj"
	-@erase "$(INTDIR)\OptionsGeneral.obj"
	-@erase "$(INTDIR)\OptionsMaterial.obj"
	-@erase "$(INTDIR)\OptionsRtf.obj"
	-@erase "$(INTDIR)\PropertiesCtrl.obj"
	-@erase "$(INTDIR)\Renderer.obj"
	-@erase "$(INTDIR)\ResultsDlg.obj"
	-@erase "$(INTDIR)\Rotate.obj"
	-@erase "$(INTDIR)\SCAD3DMdlSettings.obj"
	-@erase "$(INTDIR)\SCADDefProj.obj"
	-@erase "$(INTDIR)\SCADFolderTreeCtrl.obj"
	-@erase "$(INTDIR)\SCADTwoPartBtn.obj"
	-@erase "$(INTDIR)\ScadViewerDoc.obj"
	-@erase "$(INTDIR)\ScadViewerFrm.obj"
	-@erase "$(INTDIR)\SCADViewerStatBar.obj"
	-@erase "$(INTDIR)\ScadViewerView.obj"
	-@erase "$(INTDIR)\SettingManager.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SvGluTesselator.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\View3DBox.obj"
	-@erase "$(INTDIR)\ViewerOptions.obj"
	-@erase "$(INTDIR)\ViewGeometry.obj"
	-@erase "$(INTDIR)\ViewLib.obj"
	-@erase "$(OUTDIR)\Forum3DView.exp"
	-@erase "$(OUTDIR)\Forum3DView.lib"
	-@erase "..\Release11\Forum3DView.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=df.exe
CPP=cl.exe
CPP_PROJ=/nologo /Zp1 /MD /W3 /GX /O2 /I "..\..\Scad11\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /D "SCAD11" /Fp"$(INTDIR)\Forum3DView.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\Forum3DView.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Forum3DView.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib Schema.lib Profile.lib ClassHelp.lib Result.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Forum3DView.pdb" /machine:I386 /def:".\Forum3DView.def" /out:"../Release11/Forum3DView.dll" /implib:"$(OUTDIR)\Forum3DView.lib" /libpath:"..\..\Scad11\lib" 
DEF_FILE= \
	".\Forum3DView.def"
LINK32_OBJS= \
	"$(INTDIR)\BmpSaveDlg.obj" \
	"$(INTDIR)\CameraDialogBar.obj" \
	"$(INTDIR)\ColorButton.obj" \
	"$(INTDIR)\ColourPopup.obj" \
	"$(INTDIR)\Cutter.obj" \
	"$(INTDIR)\DepthDialogBar.obj" \
	"$(INTDIR)\DibGlRenderer.obj" \
	"$(INTDIR)\DirChangeListener.obj" \
	"$(INTDIR)\DockFolderWnd.obj" \
	"$(INTDIR)\ExportDXF.obj" \
	"$(INTDIR)\FileProc.obj" \
	"$(INTDIR)\FolderListCtrl.obj" \
	"$(INTDIR)\FolderTreeDockingWnd.obj" \
	"$(INTDIR)\Forum3DView.obj" \
	"$(INTDIR)\ForumViewGeometry.obj" \
	"$(INTDIR)\GLDraw.obj" \
	"$(INTDIR)\GLRenderer.obj" \
	"$(INTDIR)\IsoViewerFrame.obj" \
	"$(INTDIR)\IsoViewGeometry.obj" \
	"$(INTDIR)\MainScadViewerFrame.obj" \
	"$(INTDIR)\MouseManipulatorWnd.obj" \
	"$(INTDIR)\NumEdit.obj" \
	"$(INTDIR)\OptionsGeneral.obj" \
	"$(INTDIR)\OptionsMaterial.obj" \
	"$(INTDIR)\OptionsRtf.obj" \
	"$(INTDIR)\PropertiesCtrl.obj" \
	"$(INTDIR)\Renderer.obj" \
	"$(INTDIR)\ResultsDlg.obj" \
	"$(INTDIR)\Rotate.obj" \
	"$(INTDIR)\SCAD3DMdlSettings.obj" \
	"$(INTDIR)\SCADDefProj.obj" \
	"$(INTDIR)\SCADFolderTreeCtrl.obj" \
	"$(INTDIR)\SCADTwoPartBtn.obj" \
	"$(INTDIR)\ScadViewerDoc.obj" \
	"$(INTDIR)\ScadViewerFrm.obj" \
	"$(INTDIR)\SCADViewerStatBar.obj" \
	"$(INTDIR)\ScadViewerView.obj" \
	"$(INTDIR)\SettingManager.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SvGluTesselator.obj" \
	"$(INTDIR)\View3DBox.obj" \
	"$(INTDIR)\ViewerOptions.obj" \
	"$(INTDIR)\ViewGeometry.obj" \
	"$(INTDIR)\ViewLib.obj" \
	"$(INTDIR)\Forum3DView.res"

"..\Release11\Forum3DView.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Forum3DView.dep")
!INCLUDE "Forum3DView.dep"
!ELSE 
!MESSAGE Warning: cannot find "Forum3DView.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Forum3DView - Win32 Release" || "$(CFG)" == "Forum3DView - Win32 Debug" || "$(CFG)" == "Forum3DView - Win32 Debug11" || "$(CFG)" == "Forum3DView - Win32 Release11"
SOURCE=..\BmpSaveDlg.cpp

"$(INTDIR)\BmpSaveDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CameraDialogBar.cpp

"$(INTDIR)\CameraDialogBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"


SOURCE=..\ColorButton.cpp

"$(INTDIR)\ColorButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ColourPopup.cpp

"$(INTDIR)\ColourPopup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Cutter.cpp

"$(INTDIR)\Cutter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\DepthDialogBar.cpp

"$(INTDIR)\DepthDialogBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\DibGlRenderer.cpp

"$(INTDIR)\DibGlRenderer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\DirChangeListener.cpp

"$(INTDIR)\DirChangeListener.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\DockFolderWnd.cpp

"$(INTDIR)\DockFolderWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ExportDXF.cpp

"$(INTDIR)\ExportDXF.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FileProc.cpp

"$(INTDIR)\FileProc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FolderListCtrl.cpp

"$(INTDIR)\FolderListCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\FolderTreeDockingWnd.cpp

"$(INTDIR)\FolderTreeDockingWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Forum3DView.cpp

"$(INTDIR)\Forum3DView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"


SOURCE=.\Forum3DView.rc

!IF  "$(CFG)" == "Forum3DView - Win32 Release"


"$(INTDIR)\Forum3DView.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x419 /fo"$(INTDIR)\Forum3DView.res" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug"


"$(INTDIR)\Forum3DView.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x419 /fo"$(INTDIR)\Forum3DView.res" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug11"


"$(INTDIR)\Forum3DView.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x419 /fo"$(INTDIR)\Forum3DView.res" /d "_DEBUG" /d "_AFXDLL" /d "SCAD11" $(SOURCE)


!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11"


"$(INTDIR)\Forum3DView.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x419 /fo"$(INTDIR)\Forum3DView.res" /d "NDEBUG" /d "_AFXDLL" /d "SCAD11" $(SOURCE)


!ENDIF 

SOURCE=..\ForumViewGeometry.cpp

"$(INTDIR)\ForumViewGeometry.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\GLDraw.cpp

"$(INTDIR)\GLDraw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\GLRenderer.cpp

"$(INTDIR)\GLRenderer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\IsoViewerFrame.cpp

"$(INTDIR)\IsoViewerFrame.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\IsoViewGeometry.cpp

"$(INTDIR)\IsoViewGeometry.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\MainScadViewerFrame.cpp

"$(INTDIR)\MainScadViewerFrame.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\MouseManipulatorWnd.cpp

"$(INTDIR)\MouseManipulatorWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\NumEdit.cpp

"$(INTDIR)\NumEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"


SOURCE=..\OptionsGeneral.cpp

"$(INTDIR)\OptionsGeneral.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\OptionsMaterial.cpp

"$(INTDIR)\OptionsMaterial.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\OptionsRtf.cpp

"$(INTDIR)\OptionsRtf.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\PropertiesCtrl.cpp

"$(INTDIR)\PropertiesCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Renderer.cpp

"$(INTDIR)\Renderer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ResultsDlg.cpp

!IF  "$(CFG)" == "Forum3DView - Win32 Release"

CPP_SWITCHES=/nologo /Zp1 /MD /W3 /GX /O2 /I "..\..\msclass\include" /I "Forum3DView" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /Fp"$(INTDIR)\Forum3DView.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ResultsDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug"

CPP_SWITCHES=/nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\msclass\include" /I "Forum3DView" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /Fp"$(INTDIR)\Forum3DView.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\ResultsDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug11"

CPP_SWITCHES=/nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\Scad11\include" /I "Forum3DView" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "SCAD11" /Fp"$(INTDIR)\Forum3DView.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\ResultsDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11"

CPP_SWITCHES=/nologo /Zp1 /MD /W3 /GX /O2 /I "..\..\Scad11\include" /I "Forum3DView" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /D "SCAD11" /Fp"$(INTDIR)\Forum3DView.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ResultsDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\Rotate.cpp

"$(INTDIR)\Rotate.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\SCAD3DMdlSettings.cpp

"$(INTDIR)\SCAD3DMdlSettings.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\SCADDefProj.cpp

"$(INTDIR)\SCADDefProj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\SCADFolderTreeCtrl.cxx

"$(INTDIR)\SCADFolderTreeCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\SCADTwoPartBtn.cxx

"$(INTDIR)\SCADTwoPartBtn.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ScadViewerDoc.cpp

"$(INTDIR)\ScadViewerDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ScadViewerFrm.cpp

"$(INTDIR)\ScadViewerFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\SCADViewerStatBar.cpp

"$(INTDIR)\SCADViewerStatBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ScadViewerView.cpp

"$(INTDIR)\ScadViewerView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\SettingManager.cpp

"$(INTDIR)\SettingManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Forum3DView - Win32 Release"

CPP_SWITCHES=/nologo /Zp1 /MD /W3 /GX /O2 /I "..\..\msclass\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /Fp"$(INTDIR)\Forum3DView.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Forum3DView.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug"

CPP_SWITCHES=/nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\msclass\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /Fp"$(INTDIR)\Forum3DView.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Forum3DView.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug11"

CPP_SWITCHES=/nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\Scad11\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "SCAD11" /Fp"$(INTDIR)\Forum3DView.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Forum3DView.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11"

CPP_SWITCHES=/nologo /Zp1 /MD /W3 /GX /O2 /I "..\..\Scad11\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /D "SCAD11" /Fp"$(INTDIR)\Forum3DView.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Forum3DView.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\SvGluTesselator.cpp

"$(INTDIR)\SvGluTesselator.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\View3DBox.cpp

"$(INTDIR)\View3DBox.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ViewerOptions.cpp

"$(INTDIR)\ViewerOptions.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ViewGeometry.cpp

"$(INTDIR)\ViewGeometry.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ViewLib.cpp

"$(INTDIR)\ViewLib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Forum3DView.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "Forum3DView - Win32 Release"

"MsClass - Win32 Release" : 
   cd "\work\Projects\ScadSoft\msclass"
   $(MAKE) /$(MAKEFLAGS) /F .\MsClass.mak CFG="MsClass - Win32 Release" 
   cd "..\..\..\..\Symbian\Carbide\workspace\Forum3DView\Forum3DView"

"MsClass - Win32 ReleaseCLEAN" : 
   cd "\work\Projects\ScadSoft\msclass"
   $(MAKE) /$(MAKEFLAGS) /F .\MsClass.mak CFG="MsClass - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\..\Symbian\Carbide\workspace\Forum3DView\Forum3DView"

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug"

"MsClass - Win32 Debug" : 
   cd "\work\Projects\ScadSoft\msclass"
   $(MAKE) /$(MAKEFLAGS) /F .\MsClass.mak CFG="MsClass - Win32 Debug" 
   cd "..\..\..\..\Symbian\Carbide\workspace\Forum3DView\Forum3DView"

"MsClass - Win32 DebugCLEAN" : 
   cd "\work\Projects\ScadSoft\msclass"
   $(MAKE) /$(MAKEFLAGS) /F .\MsClass.mak CFG="MsClass - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\..\Symbian\Carbide\workspace\Forum3DView\Forum3DView"

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug11"

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11"

!ENDIF 


!ENDIF 

