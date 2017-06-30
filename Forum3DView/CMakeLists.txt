cmake_minimum_required(VERSION 2.8.11)

include_directories(
    .
	../Scad21/Include
	"../Berkeley DB 4.4.20/include"
)

link_directories(
	.
	../Scad21/Lib/32
	"../Berkeley DB 4.4.20/lib/32"
)

add_definitions(-D_AFXDLL -DSCAD21 -DFORUM3DVIEW_EXPORTS -D_UNICODE -DUNICODE)
set(CMAKE_MFC_FLAG 2)

add_subdirectory(RTree)
add_subdirectory(ForumView_ENG)
add_subdirectory(ForumView_RUS)

set(CXX_SRCS
	BmpSaveDlg.cpp
	CameraDialogBar.cpp
	ColorButton.cpp
	ColourPopup.cpp
	Cutter.cpp
	DelimDialog.cpp
	DepthDialogBar.cpp
	DibGlRenderer.cpp
	DirChangeListener.cpp
	DockFolderWnd.cpp
	ExportDXF.cpp
	FileProc.cpp
	FolderListCtrl.cpp
	FolderTreeDockingWnd.cpp
	Forum3DView.cpp
	ForumViewGeometry.cpp
	GLDraw.cpp
	GLRenderer.cpp
	HSV2RGB.cpp
	IsoViewerFrame.cpp
	IsoViewGeometry.cpp
	MainScadViewerFrame.cpp
	MouseManipulatorWnd.cpp
	NumEdit.cpp
	OptionsGeneral.cpp
	OptionsMaterial.cpp
	optionsrtf.cpp
	Renderer.cpp
	ResultsDialogBar.cpp
	ResultsDlg.cpp
	Rotate.cpp
	SaveBmp.cpp
	SCAD3DMdlSettings.cpp
	SCADDefProj.cpp
	ScadViewerDoc.cpp
	ScadViewerFrm.cpp
	SCADViewerStatBar.cpp
	ScadViewerView.cpp
	ScaleDialog.cpp
	ScaleDlg.cpp
	ScalePane.cpp
	SettingManager.cpp
	SvGluTesselator.cpp
	View3DBox.cpp
	ViewerOptions.cpp
	ViewGeometry.cpp
	ViewLib.cpp
	GridSrc/GridCell.cpp
	GridSrc/GridCellBase.cpp
	GridSrc/GridCellCheck.cpp
	GridSrc/GridCtrl.cpp
	GridSrc/GridDropTarget.cpp
	GridSrc/InPlaceEdit.cpp
	GridSrc/TitleTip.cpp
)

MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    SET(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
    SET(Sources ${${SourcesVar}})

    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Zp1 /Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
    SET_SOURCE_FILES_PROPERTIES(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Zp1 /Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")  
    # Add precompiled header to SourcesVar
    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" CXX_SRCS)

if(WIN32)
    # Define the resource files
    set ( RC_SRCS
        Forum3dView.rc
    )
endif(WIN32)

add_library(Forum3dView21 SHARED  ThumbCashe.cpp ${CXX_SRCS} ${RC_SRCS})

target_link_libraries(Forum3dView21
	Opengl32
	glu32
	Shlwapi
	azip
	SCADAPIX
	libdb62
	sprfem
	SprResult
	SprTools
	RTree)

set_target_properties(Forum3dView21 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
#set_target_properties(Forum3dView21 PROPERTIES  LINK_FLAGS "/DEF:${CMAKE_SOURCE_DIR}/Forum3DView/Forum3DView21.def")

set_property(TARGET Forum3dView21 PROPERTY FOLDER "libraries")
# Properties->General->Output Directory
install(TARGETS Forum3dView21
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install
	)
