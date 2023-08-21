#pragma once

#include "Engine/Core/Event.h"
#include "stuppch.h"
#include <GLFW/glfw3.h>

namespace Stup {

namespace Config {
struct WindowConfig {
    std::string Title;
    uint32_t Width, Height;

    WindowConfig(const std::string &title, uint32_t width, uint32_t height)
        : Title(title), Width(width), Height(height)
    {
    }
};
} // namespace Config

class Window {
  public:
    using EventCallbackFn = std::function<void(Event&)>;

    Window(const Config::WindowConfig &config);
    ~Window();
    void OnUpdate();

    void *GetWindow() { return m_window; }
    uint32_t GetWidth() { return m_windowConfig.Width; };
    uint32_t GetHeight() { return m_windowConfig.Height; };

    bool IsVsyncEnabled() { return m_vsyncEnabled; }
    void SetVsync(bool enabled);

    void SetEventCallback(const EventCallbackFn& callback) { 
        m_eventCallback = callback; 
    }

  private:
    void SwapBuffers();

  private:
    void OnEvent(Event& e);
    EventCallbackFn m_eventCallback;
    GLFWwindow *m_window;
    Config::WindowConfig m_windowConfig;
    bool m_vsyncEnabled;
};
} // namespace Stup
