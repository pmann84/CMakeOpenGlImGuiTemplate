#include "application.hpp"

static void error_callback(int error, const char* description)
{
    logging::error("GLFW Error ({0}): {1}", error, description);
}

application::application(application_data application_props) : m_props(application_props)
{
    logging::init(spdlog::level::debug);

    if (!glfwInit())
    {
        // Initialization failed
        logging::critical("GLFW Initialisation failed.");
        return;
    }

    glfwSetErrorCallback(error_callback);

    m_window = glfwCreateWindow(m_props.width, m_props.height, m_props.title.c_str(), NULL, NULL);
    if (!m_window)
    {
        // Window or context creation failed
        logging::critical("GLFW Window creation failed.");
        glfwTerminate();
        return;
    }

    glfwSetWindowUserPointer(m_window, this);

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        application& app = *(application*)glfwGetWindowUserPointer(window);
        // TODO: Consider converting this into something more sane?
        app.on_key_press(key, scancode, action, mods);
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window){
        application& app = *(application*)glfwGetWindowUserPointer(window);
        app.on_window_close();
    });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height){
        application& app = *(application*)glfwGetWindowUserPointer(window);
        app.m_props.width = width;
        app.m_props.height = height;
        app.on_window_resize(width, height);
    });

    glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
    {
        application& app = *(application*)glfwGetWindowUserPointer(window);
        app.on_char_press(keycode);
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
    {
        application& app = *(application*)glfwGetWindowUserPointer(window);
        app.on_mouse_button(button, action, mods);
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        application& app = *(application*)glfwGetWindowUserPointer(window);
        app.on_scroll(xOffset, yOffset);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
    {
        application& app = *(application*)glfwGetWindowUserPointer(window);
        app.on_cursor_pos_changed(xPos, yPos);
    });

    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);
}

void application::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        // Code to run every frame
        on_update();

        // Swap buffer and poll for events
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

application::~application()
{
    logging::debug("Closing application...");
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
