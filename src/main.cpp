#include "application.hpp"

//static void error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Error: %s\n", description);
//}
//
//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//    fprintf(stdout, "Key: %i, scancode: %i, action: %i\n", key, scancode, action);
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GLFW_TRUE);
//}
//
//static void window_close_callback(GLFWwindow* window)
//{
//    fprintf(stdout, "Window closing...\n");
//}

class my_app : public application
{
public:
    my_app(application_data props) : application(props)
    {
    }

    virtual void on_update() override
    {
    }
};

int main()
{
    application_data props;
    my_app app(props);
    app.run();

    return 0;
}
