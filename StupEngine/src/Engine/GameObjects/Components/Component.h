#pragma once

#include "stuppch.h"

namespace Stup {
    class GameObject;
    class Component
    {
        public:
            Component();
            ~Component();

            virtual void Update(float dt) = 0;
        protected:
            std::shared_ptr<GameObject> m_owner;
    };

}
