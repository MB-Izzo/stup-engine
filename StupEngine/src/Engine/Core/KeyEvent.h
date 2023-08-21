#pragma once

#include "Engine/Core/Event.h"
#include "Engine/Core/KeyCodes.h"

namespace Stup 
{
    class KeyEvent : public Event
    {
        public:
            KeyCode GetKeyCode() const { return m_keyCode; }
        protected:
            KeyEvent(const KeyCode keycode) : m_keyCode(keycode) {}
            KeyCode m_keyCode;

    };

    class KeyPressedEvent : public KeyEvent
    {
        public:
            KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
                : KeyEvent(keycode), m_isRepeat(isRepeat) {}

            bool IsRepeat() const { return m_isRepeat; }
            EVENT_CLASS_TYPE(KeyPressed);
        private:
            bool m_isRepeat;

    };
}
