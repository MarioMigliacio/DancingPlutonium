#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BasicShip.h"
#include "PlutoniumShip.h"
#include "InputManager.h"
#include "Weapon.h"
#include "Collision.h"
#include "LevelObserver.h"

namespace DancingPlutonium
{
	/* Level1 class object represents the state logic for when user is playing the first stage in Dancing Plutonium game */
	class Level1
	{
	public:
		#pragma region PlayState enum

		/* LevelState enum holds the types of states that this Level object may be in */
		enum LevelState
		{
			s_uninitialized,
			s_intro,
			s_wave1,
			s_wave2,
			s_quit
		};

		#pragma endregion

		#pragma region Ctor/Dtors

		/* Level1 default constructor */
		Level1() {}
		/* Level1 copy constructor */
		Level1(const Level1& _ref) {}
		/* Level1 deconstructor */
		~Level1() {}

		#pragma endregion

		#pragma region Methods

		/* Runs the logic for this Level object */
		void Show(sf::RenderWindow& _window, PlutoniumShip* _player);

		#pragma endregion

	private:
		static sf::Uint32 m_state;		/* Static variable which maintains the state for this Level1 object */
	};
}