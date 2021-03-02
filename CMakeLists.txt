cmake_minimum_required(VERSION 3.16)

project(SpatialOrganizer VERSION 1.0.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_TESTS "Build tests" false)

add_library(SpatialOrganizer
	"src/SpatialMap.cpp"

	"include/SpatialMap.hpp"
	"include/ConcurrentSpatialMap.hpp"
	"include/ConcurrentHashMap.hpp"
	"include/ConcurrentList.hpp"
)

target_include_directories(SpatialOrganizer PUBLIC include)

if (BUILD_TESTS)
	add_subdirectory(tests)
endif()