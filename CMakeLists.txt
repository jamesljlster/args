cmake_minimum_required(VERSION 2.8)

# Set variables
set(PROJECT_NAME args)

# Environment variables
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation directory")
set(BUILD_TEST OFF CACHE BOOL "Enable building test")

# Set project
project(${PROJECT_NAME} ${PROJECT_LANGUAGE})

# Include subdirectory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
if(${BUILD_TEST})
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

