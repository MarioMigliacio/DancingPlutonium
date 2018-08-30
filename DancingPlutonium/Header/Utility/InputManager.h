#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"

namespace DancingPlutonium
{
	/* 
	   InputManager class can be queried at any time for static access to what kind of input the user is attempting to access.
	   Including and not limited to: Player movement, actions, commands etc.
	*/
	class InputManager
	{
	public:
		#pragma region Dtor

		/* InputManager destructor. */
		~InputManager() {}

		#pragma endregion

		#pragma region Static Methods

		/* GetDirection should be used once it is known the player is moving (Query IsMoving 1st).  */
		static sf::Uint32 GetDirection();
		/* Returns true if player is attempting to move, false otherwise. */
		static bool IsMoving();
		/* Returns true if player is pressing Left Shift or Right Shift to try to make player move faster, false otherwise. */
		static bool IsUsingBoost();
		/* Returns true if player is pressing Space bar, false otherwise. */
		static bool IsShooting();
		/* Returns true if player is pressing B key, false otherwise. */
		static bool IsUsingBomb();
		/* Returns true if player is pressing Enter key, false otherwise. */
		static bool IsFinishedReadingText();
		
		#pragma endregion
	private:
		#pragma region Ctor

		/* Disallow access to creating the InputManager class. It holds useful static methods which can be queried by using syntax: InputManager::<member name>. */
		InputManager() { }

		#pragma endregion
	};
}