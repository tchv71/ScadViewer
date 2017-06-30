cmake_minimum_required(VERSION 2.8.11)

project(ScadViewer)


include_directories(
    .
	Scad21/Include
)

link_directories(
	.
	Forum3DView
	Scad21/Lib/32
	"Berkeley DB 4.4.20/lib/32"
)

add_definitions(-D_AFXDLL -DSCAD21 -D_UNICODE -DUNICODE)
set(CMAKE_MFC_FLAG 2)

add_subdirectory(Forum3DView)

set(CXX_SRCS
	ScadViewer.cpp
)

add_executable(ScfExplorer WIN32 ${CXX_SRCS} ScadViewer.rc)
#set_target_properties(ScfExplorer PROPERTIES  LINK_FLAGS "/NODEFAULTLIB ")

target_link_libraries(ScfExplorer
	azip
	SCADAPIX
	libdb62
	Version
	Forum3dView21
	)

set (AFX_DLLS
	libcmt
	Kernel32
	User32
	Gdi32
	MSImg32
	ComDlg32
	WinSpool
	AdvAPI32
	Shell32
	ComCtl32
	ShLwApi
	Uuid
	atls
	Ole32
	OleAut32
	oldnames
	WS2_32
	MsWSock
	OleAcc
	comsuppw
	GdiPlus
	Imm32
	WinMM
	MsXml2
	OleDlg
	Urlmon
)

set_target_properties(ScfExplorer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_custom_command(
  TARGET ScfExplorer
  POST_BUILD COMMAND
    mt.exe -manifest \"${CMAKE_CURRENT_SOURCE_DIR}/ScadViewer32.manifest\"  -outputresource:\"${PROJECT_BINARY_DIR}/bin/${CMAKE_CFG_INTDIR}/ScfExplorer.exe\";#2
  COMMENT
    "Appending manifest for MSVCRT90 dependency."
)

# Adds logic to INSTALL.vcproj to copy math.dll to the destination directory
install (TARGETS ScfExplorer
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)

