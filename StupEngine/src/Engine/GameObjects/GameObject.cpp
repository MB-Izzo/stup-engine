#include "GameObject.h"

namespace Stup {

GameObject::GameObject() { m_transform = std::make_unique<Transform>(); }
GameObject::~GameObject() {}

void GameObject::Update(float dt) {}
} // namespace Stup
