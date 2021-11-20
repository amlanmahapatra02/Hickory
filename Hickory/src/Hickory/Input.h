#pragma once

#include "Hickory/Core.h"

namespace Hickory
{
	class HICKORY_API Input
	{
		private:
			static Input* s_Instance;

		public:
			inline static bool isKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode); }

			inline static bool isMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); }

			inline static std::pair<float, float>GetMousePos() { return s_Instance->GetMousePosImpl(); }

			inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
			inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		protected:
			virtual bool isKeyPressedImpl(int keycode) = 0;

			virtual bool isMouseButtonPressedImpl(int keycode) = 0;

			virtual std::pair<float, float>GetMousePosImpl() = 0;

			virtual float GetMouseXImpl() = 0;
			virtual float GetMouseYImpl() = 0;
	};
}