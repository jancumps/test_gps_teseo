cmake_minimum_required(VERSION 3.28)

project(test_teseo_nmea C CXX ASM)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts -fcommon")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-allow-multiple-definition")

if(DEFINED PATH_TO_LIBS)
set(SOURCE_PATH ${PATH_TO_LIBS})
else()
set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/source)
endif()
message("library source path=" ${SOURCE_PATH})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${CMAKE_PROJECT_NAME})
target_sources(${CMAKE_PROJECT_NAME}
        PUBLIC
        ${SOURCE_PATH}/gps_teseo_lib/teseo/teseo.cpp
        ${SOURCE_PATH}/gps_nmea_lib/nmea/nmea.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/gps_nmea_lib/test_gps_nmea_lib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/gps_teseo_lib/test_gps_teseo_lib.cpp
        ${SOURCE_PATH}/callbackmanager/test/callbackmanager_test.cpp
)
target_sources(${CMAKE_PROJECT_NAME}
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        ${SOURCE_PATH}/callbackmanager/callbackmanager.cpp
        ${SOURCE_PATH}/gps_teseo_lib/teseo/teseo_iface.cpp
        ${SOURCE_PATH}/gps_nmea_lib/nmea/nmea_iface.cpp
)

target_link_libraries( ${CMAKE_PROJECT_NAME}
        GTest::gtest_main
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})