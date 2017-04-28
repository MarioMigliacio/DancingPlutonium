#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"

class TitleMenu
{
public:
	TitleMenu() {}
	~TitleMenu() {};
	void Show(sf::RenderTarget& window);
	sf::Uint32 getMenuState() const;

private:
	enum menu_states
	{
		s_undecided,
		s_play,
		s_options,
		s_score,
		s_quit
	};

private:
	static menu_states m_state;
};