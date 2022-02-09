#pragma  once

#include "Hickory/Renderer/Camera.h"
#include "Hickory/Core/Timestep.h"

#include "Hickory/Events/ApplicationEvent.h"
#include "Hickory/Events/MouseEvent.h"

namespace Hickory
{
	class CameraController
	{
		public:

			CameraController(float aspectRatio, bool rotation = false);

			void OnUpdate(Timestep DeltaTime);
			void OnEvent(Event& e);

			Camera& GetCamera() { return m_Camera; }
			const Camera& GetCamera() const { return m_Camera; }

		private:
			bool OnMouseScrolled(MouseScrolledEvent& e);
			bool OnWindowResized(WindowResizeEvent& e);

		private:
			float m_AspectRatio;
			float ZoomLevel = 1.0f;
			bool m_Rotation;
			Camera m_Camera;

			glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
			float m_CameraRotation = 180.0f;
			float m_CameraSpeed = 5.0f;

	};
}
