#include "Application.h"
#include "Engine/Renderer/Window.h"

// TODO: Put in a place with all helpers macros
#define STUP_BIND_EVENT_FN(fn)                                                 \
    [this](auto &&...args) -> decltype(auto) {                                 \
        return this->fn(std::forward<decltype(args)>(args)...);                \
    }

namespace Stup {

Application *Application::s_instance = nullptr;

Application::Application()
{
    s_instance = this;
    Config::WindowConfig window_config =
        Config::WindowConfig("Game Name", 640, 640);
    m_window = std::make_unique<Window>(window_config);
    m_window->SetEventCallback(STUP_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() { std::cout << "app got killed"; }

void Application::Run()
{
    while (m_running) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - m_lastFrameTime;
        m_lastFrameTime = currentFrame;

        for (Layer *layer : m_layers) {
            layer->OnUpdate(deltaTime);
        }

        m_window->OnUpdate();
    }
}

void Application::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(
        STUP_BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = m_layers.begin(); it != m_layers.end(); ++it) {
        if (e.Handled)
            break;

        (*it)->OnEvent(e);
    }
}

bool Application::OnWindowClose(WindowCloseEvent &event)
{
    std::cout << "on window close called";
    m_running = false;
    return true;
}

void Application::PushLayer(Layer *const layer)
{
    m_layers.push_back(layer);
    layer->OnAttach();
}

} // namespace Stup
