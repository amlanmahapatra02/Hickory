#pragma once

#include<glm/glm.hpp>

namespace Hickory
{
	class Camera
	{
		public:
			Camera(float left, float right, float bottom, float top);

			void SetProjection(float left, float right, float bottom, float top);

			const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
			const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
			const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

			//Setters Function
			void SetPosition(const glm::vec3& position) { m_Position = position; CalculateViewMatrix(); }
			void SetRotation(float rotation) { m_Rotation = rotation; CalculateViewMatrix(); }

			//Getters Function
			const glm::vec3& GetPosition() { return m_Position; }
			const float GetRotation() { return m_Rotation; }

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