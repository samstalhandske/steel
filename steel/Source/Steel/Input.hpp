
#pragma once
#include "Steel/Core.hpp"

namespace Steel
{
	class Input
	{
	public:
		static Input* GetInstance();
		static bool IsKeyPressed(int keyCode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* myInstance;
	};
}