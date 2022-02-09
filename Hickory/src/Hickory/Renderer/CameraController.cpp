#include "hkpch.h"
#include "CameraController.h"

#include "Hickory/Core/KeyCodes.h"
#include "Hickory/Core/Input.h"

namespace Hickory
{

	CameraController::CameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * ZoomLevel, m_AspectRatio* ZoomLevel, -ZoomLevel, ZoomLevel),
		 m_Rotation(rotation)
	{
	}

	void CameraController::OnUpdate(Timestep DeltaTime)
	{
		if (Hickory::Input::isKeyPressed(HK_KEY_RIGHT) || Hickory::Input::isKeyPressed(HK_KEY_D))
			m_CameraPosition.x += m_CameraSpeed * DeltaTime;

		else if (Hickory::Input::isKeyPressed(HK_KEY_LEFT) || Hickory::Input::isKeyPressed(HK_KEY_A))
			m_CameraPosition.x -= m_CameraSpeed * DeltaTime;

		if (Hickory::Input::isKeyPressed(HK_KEY_UP) || Hickory::Input::isKeyPressed(HK_KEY_W))
			m_CameraPosition.y += m_CameraSpeed * DeltaTime;

		else if (Hickory::Input::isKeyPressed(HK_KEY_DOWN) || Hickory::Input::isKeyPressed(HK_KEY_S))
			m_CameraPosition.y -= m_CameraSpeed * DeltaTime;

		if (m_Rotation)
		{
			if (Hickory::Input::isKeyPressed(HK_KEY_Q))
			{
				m_CameraRotation += m_CameraRotation * DeltaTime;
			}

			if (Hickory::Input::isKeyPressed(HK_KEY_E))
			{
				m_CameraRotation -= m_CameraRotation * DeltaTime;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraSpeed = ZoomLevel;
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispacter(e);
		dispacter.Dispatch<MouseScrolledEvent>(HK_BIND_EVENT_FUNC(CameraController::OnMouseScrolled));
		dispacter.Dispatch<WindowResizeEvent>(HK_BIND_EVENT_FUNC(CameraController::OnWindowResized));
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		ZoomLevel -= e.GetYOffset() * 0.25f;
		ZoomLevel = std::max(ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * ZoomLevel, m_AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel);

		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * ZoomLevel, m_AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel);

		return false;
	}

}