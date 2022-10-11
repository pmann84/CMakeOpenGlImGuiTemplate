#include "application.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void application::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        // Swap buffer and poll for events
        glfwPollEvents();

        // Code to update every frame
        on_update(m_time_step);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static ImGuiDockNodeFlags dock_space_flags = ImGuiDockNodeFlags_None;

            // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
            // because it would be confusing to have two docking targets within each others.
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

            // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
            // and handle the pass-thru hole, so we ask Begin() to not render a background.
            if (dock_space_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
                window_flags |= ImGuiWindowFlags_NoBackground;
            }

            // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
            // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
            // all active windows docked into it will lose their parent and become undocked.
            // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
            // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("DockSpace Demo", nullptr, window_flags);
            ImGui::PopStyleVar();

            ImGui::PopStyleVar(2);

            // Submit the DockSpace
            ImGuiIO &io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dock_space_id = ImGui::GetID("AppDockSpace");
                ImGui::DockSpace(dock_space_id, ImVec2(0.0f, 0.0f), dock_space_flags);
            }

            bool show_demo_window = true;
            ImGui::ShowDemoWindow(&show_demo_window);

            ImGui::Begin("Application Info", nullptr);
            ImGui::Text("OpenGL Vendor: %s", glGetString(GL_VENDOR));
            ImGui::Text("OpenGL Renderer: %s", glGetString(GL_RENDERER));
            ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));
            ImGui::Text("ImGui Version: %s", IMGUI_VERSION);
            ImGui::Separator();
            ImGui::End();

            // UI Code to run every frame
            glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            on_ui_render();


            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(m_window);

        float time = (float)glfwGetTime();
        m_frame_time = time - m_last_frame_time;
        m_time_step = glm::min<float>(m_frame_time, 0.0333f);
        m_last_frame_time = time;
    }
}

application::~application()
{
    logging::debug("Closing application...");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}
