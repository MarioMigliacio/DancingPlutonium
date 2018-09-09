#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BasicShip.h"
#include "PlutoniumShip.h"
#include "InputManager.h"
#include "Weapon.h"
#include "Collision.h"
#include "Level1.h"
#include "ChatBox.h"

namespace DancingPlutonium
{
	/* Playing class object represents the state logic for when user is playing the Dancing Plutonium game */
	class Playing
	{
	public:
		#pragma region PlayState enum

		/* PlayState enum holds the types of states that Dancing Plutonium Playing logic may be in */
		enum PlayState
		{
			s_uninitialized,
			s_sandbox,
			s_level1,
			s_gameover,
			s_quit
		};

		#pragma endregion

		#pragma region Ctor/Dtors

		/* Playing default constructor */
		Playing() {}
		/* Playing copy constructor */
		Playing(const Playing& _ref) {}
		/* Playing deconstructor */
		~Playing() {}

		#pragma endregion

		#pragma region Methods

		/* Runs the logic for Dancing Plutoniums Playing object */
		void Show(sf::RenderWindow& _window);
		/* Returns the state of which the Playing object is in */
		sf::Uint32 getPlayState() const;

		#pragma endregion
	private:
		static sf::Uint32 m_state;	/* Static variable which maintains the state for this Playing object */
	};
}