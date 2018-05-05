#include "Playing.h"
#include <iostream>

// Static variable declarations:
sf::Uint32 DancingPlutonium::Playing::m_state = s_uninitialized;

//Playgrounds for testing
void DancingPlutonium::Playing::Show(sf::RenderWindow& _window)
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (m_state != PlayState::s_uninitialized)
	{
		return;
	}

	// Set the State:
	m_state = PlayState::s_playing;
	BasicShip* m_ship;
	m_ship = new BasicShip(_window);
	PlutoniumShip* me;
	me = new PlutoniumShip(_window);

	std::vector<AbstractBaseUnit*> enemyShips;
	std::vector<AbstractBaseProjectile*> alladembulletsMmHmm;
	std::vector<AbstractBaseProjectile*> allademeEnemybulletsMmHmm;
	enemyShips.push_back(m_ship);


	// Scale screens with different computer screen resolutions: (the standard resolution in place is 720p: 1280wide x 720high, 60 fps)
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();

	// Set up the background:
	sf::Texture bgTexture;
	bgTexture.loadFromFile("Content/Images/Space1.png");

	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setOrigin(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);
	bgSprite.setPosition(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);

	// Set up the Timers.
	sf::Clock clock;
	sf::Time dt;

	while (m_state == PlayState::s_playing)
	{
		sf::Event event;

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_state = PlayState::s_quit;
				return;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{	
				auto tempShip = new BasicShip(_window);
				tempShip->SpawnRandomly(_window);
				enemyShips.push_back(tempShip);
				//enemyShips[0]->SpawnRandomly(_window);
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LControl ||
				event.key.code == sf::Keyboard::RControl))
			{
				me->GetWeaponEquipped()->UpgradeWeaponPattern();
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LAlt ||
				event.key.code == sf::Keyboard::RAlt))
			{
				me->GetWeaponEquipped()->UpgradeWeaponFireRate();
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Up))
			{
				me->GetWeaponEquipped()->UpgradeWeaponVelocityRate();
			}
		}
		
		bool isPlayerMoving = InputManager::IsMoving();
		me->SetMovingState(isPlayerMoving);
		
		if (isPlayerMoving)
		{
			sf::Uint32 whichDirection = InputManager::GetDirection();
			me->SetMoveState(whichDirection);

			// this proves level has access to the coords of player and able to get bounding rectangle
			//auto playerRect = me->GetRect();
			//std::cout << " our rect bounds are at (L: " << playerRect.left << ", T: " << playerRect.top <<
			//	", W: " << playerRect.width << ", H: " << playerRect.height << std::endl;
		}
		
		dt = clock.restart();
		_window.clear();
		_window.draw(bgSprite);
		me->Update(dt.asSeconds(), _window);
		me->Draw(_window);

		
		// EXPERIMENT REGION BE WARNED
		//
		//
		// this would be a simple check for Unit to Unit collision.
		if (enemyShips.size() > 0)
		{
			sf::FloatRect npcRect = sf::FloatRect();

			// backwards iterator for vectors are more efficient, because the elements after the removed item are always shifted left and re-evaluate capacity.
			for (int i = static_cast<int>(enemyShips.size() - 1); i >= 0; i--)
			{
				if (enemyShips[i]->GetActiveState(_window))
				{
					enemyShips[i]->Update(dt.asSeconds(), _window);
					enemyShips[i]->Draw(_window);
					npcRect = enemyShips[i]->GetBounds();

					auto temp = me->GetRect();

					if (temp.intersects(npcRect))
					{
						// this is where you would trade damages, render objects innert for a time period. etc.
						std::cout << " You have crashed into an enemy ship! " << std::endl;
					}
				}
				else
				{
					std::cout << " ship " << i << " has been destroyed" << std::endl;
					delete enemyShips[i];
					enemyShips.erase(enemyShips.begin() + i);
				}
			}
		}

		alladembulletsMmHmm = me->GetWeaponEquipped()->GetAmmunitionContainer();
		std::vector<sf::FloatRect> playerBullet = std::vector<sf::FloatRect>();

		if (alladembulletsMmHmm.size() > 0)
		{
			for (int j = 0; j < static_cast<int>(alladembulletsMmHmm.size()); j++)
			{
				playerBullet = alladembulletsMmHmm[j]->GetBounds();

				if (playerBullet.size() > 0)
				{
					for (int k = 0; k < static_cast<int>(playerBullet.size()); k++)
					{
						std::cout << " Projectile HOT at (L: " << playerBullet[k].left << ", T: " << playerBullet[k].top <<
							", W: " << playerBullet[k].width << ", H: " << playerBullet[k].height << std::endl;
					}
				}				
			}
		}

		/*if (enemyShips.size() > 0)
		{
			sf::FloatRect npcRect = sf::FloatRect();
			sf::FloatRect playerBullet = sf::FloatRect();

			for (int i = 0; i < static_cast<int>(enemyShips.size()); i++)
			{
				if (alladembulletsMmHmm.size() > 0)
				{
					for (int j = 0; j < static_cast<int>(alladembulletsMmHmm.size()); j++)
					{
						playerBullet = alladembulletsMmHmm[j]->GetBounds();

						if (npcRect.intersects(playerBullet))
						{
							std::cout << " You have SHOT an enemy ship! " << std::endl;
						}
					}
				}
			}
		}*/

		_window.display();
	}
}
