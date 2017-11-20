#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BasicShip.h"
#include "PlutoniumShip.h"
#include "BasicBullet.h"

class Playing
{
public:
	enum play_state
	{
		s_uninitialized,
		s_playing,
		s_quit
	};

	Playing() {}
	Playing(const Playing& _ref) {}
	~Playing() {}
	void Show(sf::RenderWindow& _window);

private:
	static sf::Uint32 m_state;
};