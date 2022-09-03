#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel {

	// Enumerate different event types (a set of constants)
	// We use enum classes because of their type safety
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Enumerate different event categories
	// We can't use type safety here because we need to define a variable later in this code using this enum (out of scope)
	enum EventCategory {
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};

    // Some macros for defining event classes and categories in events
    #define EVENT_CLASS_TYPE(type)         static EventType GetStaticType() { return EventType::##type; }\
    								       virtual EventType GetEventType() const override { return GetStaticType(); }\
    								       virtual const char* GetName() const override { return #type; }
    
    #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	// The main class, a declaration / template for later defining
	class HAZEL_API Event {
		friend class EventDispatcher; // Allow access to this class from the EventDispatcher class (without physically inheriting)
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	// A class for handling / routing events coming from other classes (eg. window class)
	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
		: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// Ostream operator, used for logging, manipulates eve
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}

