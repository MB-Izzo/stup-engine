#include "Scene.h"

namespace Stup {

Scene::Scene()
{
}

void Scene::Update(float dt) {
    for (auto& gameObject : m_gameObjects)
    {
        gameObject->Update(dt);
    }
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    m_gameObjects.push_back(gameObject);
}

} // namespace Stup
