#pragma once

#include "Engine/Core/Event.h"

namespace Stup {
    class WindowCloseEvent : public Event
    {
        public: 
            WindowCloseEvent() = default;
            EVENT_CLASS_TYPE(WindowClose)

    };

}
