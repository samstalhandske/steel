#include "pch.h"
#include "Input.hpp"

namespace Steel
{
	Input* Input::GetInstance()
	{
		return myInstance;
	}

	bool Input::IsKeyPressed(int keyCode)
	{
		return myInstance->IsKeyPressedImpl(keyCode);
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		return myInstance->IsMouseButtonPressedImpl(button);
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		return myInstance->GetMousePositionImpl();
	}
}
