set(glad_PATH ${CMAKE_SOURCE_DIR}/vendor/glad)

add_library(glad ${glad_PATH}/include/glad/glad.h ${glad_PATH}/include/KHR/khrplatform.h  ${glad_PATH}/src/glad.c)
target_include_directories(glad PUBLIC ${glad_PATH}/include/)