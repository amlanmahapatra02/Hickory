#pragma once

#include "Hickory/Input.h"

namespace Hickory
{
	class WindowsInput : public Input
	{
		protected:
			virtual bool isKeyPressedImpl(int keycode) override;
			virtual bool isMouseButtonPressedImpl(int button) override;

			virtual std::pair<float, float> GetMousePosImpl() override;
			virtual float GetMouseXImpl() override;
			virtual float GetMouseYImpl() override;
	};
}