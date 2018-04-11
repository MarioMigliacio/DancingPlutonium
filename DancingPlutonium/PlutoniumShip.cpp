#include "PlutoniumShip.h"

// Static variable declarations:
sf::Uint32 DancingPlutonium::PlutoniumShip::m_weapon = s_uninitialized;
sf::Uint32 DancingPlutonium::PlutoniumShip::m_movement = s_noMovement;

DancingPlutonium::PlutoniumShip::PlutoniumShip(const sf::RenderTarget& _rt)
{
	lives = 3;
	bombs = 0;
	score = 0;
	health = 100;
	accumulator = 0.0f;
	speed = 100.0f;
	isActive = true;
	InitializeWeaponry();
	SetSprite(_rt);
	ammunition = std::vector<Bullet*>();
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

//TODO: when finished with projectile classes, use a pointer to a basic bullet and figure out based on factory types.
// idk, maybe enum is appropriate. Need to discuss this.
void DancingPlutonium::PlutoniumShip::UpgradeWeapon()
{
	switch (m_weapon)
	{
		case WeaponState::s_uninitialized: 
			m_weapon = WeaponState::s_basic;
			fireDamage = 15;
			fireRate = 0.33f; 
			break;
		case WeaponState::s_basic:
			m_weapon = WeaponState::s_sidecannons;
			fireDamage = 25;
			fireRate = 0.33f;
			break;
		case WeaponState::s_sidecannons: 
			m_weapon = WeaponState::s_lazerstream; 
			fireDamage = 25;
			fireRate = 0.25f;
			break;
		case WeaponState::s_lazerstream:
			m_weapon = WeaponState::s_widelazer; 
			fireDamage = 35;
			fireRate = 0.25f;
			break;
		case WeaponState::s_widelazer: 
			m_weapon = WeaponState::s_homing; 
			fireDamage = 40;
			fireRate = 0.175f;
			break;
		default: break;
	}

	return;
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
	if (position.y > texture.getSize().y / 2.0f - 4.0f && (position.y <= _rt.getSize().y - texture.getSize().y / 2.0f) &&
		position.x > texture.getSize().x / 2.0f - 4.0f && (position.x <= _rt.getSize().x - texture.getSize().x / 2.0f))
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
	return m_weapon;
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

void DancingPlutonium::PlutoniumShip::Update(float dt, const sf::RenderTarget& _rt)
{
	accumulator += dt;

	if (isActive)
	{
		// update movement
		if (isMoving)
		{
			if (InputManager::IsUsingBoost())
			{
				speed = 300.0f;
			}
			else
			{
				speed = 100.0f;
			}

			auto tempPosition = position;

			// perform bounds checking to make sure the player is within the render window limits before calling SetPosition().
			switch (m_movement)
			{
				case Movement::s_north:
						SetPosition(sf::Vector2f(position.x, position.y - speed * dt));
					break;
				case Movement::s_east:
						SetPosition(sf::Vector2f(position.x + speed * dt, position.y));
					break;
				case Movement::s_south:
						SetPosition(sf::Vector2f(position.x, position.y + speed * dt));
					break;
				case Movement::s_west:
						SetPosition(sf::Vector2f(position.x - speed * dt, position.y));
					break;
				case Movement::s_northWest:
						SetPosition(sf::Vector2f(position.x - speed * dt, position.y - speed * dt));
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x - speed * dt, position.y));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x, position.y - speed * dt));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
						}
					break;
				case Movement::s_northEast:
						SetPosition(sf::Vector2f(position.x + speed * dt, position.y - speed * dt));
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x + speed * dt, position.y));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x, position.y - speed * dt));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
						}
					break;
				case Movement::s_southEast:
						SetPosition(sf::Vector2f(position.x + speed * dt, position.y + speed * dt));
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x + speed * dt, position.y));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x, position.y + speed * dt));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
						}
					break;
				case Movement::s_southWest:
						SetPosition(sf::Vector2f(position.x - speed * dt, position.y + speed * dt));
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x - speed * dt, position.y));
						}
						if (!IsWithinBounds(_rt))
						{
							SetPosition(tempPosition);
							SetPosition(sf::Vector2f(position.x, position.y + speed * dt));
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
			if (accumulator >= fireRate)
			{
				Shoot(_rt);
				accumulator = 0.0f;
			}
		}

		if (ammunition.size() != 0)
		{
			CleanAmmunition(_rt);

			for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
			{
				ammunition[i]->Update(dt);
			}
		}
	}
}

void DancingPlutonium::PlutoniumShip::Draw(sf::RenderTarget& _rt)
{
	// draw our ship
	_rt.draw(sprite);

	// draw our projectiles
	for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
	{
		ammunition[i]->Draw(_rt);
	}
}

void DancingPlutonium::PlutoniumShip::Shoot(const sf::RenderTarget& _rt)
{
	switch (m_weapon)
	{
		case WeaponState::s_basic:
			//ammunition.push_back(new BasicBulletPlayer(_rt, sf::Vector2f(position.x + 3, position.y - texture.getSize().y / 2.0f)));
			ammunition.push_back(new TripleBulletPlayer(_rt, sf::Vector2f(position.x + 3, position.y - texture.getSize().y / 2.0f)));
		break;
	default:
		break;
	}
}

void DancingPlutonium::PlutoniumShip::CleanAmmunition(const sf::RenderTarget & _rt)
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

void DancingPlutonium::PlutoniumShip::InitializeWeaponry()
{
	if (m_weapon == WeaponState::s_uninitialized)
	{
		m_weapon = WeaponState::s_basic;
		fireDamage = 15;
		fireRate = 0.33f;
	}
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
