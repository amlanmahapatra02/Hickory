#pragma once

#include "Hickory/Core.h"
#include "Hickory/Events/ApplicationEvent.h"

namespace Hickory
{
	class HICKORY_API Layer
	{
	protected:
		std::string m_DebugName;

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() { return m_DebugName; }
	};
}