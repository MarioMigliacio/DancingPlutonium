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

void DancingPlutonium::PlutoniumShip::Update(float dt)
{
	if (isActive)
	{
		if (isMoving)
		{
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
					break;
				case Movement::s_northEast:
					SetPosition(sf::Vector2f(position.x + speed * dt, position.y - speed * dt));
					break;
				case Movement::s_southEast:
					SetPosition(sf::Vector2f(position.x + speed * dt, position.y + speed * dt));
					break;
				case Movement::s_southWest:
					SetPosition(sf::Vector2f(position.x - speed * dt, position.y + speed * dt));
					break;
				default:
					break;
			}
		}
	}
}

void DancingPlutonium::PlutoniumShip::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(sprite);
}

void DancingPlutonium::PlutoniumShip::Shoot()
{
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
	sf::Vector2f origin = sf::Vector2f(_rt.getSize().x / 2.0f, _rt.getSize().y - 32.0f);

	texture.loadFromFile("Content/Images/PlayerShip.png");
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.75f, 0.75f));
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(origin);
	position = origin;
}
