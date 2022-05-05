#ifndef OPENGLIMGUITEMPLATE_APPLICATION_HPP
#define OPENGLIMGUITEMPLATE_APPLICATION_HPP

#include "logging.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/vec4.hpp>

// TODO: GL event handling
// TODO: Window resize handling

struct application_data
{
    std::string title = "OpenGL ImGui Template";
    uint32_t width = 640;
    uint32_t height = 480;
};

class application
{
public:
    application(application_data application_props);
    ~application();
    void run();

    virtual void on_update() = 0;
private:
    application_data m_props;
    GLFWwindow* m_window;
};


#endif //OPENGLIMGUITEMPLATE_APPLICATION_HPP
