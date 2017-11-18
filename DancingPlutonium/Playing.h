#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GenericEnemyUnit.h"
#include "BasicShip.cpp"

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
	~Playing() {}
	void Show(sf::RenderWindow& _window);
	void SpawnShip(sf::RenderWindow& _window);
	BasicShip m_ship;

private:
	sf::Vector2f Emplace(sf::RenderWindow& _window);
	static sf::Uint32 m_state;
};