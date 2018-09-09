#include "Game.h"

// Static variable declarations:
sf::Uint32 DancingPlutonium::Game::m_state = s_uninitialized;
sf::RenderWindow DancingPlutonium::Game::m_window;

void DancingPlutonium::Game::Initialize()
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (m_state != CurrentState::s_uninitialized)
	{
		return;
	}
	// sf::Style::Fullscreen
	// Create the Rendering Window.
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();

	// 720p resolution: 1280 x 720
	const int gameWidth = 1280;
	const int gameHeight = 720;
	sf::View gameView;
	gameView.reset(sf::FloatRect(0.f, 0.f, static_cast<float>(gameWidth), static_cast<float>(gameHeight)));
	gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	// use the sf::Style to change the window's options. Fullscreen makes debugging a nightmare, the Titlebar + close styles prevent resizing window.
	m_window.create(sf::VideoMode(gameWidth, gameHeight, mode.bitsPerPixel), "Dancing Plutonium", sf::Style::Titlebar | sf::Style::Close);
	m_window.setView(gameView);
	m_window.setFramerateLimit(60);

	m_state = CurrentState::s_intro;

	while (!Quitting())
	{
		Run();
	}

	m_window.close();
}

void DancingPlutonium::Game::Run()
{
	switch (m_state)
	{
		case CurrentState::s_intro:
			Introduction();			
			break;
		case CurrentState::s_menu:
			Menu();
			break;
		case CurrentState::s_playing:
			Play();
			break;
		case CurrentState::s_options:
			Options();
			break;
		case CurrentState::s_scoreboard:
			ScoreScreen();
			break;
		case CurrentState::s_levelwin:
			WinLevel();
			break;
		case CurrentState::s_gameover:
			GameOver();
			break;
		default:
			break;
	}
}

void DancingPlutonium::Game::Introduction()
{
	Intro intro;
	m_window.setTitle("Intro");	
	intro.Show(m_window);

	if (intro.getIntroState() == Intro::s_done)
	{
		m_state = CurrentState::s_menu;
	}
}

void DancingPlutonium::Game::Menu()
{
	TitleMenu menu;
	m_window.setTitle("Main Menu");
	menu.Show(m_window);

	if (menu.getMenuState() == TitleMenu::s_play)
	{
		sf::SoundBuffer sb;
		sb.loadFromFile("Content/Sounds/PewPew.wav");

		sf::Sound menusound;
		menusound.setBuffer(sb);
		menusound.setVolume(85);
		menusound.play();

		sf::Clock timer;

		while (timer.getElapsedTime().asSeconds() < 1.0f){}

		m_state = CurrentState::s_playing;
	}
	else if (menu.getMenuState() == TitleMenu::s_options)
	{
		sf::SoundBuffer sb;
		sb.loadFromFile("Content/Sounds/Explosion.wav");

		sf::Sound menusound;
		menusound.setBuffer(sb);
		menusound.setVolume(85);
		menusound.play();

		sf::Clock timer;

		while (timer.getElapsedTime().asSeconds() < 1.0f) {}

		m_state = CurrentState::s_quit;
	}
	else if (menu.getMenuState() == TitleMenu::s_score)
	{
		sf::SoundBuffer sb;
		sb.loadFromFile("Content/Sounds/Bomb.wav");

		sf::Sound menusound;
		menusound.setBuffer(sb);
		menusound.setVolume(85);
		menusound.play();

		sf::Clock timer;

		while (timer.getElapsedTime().asSeconds() < 1.0f) {}

		m_state = CurrentState::s_quit;
	}
	else if (menu.getMenuState() == TitleMenu::s_quit)
	{
		m_state = CurrentState::s_quit;
	}
}

void DancingPlutonium::Game::Play()
{
	m_window.setTitle("Playing");
	Playing playGame;

	playGame.Show(m_window);

	if (playGame.getPlayState() == Playing::PlayState::s_gameover)
	{
		m_state = CurrentState::s_gameover;
	}
	else
	{
		m_state = CurrentState::s_quit;
	}
}

void DancingPlutonium::Game::WinLevel()
{
	m_window.setTitle("Mission Success");
	// get around to creating the mission class.
}

void DancingPlutonium::Game::GameOver()
{
	DancingPlutonium::GameOver gameOver;
	m_window.setTitle("Game Over");
	gameOver.Show(m_window);

	if (gameOver.getGameOverState() == GameOver::GameOverState::s_done)
	{
		m_state = CurrentState::s_menu;
	}
}

void DancingPlutonium::Game::Options()
{
	m_window.setTitle("Options");
	// get around to creating the options class.
}

void DancingPlutonium::Game::ScoreScreen()
{
	m_window.setTitle("Scoreboard");
	// get around to creating the scoreboard class.
}

bool DancingPlutonium::Game::Quitting()
{
	return m_state == CurrentState::s_quit;
}