# Microsoft Developer Studio Project File - Name="Forum3DView" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Forum3DView - Win32 Debug11
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Forum3DView.mak".
!MESSAGE 
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
!MESSAGE "Forum3DView - Win32 Release11D" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Work/Projects/ScadSoft/ForumView/Forum3DView", RJOAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Forum3DView - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "..\..\msclass\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib libdb44.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../Release/Forum3DView.dll"

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\msclass\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib libdb44d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../Debug/Forum3DView.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug11"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Forum3DView___Win32_Debug110"
# PROP BASE Intermediate_Dir "Forum3DView___Win32_Debug110"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug11"
# PROP Intermediate_Dir "Debug11"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\msclass\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\Scad11\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "SCAD11" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL" /d "SCAD11"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../Debug/Forum3DView11.dll" /pdbtype:sept
# ADD LINK32 Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib Schema.lib Profile11.lib ClassHelp.lib Result.lib libdb44d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:"Forum3DView11.def" /out:"../Debug11/Forum3DView11.dll" /pdbtype:sept /libpath:"..\..\Scad11\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Forum3DView___Win32_Release11"
# PROP BASE Intermediate_Dir "Forum3DView___Win32_Release11"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release11"
# PROP Intermediate_Dir "Release11"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "..\..\msclass\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "..\..\Scad11\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /D "SCAD11" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "SCAD11"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../Release/Forum3DView11.dll"
# ADD LINK32 Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib Schema.lib Profile11.lib ClassHelp.lib Result.lib libdb44.lib /nologo /subsystem:windows /dll /machine:I386 /def:"Forum3DView11.def" /out:"../Release11/Forum3DView11.dll" /libpath:"..\..\Scad11\lib"
# SUBTRACT LINK32 /pdb:none /debug

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11D"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Forum3DView___Win32_Release11D"
# PROP BASE Intermediate_Dir "Forum3DView___Win32_Release11D"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Forum3DView___Win32_Release11D"
# PROP Intermediate_Dir "Forum3DView___Win32_Release11D"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "..\..\Scad11\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /D "SCAD11" /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /Zp1 /MD /W3 /GX /Zi /O2 /I "..\..\Scad11\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "FORUM3DVIEW_EXPORTS" /D "_SECDLL" /D "SCAD11" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "SCAD11"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "SCAD11"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib Schema.lib Profile.lib ClassHelp.lib Result.lib libdb44.lib /nologo /subsystem:windows /dll /machine:I386 /def:"Forum3DView11.def" /out:"../Release11/Forum3DView11.dll" /libpath:"..\..\Scad11\lib"
# SUBTRACT BASE LINK32 /pdb:none /debug
# ADD LINK32 Opengl32.lib glu32.lib Shlwapi.lib D3dx8.lib azip.lib Schema.lib Profile11.lib ClassHelp.lib Result.lib libdb44.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:"Forum3DView11.def" /out:"../Release11/Forum3DView11.dll" /libpath:"..\..\Scad11\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Forum3DView - Win32 Release"
# Name "Forum3DView - Win32 Debug"
# Name "Forum3DView - Win32 Debug11"
# Name "Forum3DView - Win32 Release11"
# Name "Forum3DView - Win32 Release11D"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\BmpSaveDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=..\ColorButton.cpp
# End Source File
# Begin Source File

SOURCE=..\ColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=..\Cutter.cpp
# End Source File
# Begin Source File

SOURCE=..\DepthDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=..\DibGlRenderer.cpp
# End Source File
# Begin Source File

SOURCE=..\DirChangeListener.cpp
# End Source File
# Begin Source File

SOURCE=..\DockFolderWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\ExportDXF.cpp
# End Source File
# Begin Source File

SOURCE=..\FileProc.cpp
# End Source File
# Begin Source File

SOURCE=..\FolderListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\FolderTreeDockingWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Forum3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\Forum3DView.def

!IF  "$(CFG)" == "Forum3DView - Win32 Release"

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug"

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug11"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11D"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forum3DView.rc

!IF  "$(CFG)" == "Forum3DView - Win32 Release"

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug"

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug11"

# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11"

# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11D"

# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forum3DView11.def

!IF  "$(CFG)" == "Forum3DView - Win32 Release"

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug"

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Debug11"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Forum3DView - Win32 Release11D"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\ForumViewGeometry.cpp
# End Source File
# Begin Source File

SOURCE=..\GLDraw.cpp
# End Source File
# Begin Source File

SOURCE=..\GLRenderer.cpp
# End Source File
# Begin Source File

SOURCE=..\IsoViewerFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\IsoViewGeometry.cpp
# End Source File
# Begin Source File

SOURCE=..\MainScadViewerFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\MouseManipulatorWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\Mp4View.cpp
# End Source File
# Begin Source File

SOURCE=.\NumEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\OptionsGeneral.cpp
# End Source File
# Begin Source File

SOURCE=..\OptionsMaterial.cpp
# End Source File
# Begin Source File

SOURCE=..\OptionsRtf.cpp
# End Source File
# Begin Source File

SOURCE=..\PropertiesCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Renderer.cpp
# End Source File
# Begin Source File

SOURCE=..\ResultsDlg.cpp
# ADD CPP /I "Forum3DView"
# End Source File
# Begin Source File

SOURCE=..\Rotate.cpp
# End Source File
# Begin Source File

SOURCE=..\SCAD3DMdlSettings.cpp
# End Source File
# Begin Source File

SOURCE=..\SCADDefProj.cpp
# End Source File
# Begin Source File

SOURCE=..\SCADFolderTreeCtrl.cxx
# End Source File
# Begin Source File

