#include "MainMenu.h"

Menu::Menu(sf::RenderWindow& window)
{
	LoadBackground();
	LoadMusic();
	InitializeButtons(window);
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
	window.draw(backSprite);


	window.draw(welcomeButton.getAsText(), states);
	//playButton.Draw(window);
	//optionsButton.Draw(window);
	//scoreButton.Draw(window);
}

void Menu::Update(float dt)
{
	welcomeButton.Update(dt);
	playButton.Update(dt);
	optionsButton.Update(dt);
	scoreButton.Update(dt);
}

void Menu::LoadBackground()
{
	backTexture.loadFromFile("Content/Images/TitleBackground.jpg");

	backSprite = sf::Sprite(backTexture);
}

void Menu::LoadMusic()
{
	music.openFromFile("Content/Sounds/RootMenu.wav");

	music.setLoop(true);
	music.play();
}

void Menu::InitializeButtons(sf::RenderWindow& window)
{
	welcomeButton = Button("Welcome To Dancing Plutonium", sf::Color::Red, sf::Color::Blue);
	playButton = Button("Play", sf::Color::Yellow, sf::Color::Blue);
	optionsButton = Button("Options", sf::Color::Yellow, sf::Color::Blue);
	scoreButton = Button("ScoreBoard", sf::Color::Yellow, sf::Color::Blue);

	welcomeButton.setPosition(sf::Vector2f((float)window.getSize().x / 2 - welcomeButton.getBounds().width / 2, (float)window.getSize().y / 10 - welcomeButton.getBounds().height / 2));
	playButton.setPosition(sf::Vector2f((float)window.getSize().x / 2 - playButton.getBounds().width / 2, (float)window.getSize().y / 4 - playButton.getBounds().height / 2));
	optionsButton.setPosition(sf::Vector2f((float)window.getSize().x - optionsButton.getBounds().width / 2, (float)window.getSize().y / 4 - optionsButton.getBounds().height / 2 + 85));
	scoreButton.setPosition(sf::Vector2f((float)window.getSize().x / 2 - scoreButton.getBounds().width / 2, (float)window.getSize().y / 4 - scoreButton.getBounds().height / 2 + 170));

	buttonContainer.push_back(welcomeButton);
	buttonContainer.push_back(playButton);
	buttonContainer.push_back(optionsButton);
	buttonContainer.push_back(scoreButton);
}

std::vector<Button> Menu::getButtons() const
{
	return buttonContainer;
}
