#include "TitleMenu.h"
#include <iostream>

void TitleMenu::Show(sf::RenderTarget & window)
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	float scale = mode.width / 800.f;
	int m_winsizeX = mode.width;
	int m_winsizeY = mode.height;
	std::cout << m_winsizeX << "\n" << m_winsizeY << std::endl;
	float m_scale = scale;
}

sf::Uint32 TitleMenu::getMenuState() const
{
	return sf::Uint32();
}
