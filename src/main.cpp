//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
//#include <glad/gl.h>
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

int main()
{
    auto logger = configure_logging();
    logger->info("Hello, OpenGL ImGui Template!");

    glm::vec4 my_vec4 = { 1.0, 0.0, 0.0, 1.0 };
    logger->info("My vec4: [{},{},{},{}]", my_vec4.x, my_vec4.y, my_vec4.z, my_vec4.w);

//    if (!glfwInit())
//    {
//        // Initialization failed
//    }

    return 0;
}
