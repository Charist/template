project(sqlite_pro)
set(PROJECT sqlite3)
add_compile_definitions(
    SQLITE_ENABLE_COLUMN_METADATA
    SQLITE_ENABLE_MATH_FUNCTIONS
)

add_library(${PROJECT} STATIC sqlite3.c)
add_executable(sqlite3_shell shell.c)
target_link_libraries(sqlite3_shell 
    ${PROJECT}
    $<$<PLATFORM_ID:Linux>:pthread>
    $<$<PLATFORM_ID:Linux>:dl>
    $<$<PLATFORM_ID:Linux>:m>
)

#set(PROJECT sqlite3)
#get_filename_component(THIS_ROOT_PATH "./" ABSOLUTE)
#add_library(${PROJECT} STATIC IMPORTED GLOBAL)
#set_target_properties(${PROJECT} PROPERTIES
#    INTERFACE_INCLUDE_DIRECTORIES "${THIS_ROOT_PATH}" 
#    IMPORTED_LOCATION_DEBUG "${THIS_ROOT_PATH}/sqlite3.lib"
#    IMPORTED_LOCATION_RELEASE "${THIS_ROOT_PATH}/sqlite3.lib"
#)
