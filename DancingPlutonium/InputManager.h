#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"

namespace DancingPlutonium
{
	class InputManager
	{
	public:
		~InputManager() { }

		static sf::Uint32 GetDirection();
		static bool IsMoving();

	private:
		InputManager() { }
	};
}