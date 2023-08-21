#pragma once

#include "Engine/Core/ApplicationEvent.h"
#include "Engine/Core/Event.h"
#include "Engine/Core/Layer.h"
#include "stuppch.h"

#include "Engine/Renderer/Window.h"

namespace Stup {

class Application {
  public:
    Application();
    ~Application();

    void Run();

    void PushLayer(Layer *const layer);

    void OnEvent(Event &e);

    Window &GetWindow() { return *m_window; }

    static Application& Get() { return *s_instance; }

  private:
    bool OnWindowClose(WindowCloseEvent &event);

  private:
    static Application* s_instance;
    std::vector<Layer *> m_layers;
    std::unique_ptr<Window> m_window;
    bool m_running;

    float m_lastFrameTime;
};

} // namespace Stup
