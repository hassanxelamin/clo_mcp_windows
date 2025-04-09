#--------------------------------------------------------------------------------
# Copyright 2009-2023 CLO Virtual Fashion. All rights reserved.
# Sample CMakeLists.txt file for ExportPlugin

#--------------------------------------------------------------------------------
# Minimum CMake version
cmake_minimum_required(VERSION 3.20)

#--------------------------------------------------------------------------------
# Qt related tools
if (MSVC AND NOT DEFINED ENV{QTDIR})
    message(FATAL_ERROR
        "Please provide 'QTDIR' as an environment variable"
    )
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

cmake_host_system_information(RESULT NUM_LOGICAL_CORES QUERY NUMBER_OF_LOGICAL_CORES)
set(CMAKE_AUTOGEN_PARALLEL ${NUM_LOGICAL_CORES})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#--------------------------------------------------------------------------------
# 3rd party libraries
if (MSVC)
    # Set Qt5_DIR for find_package, although QTDIR is used directly for paths below
    set(Qt5_DIR $ENV{QTDIR}/lib/cmake/Qt5) 
    set(CMAKE_PROGRAM_PATH $ENV{QTDIR}/bin)
    
    # link_directories($ENV{QTDIR}/lib) # Not needed when providing full paths

    # Explicitly set Qt import libraries # This block is unused now
    # set(Qt5_LIBRARIES
    #     $ENV{QTDIR}/lib/Qt5Core.lib
    #     $ENV{QTDIR}/lib/Qt5Widgets.lib
    #     $ENV{QTDIR}/lib/Qt5Gui.lib
    # )
endif()

# Find Qt packages
# Set the directory where Qt5 is installed
# You might need to adjust this path based on your system
# set(Qt5_DIR "C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5") # No longer needed if passed via command line

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

# Debug messages (optional, remove once working)
# message("Qt5_FOUND: ${Qt5_FOUND}")
# message("Qt5_DIR: ${Qt5_DIR}")
# message("Qt5Core_LIBRARIES: ${Qt5Core_LIBRARIES}") # Output showed: Qt5::Core
# message("Qt5Widgets_LIBRARIES: ${Qt5Widgets_LIBRARIES}") # Output showed: Qt5::Widgets
# message("Qt5Gui_LIBRARIES: ${Qt5Gui_LIBRARIES}") # Output showed: Qt5::Gui

#--------------------------------------------------------------------------------
# Target definitions
message("\n>> Copyright 2009-2023 CLO Virtual Fashion. All rights reserved.")
message("\n>> Configuring Sample Project for ExportPlugin\n")

project(
    ExportPlugin
    DESCRIPTION "Sample Export Plugin for CLO"
    VERSION 7.1.194
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} SHARED "")

#--------------------------------------------------------------------------------
# Compiler settings
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

#--------------------------------------------------------------------------------
# Runtime library options
if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
    )
endif()

#--------------------------------------------------------------------------------
# Preprocessor definitions
if(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        CLO_API_INTERFACE_STATIC_BUILD
    )
elseif(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        UNICODE
        _WINDOWS
        _USRDLL
        BOMAPIDLL_EXPORTS
    )
endif()

#--------------------------------------------------------------------------------
# macOS specific settings
if(APPLE)
    # Deployment target
    set(CMAKE_OSX_DEPLOYMENT_TARGET 12.0) # Monterey
    message("-- macOS deployment target: ${CMAKE_OSX_DEPLOYMENT_TARGET}")
    # Target architectures
    if ("${CMAKE_OSX_ARCHITECTURES}" STREQUAL "")
        execute_process(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE osx_architecture)
        set(CMAKE_OSX_ARCHITECTURES ${osx_architecture})
    elseif( NOT ((${CMAKE_OSX_ARCHITECTURES} MATCHES "x86_64") OR (${CMAKE_OSX_ARCHITECTURES} MATCHES "arm64")) )
        message(FATAL_ERROR "Target architecture not supported: ${CMAKE_OSX_ARCHITECTURES}")
    endif()
    message("-- Target macOS architecture (${PROJECT_NAME}): ${CMAKE_OSX_ARCHITECTURES}")
endif()

#--------------------------------------------------------------------------------
# Source
if (MSVC)
    target_sources(${PROJECT_NAME} PRIVATE
        dllmain.cpp
    )
endif()

target_sources(${PROJECT_NAME} PRIVATE
    ExportPlugin.cpp
    ExportPlugin.h
)

#--------------------------------------------------------------------------------
# CLOAPIInterface
find_library(CLO_API_INTERFACE NAMES CLOAPIInterface PATHS ../../CLOAPIInterface/Lib REQUIRED)

if (MSVC)
    find_file(CLO_API_INTERFACE_DLL NAMES CLOAPIInterface.dll PATHS ../../CLOAPIInterface/Lib REQUIRED)
    # list(APPEND STATIC_LIBRARIES ${CLO_API_INTERFACE}) # No longer needed, link CLO_API_INTERFACE directly
    list(APPEND SHARED_LIBRARIES ${CLO_API_INTERFACE_DLL})
elseif (APPLE)
    list(APPEND SHARED_LIBRARIES ${CLO_API_INTERFACE})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ../../CLOAPIInterface
    ${Qt5Widgets_INCLUDE_DIRS}
)

#--------------------------------------------------------------------------------
# Linking
if (MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "${CLO_API_INTERFACE}" # Use the variable found by find_library
        # Explicitly link the .lib files using HARDCODED ABSOLUTE PATHS
        "C:/Qt/5.15.2/msvc2019_64/lib/Qt5Core.lib"
        "C:/Qt/5.15.2/msvc2019_64/lib/Qt5Widgets.lib"
        "C:/Qt/5.15.2/msvc2019_64/lib/Qt5Gui.lib"
    )
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SHARED_LIBRARIES}
    )
endif()

#--------------------------------------------------------------------------------
# Post build events

# [macOS] Ensure to adjust install names to use the same libraries as the host app
if (APPLE)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_INSTALL_NAME_TOOL} -change
            \"@rpath/libCLOAPIInterface.dylib\"
            \"@executable_path/../Frameworks/libCLOAPIInterface.dylib\"
            "lib${PROJECT_NAME}.dylib"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()