add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glm)

# Setup a test project with gtest dependencies
option(BUILD_TESTS "Build the tests" OFF)
if(BUILD_TESTS)
    add_subdirectory(vendor/googletest)
endif()

find_package(glm REQUIRED)

include(./cmake/glad.cmake)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

#configure_file(./vendor/imgui/backends/imgui_impl_glfw.cpp ./bindings/imgui_impl_glfw.cpp COPYONLY)
#configure_file(./vendor/imgui/backends/imgui_impl_glfw.h ./bindings/imgui_impl_glfw.h COPYONLY)
#configure_file(./vendor/imgui/backends/imgui_impl_opengl3.cpp ./bindings/imgui_impl_opengl3.cpp COPYONLY)
#configure_file(./vendor/imgui/backends/imgui_impl_opengl3.h ./bindings/imgui_impl_opengl3.h COPYONLY)