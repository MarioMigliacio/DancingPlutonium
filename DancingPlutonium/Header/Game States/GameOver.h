#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"

namespace DancingPlutonium
{
	/* GameOver class object represents the state logic for the main splash screen for Dancing Plutonium */
	class GameOver
	{
	public:
		#pragma region IntroState enum

		/* GameOver enum holds the types of states that Dancing Plutonium GameOver logic may be in */
		enum GameOverState
		{
			s_uninitialized,
			s_playing,
			s_done
		};

		#pragma endregion
	public:
		#pragma region Ctor/Dtors

		/* GameOver default constructor */
		GameOver() {}
		/* GameOver copy constructor */
		GameOver(const GameOver& _ref) {}
		/* GameOver destructor */
		~GameOver() {}

		#pragma endregion

		#pragma region Methods

		/* Runs the logic for Dancing Plutoniums GameOver object */
		void Show(sf::RenderWindow& _window);
		/* Returns the state of which the GameOver object is in */
		sf::Uint32 getGameOverState() const;

		#pragma endregion
	private:
		static sf::Uint32 m_state;	/* Static variable which maintains the state for this GameOver object */
	};
}