#pragma once

#include "Engine/GameObjects/Components/Component.h"
#include "Engine/GameObjects/Components/Transform.h"
#include <glm/glm.hpp>

namespace Stup {
class Rigidbody : public Component {
  public:
    Rigidbody(Transform &transform);
    ~Rigidbody() = default;

    void SetVelocity(const glm::vec2 &velocity);
    void SetVelocity(int x, int y);
    const glm::vec2 &GetVelocity() { return m_velocity; }
    void Update(float dt) override;

  private:
    Transform &m_transform;
    glm::vec2 m_velocity;
};
} // namespace Stup
