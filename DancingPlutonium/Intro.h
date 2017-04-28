#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"

class Intro
{
public:
	Intro() {}
	~Intro() {}
	void Show(sf::RenderWindow& window);
	sf::Uint32 getIntroState() const;

private:

	enum intro_state
	{
		s_uninitialized,
		s_playing,
		s_done
	};

private:
	static sf::Uint32 m_state;
};