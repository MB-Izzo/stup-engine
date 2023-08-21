#include "Window.h"

#include "Engine/Core/ApplicationEvent.h"
#include "Engine/Core/KeyEvent.h"
#include "Engine/Renderer/Renderer.h"
#include "stuppch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Stup {

Window::Window(const Config::WindowConfig &config) : m_windowConfig(config)
{
    if (!glfwInit()) {
        std::cout << "GLFW failed to Init." << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    m_window = glfwCreateWindow(m_windowConfig.Width, m_windowConfig.Height,
                                m_windowConfig.Title.c_str(), NULL, NULL);

    glfwSetWindowUserPointer(m_window, this);

    if (m_window == NULL) {
        std::cout << "Failed to create GLFW window"
                  << std::endl; // TODO: ERROR LOG spd_log
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);

    // TODO: Handle Callbacks / events
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
        std::cout << "Here" << std::endl;
        Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
//        Window& instance = *(Window*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        instance->OnEvent(event);
        std::cout << "There";
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
            {
                Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
                switch(action)
                {
                    case GLFW_PRESS:
                    {
                        KeyPressedEvent event(key, 0);
                        instance->OnEvent(event);
                        break;
                    }
                }
            }
    );

    std::cout << "Window created" << std::endl;
}
void Window::OnEvent(Event& e)
{
    m_eventCallback(e);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::OnUpdate()
{
    glfwPollEvents();
    SwapBuffers();
}

void Window::SetVsync(bool enabled)
{
    if (enabled) {
        glfwSwapInterval(1);
    }
    else {
        glfwSwapInterval(0);
    }
    m_vsyncEnabled = enabled;
}

void Window::SwapBuffers() { glfwSwapBuffers(m_window); }

} // namespace Stup
