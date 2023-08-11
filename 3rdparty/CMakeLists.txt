# get_filename_component(ROOT_PATH "./" ABSOLUTE)
# get_filename_component(3RDFOLDER ${ROOT_PATH} NAME)

set(3RDPARTY_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(GTEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/googletest")
set(3RDPARTY_LIB_PATH "${PROJECT_ROOT_PATH}/lib/${CPU_ARCH}")

MESSAGE(STATUS "3RDPARTY_PATH: ${3RDPARTY_PATH}")
MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
MESSAGE(STATUS "PROJECT_ROOT_PATH: ${PROJECT_ROOT_PATH}")
MESSAGE(STATUS "GTEST_PATH: ${GTEST_PATH}")
MESSAGE(STATUS "3RDPARTY_LIB_PATH: ${3RDPARTY_LIB_PATH}")


if(POLICY CMP0111)
    #gtest warning: Policy CMP0111 is not set: An imported target missing its location property
    cmake_policy(SET CMP0111 OLD) 
endif()

#add_subdirectory(googletest)
add_library(gtest STATIC IMPORTED GLOBAL)
set_target_properties(gtest PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GTEST_PATH}/googletest/include" 
    IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/debug/gtestd.lib"
    IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/release/gtest.lib"
)

add_library(gtest_main STATIC IMPORTED GLOBAL)
set_target_properties(gtest_main PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GTEST_PATH}/googletest/include" 
    IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/debug/gtest_maind.lib"
    IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/release/gtest_main.lib"
)

add_library(gmock STATIC IMPORTED GLOBAL)
set_target_properties(gmock PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GTEST_PATH}/googlemock/include" 
    IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/debug/gmockd.lib"
    IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/release/gmock.lib"
)

add_library(gmock_main STATIC IMPORTED GLOBAL)
set_target_properties(gmock_main PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GTEST_PATH}/googlemock/include" 
    IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/debug/gmock_maind.lib"
    IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/release/gmock_main.lib"
)

#sqlite
add_library(sqlite3 STATIC IMPORTED GLOBAL)
set_target_properties(sqlite3 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${3RDPARTY_PATH}/sqlite3" 
    IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/debug/sqlite3.lib"
    IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/release/sqlite3.lib"
)


#rttr
# add_library(rttr_core SHARED IMPORTED GLOBAL)
# set_target_properties(rttr_core PROPERTIES
#     INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/soci/include" 
#     IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/lib/debug/rttr_core_d.lib"
#     IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/lib/release/rttr_core.lib"
# )


#soci
# add shared lib:
# add_library(soci_core SHARED  IMPORTED GLOBAL)
# set_property(TARGET soci_core PROPERTY IMPORTED_LOCATION "${PROJECT_ROOT_PATH}/bin/x64/Debug/soci_core_4_1.dll")
# set_property(TARGET soci_core PROPERTY IMPORTED_IMPLIB "${3RDPARTY_LIB_PATH}/release/soci_core_4_1.lib") 

add_library(soci_core STATIC  IMPORTED GLOBAL)
set_target_properties(soci_core PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/soci/include" 
    IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/debug/soci_core_4_1.lib"
    IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/release/soci_core_4_1.lib"
)

add_library(soci_sqlite3 STATIC IMPORTED GLOBAL)
set_target_properties(soci_sqlite3 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/soci/include;${3RDPARTY_PATH}/sqlite3" 
    IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/debug/soci_sqlite3_4_1.lib"
    IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/debug/soci_sqlite3_4_1.lib"
)