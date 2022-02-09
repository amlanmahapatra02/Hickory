#pragma once

#include "Hickory/Core/Core.h"
#include "Hickory/Core/Layer.h"
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

			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnImGuiRender() override;

			void Begin();
			void End();

		private:
			float m_Time = 0.0f;
	};
}