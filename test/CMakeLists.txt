project(cmpe_130)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicTests
        tests.cpp)

add_subdirectory(googletest)

target_link_libraries(runBasicTests gtest gtest_main)
#target_link_libraries(runBasicTests library)