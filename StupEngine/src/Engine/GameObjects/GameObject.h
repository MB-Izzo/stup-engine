#pragma once

#include "Engine/GameObjects/Components/Component.h"
#include "Engine/GameObjects/Components/Transform.h"
#include "stuppch.h"
#include <glm/glm.hpp>

namespace Stup {
class GameObject {
  public:
    GameObject();
    ~GameObject();

    virtual void Update(float dt);
    Transform& GetTransform() { return *m_transform; }

  private:
    std::unique_ptr<Transform> m_transform;
};
} // namespace Stup
