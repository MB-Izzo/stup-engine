#pragma once

#include "Engine/Core/Event.h"
namespace Stup {

class Layer {
  public:
    Layer();
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate(float dt) {}
    virtual void OnEvent(Event& e) {}
};

} // namespace Stup
