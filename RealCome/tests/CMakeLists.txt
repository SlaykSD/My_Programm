cmake_minimum_required(VERSION 3.17)

set(REPO ~Git_C)

project(Test)

project(Example)

include(CTest)
enable_testing()

set(gtest_disable_pthreads on) #needed in MinGW
include(D:/Git_C/My_Programm/Lab2withTest-master/DownloadProject/DownloadProject.cmake)
download_project(
        PROJ                googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             master
        UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

set(test_SRCS gtest.cpp)
add_executable(runUnitTests gtest.cpp ${test_SRCS})
target_link_libraries(runUnitTests gtest gmock core)