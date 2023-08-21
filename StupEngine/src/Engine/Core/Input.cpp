#include "Input.h"
#include "Application.h"
#include "GLFW/glfw3.h"

namespace Stup {

bool Input::IsKeyPressed(const KeyCode key) {
    auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindow());
    auto state = glfwGetKey(window, static_cast<int32_t>(key));
    return state == GLFW_PRESS;
}

} // namespace Stup
