# Microsoft Developer Studio Project File - Name="MsClass" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MsClass - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MsClass.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MsClass.mak" CFG="MsClass - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MsClass - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MsClass - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ToolLibs/MsClass", AJEAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MsClass - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MSCLASS_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Zp1 /MD /W3 /GR /GX /O2 /I "include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "__MSCLASS_EXPORTS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\ForumView\Release/MsClass.dll"

!ELSEIF  "$(CFG)" == "MsClass - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\ForumView\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MSCLASS_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /w /W0 /Gm /GR /GX /ZI /Od /I "include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "__MSCLASS_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /profile /debug /machine:I386

!ENDIF 

# Begin Target

# Name "MsClass - Win32 Release"
# Name "MsClass - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Class"

# PROP Default_Filter ""
# Begin Group "Interpol"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Class\Interp\Interpol.cpp
# End Source File
# End Group
# Begin Group "Exit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Class\Exit\Crash.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Exit\Crashmsg.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Exit\Exit_msg.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Exit\Math_err.cpp
# End Source File
# End Group
# Begin Group "Convert"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Class\Convert\Bit.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Convert\Charconv.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Convert\Convert.cpp
# End Source File
# End Group
# Begin Group "File"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Class\File\Copyfile.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\Discfree.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\file_mem.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\filebase.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\Filepath.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\fileprnt.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\filetext.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\Filetime.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\filework.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\Fontsize.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\Frmtslct.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\File\Txtwrite.cpp
# End Source File
# End Group
# Begin Group "Gauss"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Class\Gauss\gauss.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Gauss\gaustape.cpp
# End Source File
# End Group
# Begin Group "List"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Class\List\Listtext.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\List\Textlist.cpp
# End Source File
# End Group
# Begin Group "Matrize"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Class\Matr\det3x3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Matr\matr_cos.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Matr\multmatr.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Matr\multvect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Matr\normvect.cpp
# End Source File
# End Group
# Begin Group "Message"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Class\Message\Infcode.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Message\inform.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Message\Message.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Message\Rc_text.cpp
# End Source File
# End Group
# Begin Group "String"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Class\String\Index.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\String\paramtxt.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\String\Paramvlu.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\String\Separate.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\String\Str_out.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\String\Stringup.cpp
# End Source File
# End Group
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Class\Tools\Memory.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Tools\Memvect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Tools\Poly_3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Tools\polynom.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Tools\Printfr.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Tools\Space.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Class\Tools\Toup_rus.cpp
# End Source File
# End Group
# Begin Group "Debug"

# PROP Default_Filter ""
# End Group
# Begin Group "BaseClass"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SOURCE\Class\BaseClass\baseadd.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Class\BaseClass\basechange.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Class\BaseClass\baseclass.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Class\BaseClass\baseclear.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Class\BaseClass\basecompress.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Class\BaseClass\basedelete.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Class\BaseClass\basefile.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Class\BaseClass\basereadwrite.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Class\BaseClass\objectlist.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Class\BaseClass\objectstring.cpp
# End Source File
# End Group
# End Group
# Begin Group "Schema"

# PROP Default_Filter ""
# Begin Group "Bound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Schema\Bound\Add_list.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Bound\bound.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Bound\fund.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Bound\Get_list.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Bound\Joint_fe.cpp
# End Source File
# End Group
# Begin Group "Add"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Schema\Add\Add_incl.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Add\add_schm.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Add\Addcontr.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Add\Addorder.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Add\addvolum.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Add\Del_node.cpp
# End Source File
# End Group
# Begin Group "Insert"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Schema\Insert\insert.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Insert\Schm_ins.cpp
# End Source File
# End Group
# Begin Group "Load"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Schema\Load\Add_load.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Load\dataload.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Load\del_load.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Load\force_eq.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Schema\LOAD\ForumForce.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Load\loadlist.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Load\loadread.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Load\loadwrt.cpp
# End Source File
# End Group
# Begin Group "Rigid"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Schema\Rigid\compname.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Rigid\data_rgd.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Rigid\rgd_name.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Rigid\Rgd_type.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Rigid\Rgdcompr.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Rigid\Rgdcorne.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Rigid\schm_rgd.cpp
# End Source File
# End Group
# Begin Group "ToolsS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Schema\Tools\Elemtype.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\filltree.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\getmodif.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Schema\TOOLS\scadnode.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\schema.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\schm_mk.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\schmcomp.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\Schmcoor.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\schmdelt.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\schmfile.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\schminit.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\Schmparm.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\schmread.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\schmwrt.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\schmzero.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\Settpsys.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Tools\unischem.cpp
# End Source File
# End Group
# Begin Group "Steel"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Schema\Steel\steel.cpp
# End Source File
# End Group
# Begin Group "LookBody"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\bodybody.cpp
# End Source File
# Begin Source File

SOURCE=.\SOURCE\Schema\LOOKBODY\cont_plt.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\direct.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\elembody.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\linebody.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\look_eq.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\Look_rod.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\lookbody.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\lookinto.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\lookproc.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\pnctbody.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\prof_inf.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\profelem.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\profnode.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Schema\Lookbody\profplat.cpp
# End Source File
# End Group
# End Group
# Begin Group "Profile"

# PROP Default_Filter ""
# Begin Group "User"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Profile\User\ltr_tabl.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\profuser.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\rodsc199.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\Rodsec00.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\Rodsec01.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\Rodsec02.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\Rodsec03.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\Rodsec04.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\Rodsec05.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\Rodsec06.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\Rodsec07.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\User\rodsec08.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Source\Profile\AddElast.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\prfstrrd.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\profcode.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\proffull.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\profgraf.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\profile.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\profinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\profmask.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\profname.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Profile\sectname.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\INCLUDE\amplitud.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\BASECLASS.HPP
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\BIT.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\body.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Bound.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\calcdata.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\classwin.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\CONVERT.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Crash.h
# End Source File
# Begin Source File

SOURCE=.\Include\data_rgd.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Dataload.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\DefClass.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\drctmatr.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\EDIT_WRT.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\FE_66.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\FE_BASE.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Fe_data.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\fe_form.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Fe_head.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\fe_lr_db.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\FE_LR_DR.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\fe_lr_i.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\FE_OS.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\fe_os_i.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\FE_PL_MD.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\FE_PLATE.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\fe_plt_i.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Fe_rod.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\fe_vol_i.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\fe_volum.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\File_mem.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\filebase.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\fileprnt.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\filescad.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Filetext.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\filework.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\ForumForce.hpp
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Fund.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\GAUSS.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\inform.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Inp_doc.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Inp_rgd.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Insert.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\lit_func.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\LITERA.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\LOADCOMB.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Memclass.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Memvect.hpp
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Message.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\ObjectList.hpp
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\ObjectString.hpp
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\PROC_RSU.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Proffull.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Profile.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\pvs.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Rc_text.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\rgd_name.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\RGD_OSD.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\rgd_pl.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\rgd_pl_a.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\RGD_PL_N.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\RGD_ROD.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\RGD_RODN.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\RGD_VL_A.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\RGD_VOL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\S_DEFS2.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\S_DEFS4.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\S_DEFS6.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\S_DEFS8.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\S_gauss.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\S_RSU.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\S_STABIL.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\S_super.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\SCADNODE.HPP
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\schema.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\SCHM_DEF.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\sectname.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\SG_DYN1.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\SPACE.H
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\Steel.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\STEPDATA.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\STRINGUP.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\SYSUNITS.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\TABLLOAD.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\TYPEDATA.H
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\unischem.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