SOURCE=..\SCADTwoPartBtn.cxx
# End Source File
# Begin Source File

SOURCE=..\ScadViewerDoc.cpp
# End Source File
# Begin Source File

SOURCE=..\ScadViewerFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\SCADViewerStatBar.cpp
# End Source File
# Begin Source File

SOURCE=..\ScadViewerView.cpp
# End Source File
# Begin Source File

SOURCE=..\SettingManager.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\SvGluTesselator.cpp
# End Source File
# Begin Source File

SOURCE=.\ThumbCashe.cpp
# End Source File
# Begin Source File

SOURCE=..\View3DBox.cpp
# End Source File
# Begin Source File

SOURCE=..\ViewerOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\ViewGeometry.cpp
# End Source File
# Begin Source File

SOURCE=..\ViewLib.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\3DVector.h
# End Source File
# Begin Source File

SOURCE=..\BmpSaveDlg.h
# End Source File
# Begin Source File

SOURCE=.\CameraDialogBar.h
# End Source File
# Begin Source File

SOURCE=..\ColorButton.h
# End Source File
# Begin Source File

SOURCE=..\ColourPopup.h
# End Source File
# Begin Source File

SOURCE=..\Cutter.h
# End Source File
# Begin Source File

SOURCE=..\DepthDialogBar.h
# End Source File
# Begin Source File

SOURCE=..\DetViewOpts.h
# End Source File
# Begin Source File

SOURCE=..\DibGlRenderer.h
# End Source File
# Begin Source File

SOURCE=..\DirChangeListener.h
# End Source File
# Begin Source File

SOURCE=..\DockFolderWnd.h
# End Source File
# Begin Source File

SOURCE=..\ExportDXF.h
# End Source File
# Begin Source File

SOURCE=..\FileProc.h
# End Source File
# Begin Source File

SOURCE=..\FolderListCtrl.h
# End Source File
# Begin Source File

SOURCE=..\FolderTreeDockingWnd.h
# End Source File
# Begin Source File

SOURCE=.\Forum3DView.h
# End Source File
# Begin Source File

SOURCE=..\ForumViewGeometry.h
# End Source File
# Begin Source File

SOURCE=..\GLDraw.h
# End Source File
# Begin Source File

SOURCE=..\GLRenderer.h
# End Source File
# Begin Source File

SOURCE=..\IsoViewerFrame.h
# End Source File
# Begin Source File

SOURCE=..\IsoViewGeometry.h
# End Source File
# Begin Source File

SOURCE=..\MainScadViewerFrame.h
# End Source File
# Begin Source File

SOURCE=..\model.h
# End Source File
# Begin Source File

SOURCE=..\MouseManipulatorWnd.h
# End Source File
# Begin Source File

SOURCE=..\Mp4View.h
# End Source File
# Begin Source File

SOURCE=.\NumEdit.h
# End Source File
# Begin Source File

SOURCE=..\OptionsGeneral.h
# End Source File
# Begin Source File

SOURCE=..\OptionsMaterial.h
# End Source File
# Begin Source File

SOURCE=..\OptionsRtf.h
# End Source File
# Begin Source File

SOURCE=..\PropertiesCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Renderer.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\ResultsDlg.h
# End Source File
# Begin Source File

SOURCE=..\Rotate.h
# End Source File
# Begin Source File

SOURCE=..\SCAD3DMdlSettings.h
# End Source File
# Begin Source File

SOURCE=..\SCADDefProj.h
# End Source File
# Begin Source File

SOURCE=..\SCADFolderTreeCtrl.hxx
# End Source File
# Begin Source File

SOURCE=..\SCADTwoPartBtn.hxx
# End Source File
# Begin Source File

SOURCE=..\ScadViewerDoc.h
# End Source File
# Begin Source File

SOURCE=..\ScadViewerFrm.h
# End Source File
# Begin Source File

SOURCE=..\SCADViewerStatBar.h
# End Source File
# Begin Source File

SOURCE=..\ScadViewerView.h
# End Source File
# Begin Source File

SOURCE=..\SettingManager.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\SvGluTesselator.h
# End Source File
# Begin Source File

SOURCE=..\SvTesselator.h
# End Source File
# Begin Source File

SOURCE=..\SvTypes.h
# End Source File
# Begin Source File

SOURCE=.\ThumbCashe.h
# End Source File
# Begin Source File

SOURCE=..\View3DBox.h
# End Source File
# Begin Source File

SOURCE=..\ViewerOptions.h
# End Source File
# Begin Source File

SOURCE=..\ViewGeometry.h
# End Source File
# Begin Source File

SOURCE=..\ViewLib.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Cut.cur
# End Source File
# Begin Source File

SOURCE=.\res\CutToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dnarrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Forum3DView.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ForumView.ico
# End Source File
# Begin Source File

SOURCE=.\res\InvCut.cur
# End Source File
# Begin Source File

SOURCE=.\res\LookAround.CUR
# End Source File
# Begin Source File

SOURCE=.\res\main_too.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pan.cur
# End Source File
# Begin Source File

SOURCE=.\res\results_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Rotate.cur
# End Source File
# Begin Source File

SOURCE=.\res\ScadViewer.ico
# End Source File
# Begin Source File

SOURCE=.\res\ScadViewerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Select.cur
# End Source File
# Begin Source File

SOURCE=.\res\ThumbProp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\uparrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WALK.CUR
# End Source File
# Begin Source File

SOURCE=.\res\Zoom.cur
# End Source File
# Begin Source File

SOURCE=.\res\ZoomInOut.cur
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
