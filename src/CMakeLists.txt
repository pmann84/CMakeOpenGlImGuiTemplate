set(APP_PROJECT_NAME "${PROJECT_NAME}_App")
message(STATUS "APP_PROJECT_NAME: ${APP_PROJECT_NAME}")

add_executable(${APP_PROJECT_NAME} main.cpp)

target_link_libraries(${APP_PROJECT_NAME}
        PRIVATE spdlog::spdlog
        PRIVATE glm
)

## Library

## Header only
#target_link_libraries(example_header_only PRIVATE spdlog::spdlog_header_only)

#target_include_directories(OpenGLImGuiTemplate PUBLIC ${GLFW_INCLUDE_DIRS})
#target_link_libraries(OpenGLImGuiTemplate PUBLIC ${GLFW_LINK_DIRS})
