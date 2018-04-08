#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"

namespace DancingPlutonium
{
	/* Intro class object represents the state logic for the main splash screen for Dancing Plutonium */
	class Intro
	{
	public:
		#pragma region IntroState enum

		/* IntroState enum holds the types of states that Dancing Plutonium Intro logic may be in */
		enum IntroState
		{
			s_uninitialized,
			s_playing,
			s_done
		};

		#pragma endregion
	public:
		#pragma region Ctor/Dtors

		/* Intro default constructor */
		Intro() {}
		/* Intro copy constructor */
		Intro(const Intro& _ref) {}
		/* Intro deconstructor */
		~Intro() {}

		#pragma endregion

		#pragma region Methods

		/* Runs the logic for Dancing Plutoniums Intro object */
		void Show(sf::RenderWindow& _window);
		/* Returns the state of which the Intro object is in */
		sf::Uint32 getIntroState() const;

		#pragma endregion
	private:
		static sf::Uint32 m_state;	/* Static variable which maintains the state for this Intro object */
	};
}