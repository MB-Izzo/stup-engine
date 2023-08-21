#include "Rigidbody.h"

namespace Stup {

Rigidbody::Rigidbody(Transform &transform) : m_transform(transform) {}

void Rigidbody::SetVelocity(const glm::vec2 &velocity)
{
    m_velocity = velocity;
}

void Rigidbody::SetVelocity(int x, int y) { m_velocity = glm::vec2(x, y); }

void Rigidbody::Update(float dt)
{
    m_transform.position().x += m_velocity.x * dt;
    m_transform.position().y += m_velocity.y * dt;
}

} // namespace Stup
