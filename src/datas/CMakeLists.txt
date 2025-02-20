set(PROJECT Datas)

message("PROJECT_ROOT_PATH: ${PROJECT_ROOT_PATH}")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")


file(GLOB SOURCE *.cpp)
file(GLOB HEADER *.h)

file(GLOB MODEL_SOURCE model/*.cpp)
file(GLOB MODEL_HEADER model/*.h)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${PROJECT_ROOT_PATH}/3rdparty/spdlog/include"
)


source_group("src" FILES ${SOURCE})
source_group("headers" FILES ${HEADER})

source_group("src/model" FILES ${MODEL_SOURCE})
source_group("headers/model" FILES ${MODEL_HEADER})

add_compile_options(-DEXPORT_DBMANAGER_LIB)

add_executable(${PROJECT} ${SOURCE} ${MODEL_SOURCE} 
                ${HEADER} ${MODEL_HEADER})

# add_library(${PROJECT} SHARED ${SOURCE} ${MODEL_SOURCE} 
#                 ${HEADER} ${MODEL_HEADER})
                
target_link_libraries(${PROJECT} 
    soci_core 
    soci_sqlite3
    # sqlite3
    rttr_core
    )

set_property(TARGET ${PROJECT} PROPERTY FOLDER "common")
# set_property(TARGET ${PROJECT} PROPERTY FOLDER ${THIS_FOLDER})
set_target_properties(${PROJECT} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}
)
