#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <glm/vec4.hpp>

std::shared_ptr<spdlog::logger> configure_logging()
{
    auto log_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
//    log_sink->set_pattern("%^[%T] %n: %v%$");
    auto logger = std::make_shared<spdlog::logger>("App", log_sink);
    spdlog::register_logger(logger);
    logger->set_level(spdlog::level::trace);
    logger->flush_on(spdlog::level::trace);
    return logger;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    fprintf(stdout, "Key: %i, scancode: %i, action: %i\n", key, scancode, action);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void window_close_callback(GLFWwindow* window)
{
    fprintf(stdout, "Window closing...\n");
}

int main()
{
    auto logger = configure_logging();
    logger->info("Hello, OpenGL ImGui Template!");

    glm::vec4 my_vec4 = { 1.0, 0.0, 0.0, 1.0 };
    logger->info("My vec4: [{},{},{},{}]", my_vec4.x, my_vec4.y, my_vec4.z, my_vec4.w);

    if (!glfwInit())
    {
        // Initialization failed
        logger->critical("GLFW Initialisation failed.");
    }

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL ImGui Template", NULL, NULL);
    if (!window)
    {
        // Window or context creation failed
        logger->critical("GLFW Window creation failed.");
        glfwTerminate();
        return 1;
    }
    glfwSetKeyCallback(window,key_callback);
    glfwSetWindowCloseCallback(window,window_close_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);


    while (!glfwWindowShouldClose(window))
    {
        // Code to run every frame

        // Swap buffer and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
