#pragma once

#include "Event.h"
#include <sstream>

namespace Hickory
{
	class HICKORY_API MouseMovedEvent : public Event
	{
		private:
			float m_MouseX, m_MouseY;

		public:
			MouseMovedEvent(float x, float y)
				:m_MouseX(x), m_MouseY(y)
			{
			}

			inline float GetX() const { return m_MouseX; }
			inline float GetY() const { return m_MouseY; }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseMovedEvent: " << m_MouseX << " , " << m_MouseY;
				ss.str();
			}

			EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class HICKORY_API MouseScrolledEvent : public Event
	{
		private:
			float m_XOffset, m_YOffset;

		public:
			MouseScrolledEvent(float xoffset, float yoffset)
				:m_XOffset(xoffset), m_YOffset(m_YOffset)
			{
			}

			inline float GetXOffset() const { return m_XOffset; }
			inline float GetYOffset() const { return m_YOffset; }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseScrolledEvent: " << m_XOffset << " , " << m_YOffset;
				ss.str();
			}

			EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class HICKORY_API MouseButtonEvent : public Event
	{
		protected:
			int m_Button;

			MouseButtonEvent(int button)
				: m_Button(button)
			{
			}

		public:
			inline int GetMouseButton() const { return m_Button; }

			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class HICKORY_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
				:MouseButtonEvent(button)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class HICKORY_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}