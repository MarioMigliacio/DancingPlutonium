#pragma once

#include<SFML/Graphics.hpp>
#include "enumTypes.h"

class TitleMenu
{
public:
	enum menu_states
	{
		s_undecided,
		s_play,
		s_options,
		s_score,
		s_quit
	};

public:
	TitleMenu() {}
	~TitleMenu() {};
	void Show(sf::RenderTarget& window);
	const sf::Uint32 menuState() const;

private:
	static menu_states m_state;
};