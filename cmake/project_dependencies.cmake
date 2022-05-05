add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glm)

# Setup a test project with gtest dependencies
option(BUILD_TESTS "Build the tests" OFF)
if(BUILD_TESTS)
    add_subdirectory(vendor/googletest)
endif()

find_package(glm REQUIRED)

#set(GLFW_BUILD_DOCS OFF)
#set(GLFW_INCLUDE_DIRS ./vendor/glfw/include)
#set(GLFW_LINK_DIRS ./vendor/glfw/src/$<CONFIG>)
#
#configure_file(./vendor/imgui/backends/imgui_impl_glfw.cpp ./bindings/imgui_impl_glfw.cpp COPYONLY)
#configure_file(./vendor/imgui/backends/imgui_impl_glfw.h ./bindings/imgui_impl_glfw.h COPYONLY)
#configure_file(./vendor/imgui/backends/imgui_impl_opengl3.cpp ./bindings/imgui_impl_opengl3.cpp COPYONLY)
#configure_file(./vendor/imgui/backends/imgui_impl_opengl3.h ./bindings/imgui_impl_opengl3.h COPYONLY)