#pragma once

#include "Engine/Core/KeyCodes.h"
namespace Stup {
    class Input
    {
        public:
            static Input &shared_instance()
            {
                static Input input;
                return input;
            }
            static bool IsKeyPressed(const KeyCode key);
    };
}
