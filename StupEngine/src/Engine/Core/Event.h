#pragma once

#include "stuppch.h"

namespace Stup {

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender, KeyPressed, KeyTyped, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                                                virtual const char* GetName() const override { return #type; }

class Event {
  public:
    virtual ~Event() = default;
    bool Handled = false; // todo property

    virtual EventType GetEventType() const = 0;
    virtual const char *GetName() const = 0;
    //        virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }
};

class EventDispatcher
{
    public:
        EventDispatcher(Event& event) : m_event(event)
        {}

        // F deduced by compiler
        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_event.GetEventType() == T::GetStaticType())
            {
                m_event.Handled |= func(static_cast<T&>(m_event));
                return true;
            }
            return false;
        }

    private:
        Event& m_event;
};
} // namespace Stup
