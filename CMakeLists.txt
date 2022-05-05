##### cmake -G "Visual Studio 16 2019" -A x64 ..
##### cmake -G "Visual Studio 17 2022" -A x64 ..
cmake_minimum_required(VERSION 3.22)

# Project settings
project(
        OpenGLImGuiTemplate
        VERSION 1.0.0
        DESCRIPTION ""
        LANGUAGES CXX
)

# CMake scripts
include(cmake/project_defaults.cmake) # Default project settings
include(cmake/project_dependencies.cmake) # Project dependencies

# TODO:
# Glad & Glfw
# imgui

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()



















## Set flags
#set(CMAKE_CXX_FLAGS_DEBUG "/MDd")
#set(CMAKE_CXX_FLAGS_RELEASE "/MD")

## Set compiler definitions and options
#add_definitions(-D _AFXDLL)
#add_definitions(-D WIN32)
#add_definitions(-D WIN64)
#add_definitions(-D _LIB)
#add_definitions(-D _UNICODE)
#add_definitions(-D UNICODE)

#set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
#        $<$<CONFIG:Debug>:_DEBUG>
#        $<$<CONFIG:Release>:NDEBUG>
#        $<$<CONFIG:RelWithDebInfo>:NDEBUG>
#        $<$<CONFIG:MinSizeRel>:NDEBUG>
#        )

## Allow parallel compilation of projects
#add_compile_options(/MP)
#add_compile_options(/Zc:wchar_t)