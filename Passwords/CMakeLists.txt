cmake_minimum_required(VERSION 3.10)

project(Passwords)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/errorvalues.cpp
    src/encrypt.cpp
    src/libpasswords.cpp
    src/libpasswordsfilemanager.cpp
    src/password.cpp
    src/passwordfilemanager.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

enable_testing()

set(TEST_SOURCES
    tests/test.cpp
    tests/testmain.cpp
)

set(TEST_SOURCES ${TEST_SOURCES} 
    src/errorvalues.cpp
    src/encrypt.cpp
    src/libpasswords.cpp
    src/libpasswordsfilemanager.cpp
    src/password.cpp
    src/passwordfilemanager.cpp
)

add_executable(Tests ${TEST_SOURCES})

target_include_directories(Tests PUBLIC include)

target_link_libraries(Tests PRIVATE gtest)

add_test(NAME Tests COMMAND Tests)