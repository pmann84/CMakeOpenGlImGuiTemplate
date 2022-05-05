#include "application.hpp"

application::application(application_data application_props) : m_props(application_props)
{
    logging::init(spdlog::level::debug);

    if (!glfwInit())
    {
        // Initialization failed
        logging::critical("GLFW Initialisation failed.");
        return;
    }

//    glfwSetErrorCallback(error_callback);

    m_window = glfwCreateWindow(m_props.width, m_props.height, m_props.title.c_str(), NULL, NULL);
    if (!m_window)
    {
        // Window or context creation failed
        logging::critical("GLFW Window creation failed.");
        glfwTerminate();
        return;
    }
//    glfwSetKeyCallback(m_window,key_callback);
//    glfwSetWindowCloseCallback(m_window,window_close_callback);

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
