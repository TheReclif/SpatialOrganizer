cmake_minimum_required(VERSION 3.16)

project(SpatialOrganizer VERSION 1.0.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_TESTS "Build tests" OFF)

find_package(GTest CONFIG REQUIRED)

add_library(SpatialOrganizer
	"src/SpatialOrganizer.cpp"
)

target_link_libraries(SpatialOrganizer PUBLIC GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

target_include_directories(SpatialOrganizer PUBLIC include)

if (BUILD_TESTS)
	add_subdirectory(tests)
endif()