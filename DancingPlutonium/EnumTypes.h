#pragma once

#define RES1080P sf::VideoMode(1920, 1080)

enum GameState
{
	MainMenu,
	Options,
	ScoreBoard,
	Level1,
	Level2,
	Level3
};

enum GameDifficulty
{
	Easy,
	Medium,
	Hard
};