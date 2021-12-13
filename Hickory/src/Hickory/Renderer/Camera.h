#pragma once

#include<glm/glm.hpp>

namespace Hickory
{
	class Camera
	{
		public:
			Camera(float left, float right, float bottom, float top);

			inline glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
			inline glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
			inline glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

			//Setters Function
			inline void SetPosition(const glm::vec3& position) { m_Position = position; CalculateViewMatrix(); }
			inline void SetRotation(float rotation) { m_Rotation = rotation; CalculateViewMatrix(); }

			//Getters Function
			inline glm::vec3& GetPosition() { return m_Position; }
			inline float GetRotation() { return m_Rotation; }

		private:

			void CalculateViewMatrix();


		private:

			glm::mat4 m_ProjectionMatrix;
			glm::mat4 m_ViewMatrix;
			glm::mat4 m_ViewProjectionMatrix;

			glm::vec3 m_Position = glm::vec3(0.0f);
			float m_Rotation = 0.0f;

	};
}