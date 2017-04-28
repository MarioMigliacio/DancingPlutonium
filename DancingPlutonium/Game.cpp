#include "Game.h"
#include "Intro.h"

// Static variable declarations:
sf::Uint32 Game::m_state = s_uninitialized;
sf::RenderWindow Game::m_window;

void Game::Initialize()
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (m_state != current_state::s_uninitialized)
	{
		return;
	}

	// Create the Rendering Window.
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(mode.width, mode.height, mode.bitsPerPixel), "Dancing Plutonium", sf::Style::Fullscreen);

	m_state = current_state::s_intro;

	while (!Quitting())
	{
		Run();
	}

	m_window.close();
}

void Game::Run()
{
	switch (m_state)
	{
		case current_state::s_intro:
			Introduction();
			m_state = current_state::s_menu;
			break;
		case current_state::s_menu:
			Menu();
			m_state = current_state::s_quit;
			break;
		case current_state::s_playing:
			Play();
			break;
		case current_state::s_options:
			Options();
			break;
		case current_state::s_scoreboard:
			ScoreScreen();
			break;
		case current_state::s_levelwin:
			WinLevel();
			break;
		case current_state::s_gameover:
			GameOver();
			break;
		default:
			break;
	}
}

void Game::Introduction()
{
	Intro intro;
	m_window.setTitle("Intro");	
	intro.Show(m_window);
}

void Game::Menu()
{
	m_window.setTitle("Main Menu");
	// get around to creating the menu class.	
}

void Game::Play()
{
	m_window.setTitle("Playing");
	// get around to creating the playing class.
}

void Game::WinLevel()
{
	m_window.setTitle("Mission Success");
	// get around to creating the mission class.
}

void Game::GameOver()
{
	m_window.setTitle("Game Over");
	// get around to creating the gameover class.
}

void Game::Options()
{
	m_window.setTitle("Options");
	// get around to creating the options class.
}

void Game::ScoreScreen()
{
	m_window.setTitle("Scoreboard");
	// get around to creating the scoreboard class.
}

bool Game::Quitting()
{
	return m_state == current_state::s_quit;
}