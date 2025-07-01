cmake_minimum_required(VERSION 3.28)

project(test_teseo_nmea C CXX ASM)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts -fcommon")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-allow-multiple-definition")

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG HEAD
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if(DEFINED PATH_TO_LIBS)

set(callbackmanager_PATH ${PATH_TO_LIBS}/callbackmanager-src)
set(gps_teseo_lib_PATH ${PATH_TO_LIBS}/gps_teseo_lib-src)
set(gps_nmea_lib_PATH ${PATH_TO_LIBS}/gps_nmea_lib-src)

else()

FetchContent_Declare(callbackmanager
  GIT_REPOSITORY "https://github.com/jancumps/callbackmanager.git"
  GIT_TAG "origin/main"
  SOURCE_SUBDIR =
)
FetchContent_MakeAvailable(callbackmanager)

FetchContent_Declare(gps_teseo_lib
  GIT_REPOSITORY "https://github.com/jancumps/gps_teseo_lib.git"
  GIT_TAG "origin/main"
  SOURCE_SUBDIR =
)
FetchContent_MakeAvailable(gps_teseo_lib)

FetchContent_Declare(gps_nmea_lib
  GIT_REPOSITORY "https://github.com/jancumps/gps_nmea_lib.git"
  GIT_TAG "origin/main"
  SOURCE_SUBDIR =
)
FetchContent_MakeAvailable(gps_nmea_lib)

set(callbackmanager_PATH ${callbackmanager_SOURCE_DIR})
set(gps_teseo_lib_PATH ${gps_teseo_lib_SOURCE_DIR})
set(gps_nmea_lib_PATH ${gps_nmea_lib_SOURCE_DIR})

endif()

message("callbackmanager source path: " ${callbackmanager_PATH})
message("gps_teseo_lib source path: " ${gps_teseo_lib_PATH})
message("gps_nmea_lib source path: " ${gps_nmea_lib_PATH})

enable_testing()

add_executable(${CMAKE_PROJECT_NAME})
target_sources(${CMAKE_PROJECT_NAME}
        PUBLIC
        ${gps_teseo_lib_PATH}/teseo/teseo.cpp
        ${gps_nmea_lib_PATH}/nmea/nmea.cpp
        ${gps_nmea_lib_PATH}/test/test_gps_nmea_lib.cpp
        ${gps_teseo_lib_PATH}/test/test_gps_teseo_lib.cpp
        ${callbackmanager_PATH}/test/callbackmanager_test.cpp
)
target_sources(${CMAKE_PROJECT_NAME}
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        ${callbackmanager_PATH}/callbackmanager.cpp
        ${gps_teseo_lib_PATH}/teseo/teseo_iface.cpp
        ${gps_nmea_lib_PATH}/nmea/nmea_iface.cpp
)

target_link_libraries( ${CMAKE_PROJECT_NAME}
        GTest::gtest_main
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})