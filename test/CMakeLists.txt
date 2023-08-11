cmake_minimum_required(VERSION 3.10)

# Set the project name
set(PROJECT unit_tests)

MESSAGE(STATUS "test GTEST_PATH: ${GTEST_PATH}") #不能引用3rdparty中定义的变量

#############################################
# Unit tests

file(GLOB SOURCE *.cpp)
file(GLOB HEADER *.h)

add_executable(${PROJECT} ${SOURCE} ${HEADER})

target_link_libraries(${PROJECT}
    gtest 
    gtest_main
    sqlite3
)

source_group("src" FILES ${SOURCE})
source_group("headers" FILES ${HEADER})

