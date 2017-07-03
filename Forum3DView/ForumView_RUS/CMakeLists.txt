cmake_minimum_required(VERSION 2.8.11)

include_directories(
    .
)

if(WIN32)
add_library(ForumView21_RUS SHARED ForumView_Rus.rc)
set_target_properties(ForumView21_RUS PROPERTIES LINK_FLAGS "/NOENTRY")
SET_TARGET_PROPERTIES (ForumView21_RUS PROPERTIES LINKER_LANGUAGE "CXX")
set_target_properties(ForumView21_RUS PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set_property(TARGET ForumView21_RUS PROPERTY FOLDER "libraries")
# Properties->General->Output Directory
install(TARGETS ForumView21_RUS
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install
	)
endif(WIN32)
