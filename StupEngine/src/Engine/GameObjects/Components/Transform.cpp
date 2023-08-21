#include "Transform.h"

namespace Stup {
Transform::Transform()
{
}

void Transform::SetPosition(const glm::vec2 &newPos) { m_position = newPos; }

const glm::vec2 &Transform::GetPosition() const { return m_position; }

void Transform::Update(float dt)
{
};

} // namespace Stup
