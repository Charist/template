set(PROJECT Datas)

message("PROJECT_ROOT_PATH: ${PROJECT_ROOT_PATH}")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")


file(GLOB SOURCE *.cpp)
file(GLOB HEADER *.h)

include_directories(
    # "${PROJECT_ROOT_PATH}/3rdparty/sqlite3"
)


source_group("src" FILES ${SOURCE})
source_group("headers" FILES ${HEADER})

add_compile_options(-DEXPORT_DBMANAGER_LIB)
# add_library(${PROJECT} SHARED ${SOURCE} ${HEADER})

add_executable(${PROJECT} ${SOURCE} ${HEADER})

target_link_libraries(${PROJECT} 
    soci_core 
    soci_sqlite3)

set_property(TARGET ${PROJECT} PROPERTY FOLDER "common")
# set_property(TARGET ${PROJECT} PROPERTY FOLDER ${THIS_FOLDER})
set_target_properties(${PROJECT} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}
)