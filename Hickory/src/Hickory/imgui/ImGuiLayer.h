#pragma once

#include "Hickory/Core.h"
#include "Hickory/Layer.h"
#include "Hickory/Events/ApplicationEvent.h"
#include "Hickory/Events/KeyEvent.h"
#include "Hickory/Events/MouseEvent.h"

namespace Hickory
{
	class HICKORY_API ImGuiLayer : public Layer
	{
		public:
			ImGuiLayer();
			~ImGuiLayer();

			void OnAttach();
			void OnDetach();
			void OnUpdate();
			void OnEvent(Event& event);

		private:
			bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
			bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
			bool OnMouseMovedEvent(MouseMovedEvent& e);
			bool OnMouseScrolledEvent(MouseScrolledEvent& e);
			bool OnKeyPressedEvent(KeyPressedEvent& e);
			bool OnKeyReleasedEvent(KeyReleasedEvent& e);
			bool OnKeyTypedEvent(KeyTypedEvent& e);
			bool OnWindowResizeEvent(WindowResizeEvent& e);

		private:
			float m_Time = 0.0f;
	};
}