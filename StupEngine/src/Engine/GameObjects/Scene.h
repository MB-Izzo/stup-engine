#pragma once

#include "Engine/GameObjects/GameObject.h"
#include "stuppch.h"

namespace Stup {
    class Scene 
    {
        public:
            Scene();
            ~Scene() = default;
            
            void Update(float dt);

            void AddGameObject(std::shared_ptr<GameObject> gameObject);

        private:
            std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    };
}
