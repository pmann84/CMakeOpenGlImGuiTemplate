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

    virtual void on_update(float ts) = 0;
    virtual void on_ui_render() = 0;

//    virtual void on_error(int error, const char* description) = 0;
    virtual void on_key_press(int key, int scancode, int action, int mods) {}
    virtual void on_window_close() {}
    virtual void on_window_resize(int width, int height) {}
    virtual void on_char_press(unsigned int keycode) {}
    virtual void on_mouse_button(int button, int action, int mods) {}
    virtual void on_scroll(double xOffset, double yOffset) {}
    virtual void on_cursor_pos_changed(double xPos, double yPos) {}

protected:
    application_data m_props;
    GLFWwindow* m_window;

    float m_time_step = 0.0f;
    float m_frame_time = 0.0f;
    float m_last_frame_time = 0.0f;
};


#endif //OPENGLIMGUITEMPLATE_APPLICATION_HPP
