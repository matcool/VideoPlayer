cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

project(VideoPlayer VERSION 1.0.0)

file(GLOB SOURCES
	src/*.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

if (PROJECT_IS_TOP_LEVEL) 
    target_compile_definitions(${PROJECT_NAME} PRIVATE _VIDEO_PLAYER_EXPORTING)
endif()

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} $ENV{GEODE_SDK}/build)

CPMAddPackage("gh:phoboslab/pl_mpeg#e11f014")

target_include_directories(${PROJECT_NAME} PUBLIC ${pl_mpeg_SOURCE_DIR})

setup_geode_mod(${PROJECT_NAME})
