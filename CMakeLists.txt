cmake_minimum_required(VERSION 3.10)
project(pro)

set(PROJECT_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(CPU_ARCH x86)
else()
    set(CPU_ARCH x64)
endif()

message("CMAKE_SIZEOF_VOID_P: ${CMAKE_SIZEOF_VOID_P}")
message("PROJECT_ROOT_PATH: ${PROJECT_ROOT_PATH}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#cmake_policy(SET CMP0111 OLD)

#option(ENABLE_UT "Build unit test projects" OFF)

# 生成编译调试信息
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


if (MSVC)
    add_compile_options(/W3)
    add_compile_definitions(_HAS_STD_BYTE=0)
endif()

#现在代码里的编码都不统一，这里先可以不放开
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options(-DWIN32_LEAN_AND_MEAN)

if(MSVC)
add_definitions(-DNOMINMAX)
endif()

#多核编译
if(MSVC)
OPTION(USE_MP "use multiple" ON)
if(USE_MP)
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP12")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP12")
endif()
endif()


add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(test)
