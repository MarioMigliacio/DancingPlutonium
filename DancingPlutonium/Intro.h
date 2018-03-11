#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"

namespace DancingPlutonium
{
	class Intro
	{
	public:
		enum intro_state
		{
			s_uninitialized,
			s_playing,
			s_done
		};

	public:
		Intro() {}
		Intro(const Intro& _ref) {}
		~Intro() {}
		void Show(sf::RenderWindow& _window);
		sf::Uint32 getIntroState() const;

	private:
		static sf::Uint32 m_state;
	};
}