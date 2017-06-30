cmake_minimum_required(VERSION 2.8.11)

include_directories(
    .
)

add_library(ForumView21_ENG SHARED ForumView_Eng.rc)
set_target_properties(ForumView21_ENG PROPERTIES  LINK_FLAGS "/NOENTRY")
set_target_properties (ForumView21_ENG PROPERTIES LINKER_LANGUAGE "CXX")
set_target_properties(ForumView21_ENG PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set_property(TARGET ForumView21_ENG PROPERTY FOLDER "libraries")
# Properties->General->Output Directory
install(TARGETS ForumView21_ENG
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install
	)


