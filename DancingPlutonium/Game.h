#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

class Game
{
public:
	Game() {}
	~Game() {}

	static void Initialize();

private:
	static void Run();
	static void Menu();
	static void Play();
	static void WinLevel();
	static void GameOver();
	static void Options();
	static void ScoreScreen();
	static bool Quitting();

private:
	enum current_state
	{
		s_uninitialized,
		s_menu,
		s_playing,
		s_options,
		s_scoreboard,
		s_levelwin,
		s_gameover,
		s_quit
	};

private:
	static sf::RenderWindow m_window;
	static sf::Uint32 m_state;
};