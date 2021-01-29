#pragma once

#include "Mango/Events/Event.h"
#include "Mango/Core/KeyCodes.h"
#include <sstream>

namespace Mango {

	class KeyEvent : public Event
	{
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent() = default;
	};

	class KeyCodeEvent : public KeyEvent
	{
	public:
		inline KeyCode GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyCodeEvent(KeyCode keyCode)
			: m_KeyCode(keyCode) {}

		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyCodeEvent
	{
	public:
		KeyPressedEvent(KeyCode keyCode, int repeatCount)
			: KeyCodeEvent(keyCode), m_RepeatCount(repeatCount) { }
	
		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressed: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyCodeEvent
	{
	public:
		KeyReleasedEvent(KeyCode keyCode)
			: KeyCodeEvent(keyCode) { }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleased: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};
	
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(uint32_t codepoint)
			: KeyEvent(), m_Codepoint(codepoint) { }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTyped: " << m_Codepoint;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);

	private:
		uint32_t m_Codepoint;
	};

}
