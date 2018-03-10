#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include <stdlib.h>

class TitleMenu
{
public:
	enum menu_state
	{
		s_uninitialized,
		s_undecided,
		s_play,
		s_options,
		s_score,
		s_quit
	};

public:
	TitleMenu() {}
	TitleMenu(const TitleMenu& _ref) {}
	~TitleMenu() {}
	void Show(sf::RenderWindow& _window);
	sf::Uint32 getMenuState() const;
	
private:
	static sf::Uint32 m_state;
	static void cleanup(std::vector<Button*>& _container);
};