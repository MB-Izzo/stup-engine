#pragma once

#include "Engine/GameObjects/Components/Component.h"
#include <glm/glm.hpp>

namespace Stup {
    class Transform : public Component
    {
        public:
            Transform();
            ~Transform() = default;

            void SetPosition(const glm::vec2& newPos);
            const glm::vec2& GetPosition() const;

            glm::vec2& position() { return m_position; }


            void Update(float dt) override;
        private:
            glm::vec2 m_position = glm::vec2(0,0);
    };

}
