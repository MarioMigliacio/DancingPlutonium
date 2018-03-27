#include "InputManager.h"

// Static variable declarations:
sf::Uint32 DancingPlutonium::InputManager::moveState = s_noMovement;
sf::Uint32 DancingPlutonium::InputManager::action = s_noAction;

sf::Uint32 DancingPlutonium::InputManager::GetAction(sf::Event& _event)
{
	if (_event.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			return Movement::s_northWest;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			return Movement::s_northEast;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			return Movement::s_southEast;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			return Movement::s_southWest;
		}
		if (_event.key.code == sf::Keyboard::W)
		{
			return Movement::s_north;
		}
		if (_event.key.code == sf::Keyboard::A)
		{
			return Movement::s_west;
		}
		if (_event.key.code == sf::Keyboard::S)
		{
			return Movement::s_south;
		}
		if (_event.key.code == sf::Keyboard::D)
		{
			return Movement::s_east;
		}
	}
}

sf::Uint32 DancingPlutonium::InputManager::GetMovement(sf::Event& _event)
{
	return 0;
}
