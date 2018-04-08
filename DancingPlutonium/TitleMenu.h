#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include <stdlib.h>

namespace DancingPlutonium
{
	/* TitleMenu class object represents the state logic for when user is at the main menu for the Dancing Plutonium game */
	class TitleMenu
	{
	public:
		#pragma region MenuState enum

		/* MenuState enum holds the types of states that Dancing Plutonium TitleMenu logic may be in */
		enum MenuState
		{
			s_uninitialized,
			s_undecided,
			s_play,
			s_options,
			s_score,
			s_quit
		};
		
		#pragma endregion
	public:
		#pragma region Ctor/Dtors

		/* TitleMenu default constructor*/
		TitleMenu() {}
		/* TitleMenu copy constructor */
		TitleMenu(const TitleMenu& _ref) {}
		/* TitleMenu deconstructor */
		~TitleMenu() {}

		#pragma endregion

		#pragma region Methods

		/* Runs the logic for Dancing Plutoniums TitleMenu object */
		void Show(sf::RenderWindow& _window);
		/* Returns the state of which the TitleMenu object is in */
		sf::Uint32 getMenuState() const;

		#pragma endregion
	private:
		#pragma region Cleanup

		/* Static method which handles the destruction of relevant Buttons to this TitleMenu object */
		static void cleanup(std::vector<Button*>& _container);

		#pragma endregion
	private:
		static sf::Uint32 m_state;	/* Static variable which maintains the state for this Playing object */
	};
}