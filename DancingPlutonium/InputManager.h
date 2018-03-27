#pragma once

#include <SFML/Graphics.hpp>

namespace DancingPlutonium
{
	class InputManager
	{
	public:
		~InputManager() { }

		static sf::Uint32 GetAction(sf::Event& _event);
		static sf::Uint32 GetMovement(sf::Event& _event);

	public:
		enum Movement
		{
			s_noMovement,
			s_north,
			s_northEast,
			s_east,
			s_southEast,
			s_south,
			s_southWest,
			s_west,
			s_northWest,
		};

		enum Action
		{
			s_noAction,
			s_shoot,
			s_bomb
		};

	private:
		InputManager() { }
		static sf::Uint32 moveState;
		static sf::Uint32 action;
	};
}