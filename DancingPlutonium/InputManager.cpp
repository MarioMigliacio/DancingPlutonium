#include "InputManager.h"

sf::Uint32 DancingPlutonium::InputManager::GetDirection()
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		return Movement::s_noMovement;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		return Movement::s_noMovement;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		return Movement::s_north;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		return Movement::s_west;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		return Movement::s_south;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		return Movement::s_east;
	}
	
	return Movement::s_noMovement;
}

bool DancingPlutonium::InputManager::IsMoving()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		return true;
	}

	return false;
}
