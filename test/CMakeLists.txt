cmake_minimum_required(VERSION 3.10)

# Set the project name
set(PROJECT unit_tests)
# project (test)
MESSAGE(STATUS "test GTEST_PATH: ${GTEST_PATH}")

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

