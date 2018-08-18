#include "PlutoniumShip.h"
#include <iostream>

sf::Uint32 DancingPlutonium::PlutoniumShip::m_movement = Movement::s_noMovement;

DancingPlutonium::PlutoniumShip::PlutoniumShip(const sf::RenderTarget& _rt) : AbstractBaseUnit(), lives(3),
	invulnerablePeriod(0.0f),
	bombs(0),
	score(0)
	
{
	health = 200.0f;
	speed = 175.0f;	
	isActive = true;
	isInvulnerable = false;
	allegiance = 1;
	SetSprite(_rt);
	fireRate = 0.5f;
	weapon = new Weapon(fireRate, allegiance);
}

DancingPlutonium::PlutoniumShip::~PlutoniumShip()
{
	delete weapon;
}

int DancingPlutonium::PlutoniumShip::LivesRemaining() const
{
	return lives;
}

void DancingPlutonium::PlutoniumShip::AddLife()
{
	lives++;
}

void DancingPlutonium::PlutoniumShip::RemoveLife()
{
	if (lives > 0)
	{
		lives--;
		health = 200.f;

		if (!isInvulnerable)
		{
			ToggleInvulnerability();
		}
	}
	else
	{
		isActive = false;
	}
}

int DancingPlutonium::PlutoniumShip::GetScore() const
{
	return score;
}

void DancingPlutonium::PlutoniumShip::AddScore(const int _value)
{
	score += _value;
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

void DancingPlutonium::PlutoniumShip::TakeDamage(const float _val)
{
	if (!isInvulnerable)
	{
		health -= _val;
	}
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

		if (InputManager::IsShooting())
		{
			if (CanShoot(accumulator) && !IsFiringBullet())
			{
				// remember that the LevelObserver needs to do the same operation, toggleFiring needs to flip or we'll never be able to shoot again!
				ToggleFiring();
				accumulator = 0.0f;
			}
		}

		// go blinky blinky! (get around to it eventually)
		if (isInvulnerable)
		{
			invulnerablePeriod += _dt;

			if (invulnerablePeriod >= 1.5f)
			{
				ToggleInvulnerability();

				invulnerablePeriod = 0.0f;
			}
		}
	}
}

void DancingPlutonium::PlutoniumShip::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(sprite);
}

void DancingPlutonium::PlutoniumShip::SetSprite(const sf::RenderTarget& _rt)
{
	texture.loadFromFile("Content/Images/PlayerShip.png");
	sprite.setTexture(texture);

	auto width = sprite.getGlobalBounds();
	sf::Vector2f origin = sf::Vector2f(_rt.getSize().x / 2.0f, _rt.getSize().y - width.width / 2.0f);

	sprite.setScale(sf::Vector2f(0.75f, 0.75f));
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(origin);
	position = origin;
}

bool DancingPlutonium::PlutoniumShip::CanShoot(const float & _dt)
{
	return weapon->CanShoot(_dt);
}

DancingPlutonium::AbstractBaseProjectile* DancingPlutonium::PlutoniumShip::Shoot()
{
	auto retVal = weapon->SpawnBullet(position);

	return retVal;
}

sf::Sprite& DancingPlutonium::PlutoniumShip::GetSprite()
{
	return this->sprite;
}
