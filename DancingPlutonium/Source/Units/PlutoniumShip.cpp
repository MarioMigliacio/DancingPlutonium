#include "PlutoniumShip.h"

sf::Uint32 DancingPlutonium::PlutoniumShip::m_movement = Movement::s_noMovement;

DancingPlutonium::PlutoniumShip::PlutoniumShip(const sf::RenderTarget& _rt)
{
	lives = 3;
	bombs = 0;
	score = 0;
	health = 100;
	accumulator = 0.0f;
	speed = 175.0f;
	isActive = true;
	SetSprite(_rt);
	fireRate = 0.5;
	InitializeWeaponry(fireRate);
}

DancingPlutonium::PlutoniumShip::~PlutoniumShip()
{
	delete weapon;
}

int DancingPlutonium::PlutoniumShip::LivesRemaining() const
{
	return lives;
}

int DancingPlutonium::PlutoniumShip::GetScore() const
{
	return score;
}

void DancingPlutonium::PlutoniumShip::AddScore(const int _value)
{
	score += _value;
}

int DancingPlutonium::PlutoniumShip::GetHealth() const
{
	return health;
}

void DancingPlutonium::PlutoniumShip::ModifyHealth(const int _value)
{
	health += _value;
}

float DancingPlutonium::PlutoniumShip::GetFireRate() const
{
	return fireRate;
}

int DancingPlutonium::PlutoniumShip::GetFireDamage() const
{
	return fireDamage;
}

// is this really needed?
float DancingPlutonium::PlutoniumShip::GetSpeed() const
{
	return speed;
}

bool DancingPlutonium::PlutoniumShip::GetActiveState() const
{
	return isActive;
}

bool DancingPlutonium::PlutoniumShip::IsWithinBounds(const sf::RenderTarget& _rt)
{
	auto us = sprite.getGlobalBounds();
	auto getRect = sf::FloatRect(us.width, us.height, _rt.getSize().x - 2.0f * us.width, _rt.getSize().y - 2.0f * us.height);

	if (getRect.intersects(us))
	{
		return true;
	}

	return false;
}

void DancingPlutonium::PlutoniumShip::SetMovingState(bool _state)
{
	isMoving = _state;
}

sf::Sprite& DancingPlutonium::PlutoniumShip::GetSprite()
{
	return sprite;
}

sf::Vector2f DancingPlutonium::PlutoniumShip::GetPosition() const
{
	return sprite.getPosition();
}

sf::FloatRect DancingPlutonium::PlutoniumShip::GetBounds() const
{
	return sprite.getGlobalBounds();
}

sf::Uint32 DancingPlutonium::PlutoniumShip::GetWeaponState() const
{
	return weapon->GetPattern();
}

DancingPlutonium::Weapon* DancingPlutonium::PlutoniumShip::GetWeaponEquipped()
{
	return weapon;
}

void DancingPlutonium::PlutoniumShip::SetMoveState(const sf::Uint32 _state)
{
	m_movement = _state;
}

void DancingPlutonium::PlutoniumShip::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}

void DancingPlutonium::PlutoniumShip::Update(float _dt, sf::RenderTarget& _rt)
{
	accumulator += _dt;

	if (isActive)
	{
		// update movement
		if (isMoving)
		{
			if (InputManager::IsUsingBoost())
			{
				speed = 425.0f;
			}
			else
			{
				speed = 175.0f;
			}

			auto tempPosition = position;

			// perform bounds checking to make sure the player is within the render window limits before calling SetPosition().
			switch (m_movement)
			{
				case Movement::s_north:
						SetPosition(sf::Vector2f(position.x, position.y - speed * _dt));
					break;
				case Movement::s_east:
						SetPosition(sf::Vector2f(position.x + speed * _dt, position.y));
					break;
				case Movement::s_south:
						SetPosition(sf::Vector2f(position.x, position.y + speed * _dt));
					break;
				case Movement::s_west:
						SetPosition(sf::Vector2f(position.x - speed * _dt, position.y));
					break;
				case Movement::s_northWest:
						SetPosition(sf::Vector2f(position.x - speed * _dt, position.y - speed * _dt));
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x - speed * _dt, position.y));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x, position.y - speed * _dt));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
						}
					break;
				case Movement::s_northEast:
						SetPosition(sf::Vector2f(position.x + speed * _dt, position.y - speed * _dt));
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x + speed * _dt, position.y));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x, position.y - speed * _dt));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
						}
					break;
				case Movement::s_southEast:
						SetPosition(sf::Vector2f(position.x + speed * _dt, position.y + speed * _dt));
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x + speed * _dt, position.y));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x, position.y + speed * _dt));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
						}
					break;
				case Movement::s_southWest:
						SetPosition(sf::Vector2f(position.x - speed * _dt, position.y + speed * _dt));
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x - speed * _dt, position.y));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x, position.y + speed * _dt));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
						}
					break;
				default:
					break;				
			}

			if (!IsWithinBounds(_rt))
			{
				position = tempPosition;
			}
		}

		// update bullets
		if (InputManager::IsShooting())
		{
			Shoot(accumulator);
		}

		weapon->Update(_rt, _dt);
	}
}

void DancingPlutonium::PlutoniumShip::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(sprite);
	weapon->Draw(_rt);
}

void DancingPlutonium::PlutoniumShip::Shoot(const float _dt)
{
	if (weapon->AddMunition(sf::Vector2f(position.x + 3, position.y - texture.getSize().y / 2.0f), _dt))
	{
		accumulator = 0.0f;
	}
}

void DancingPlutonium::PlutoniumShip::CleanAmmunition(const sf::RenderTarget& _rt)
{
	if (ammunition.size() != 0)
	{
		for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
		{
			if (ammunition[i]->GetActiveState(_rt) == false)
			{
				delete ammunition[i];
				ammunition.erase(ammunition.begin() + i);
			}
		}
	}
}

void DancingPlutonium::PlutoniumShip::InitializeWeaponry(const float _fireRate)
{
	ammunition = std::vector<AbstractBaseProjectile*>();
	weapon = new Weapon(_fireRate, 1);
	//fireRate = 0.33f;
}

void DancingPlutonium::PlutoniumShip::SetSprite(const sf::RenderTarget& _rt)
{
	sf::Vector2f origin = sf::Vector2f(_rt.getSize().x / 2.0f, _rt.getSize().y - 16.0f);

	texture.loadFromFile("Content/Images/PlayerShip.png");
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.75f, 0.75f));
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(origin);
	position = origin;
}
