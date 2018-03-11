#include "PlutoniumShip.h"

// Static variable declarations:
sf::Uint32 DancingPlutonium::PlutoniumShip::m_weapon = s_uninitialized;

DancingPlutonium::PlutoniumShip::PlutoniumShip(const sf::RenderTarget& _rt)
{
	lives = 3;
	bombs = 0;
	score = 0;
	health = 100;
	speed = 5.0f;
	isActive = true;
	InitializeWeaponry();
	SetSprite(_rt);
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

float DancingPlutonium::PlutoniumShip::GetSpeed() const
{
	return speed;
}

bool DancingPlutonium::PlutoniumShip::GetActiveState() const
{
	return isActive;
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

sf::Uint32 DancingPlutonium::PlutoniumShip::getWeaponState() const
{
	return m_weapon;
}

void DancingPlutonium::PlutoniumShip::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}

void DancingPlutonium::PlutoniumShip::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(sprite);
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
