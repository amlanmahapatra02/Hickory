#pragma once

#include "Hickory/Core.h"
#include "Hickory/Events/ApplicationEvent.h"
#include "Hickory/Core/Timestep.h"

namespace Hickory
{
	class HICKORY_API Layer
	{
	protected:
		std::string m_DebugName;

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep DeltaTime) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() { return m_DebugName; }
	};
}