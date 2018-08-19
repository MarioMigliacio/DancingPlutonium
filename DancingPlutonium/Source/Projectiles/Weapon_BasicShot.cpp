#include "Weapon_BasicShot.h"

DancingPlutonium::Weapon_BasicShot::Weapon_BasicShot(const sf::Vector2f& _pos)
{
	position = _pos;
	speed = defaultSpeed;
	SetSprite(position);
	innert = false;
	damage = defaultDamage;
}

DancingPlutonium::Weapon_BasicShot::Weapon_BasicShot(const sf::Vector2f& _pos, const float& _dmg, const float& _vel, const short& _alle)
{
	position = _pos;
	speed = _vel * defaultSpeed;
	SetSprite(position);
	innert = false;
	damage = defaultDamage * _dmg;
	allegiance = _alle;
}

void DancingPlutonium::Weapon_BasicShot::SetSprite(const sf::Vector2f& _origin)
{
	texture.loadFromFile("Content/Images/BulletBlue.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(_origin);
	position = _origin;
}

void DancingPlutonium::Weapon_BasicShot::Update(float _dt)
{
	if (!innert)
	{
		SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y - _dt * speed * allegiance));
	}
}

void DancingPlutonium::Weapon_BasicShot::Draw(sf::RenderTarget& _rt)
{
	if (!innert)
	{
		_rt.draw(sprite);
	}
}

bool DancingPlutonium::Weapon_BasicShot::GetActiveState(const sf::RenderTarget& _rt)
{
	if (sprite.getPosition().y < 0 || sprite.getPosition().x < 0 ||
		sprite.getPosition().y > _rt.getSize().y || sprite.getPosition().x > _rt.getSize().x)
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::vector<sf::Sprite> DancingPlutonium::Weapon_BasicShot::GetAllSprites()
{
	auto retVal = std::vector<sf::Sprite>();
	retVal.push_back(this->sprite);

	return retVal;
}

std::vector<DancingPlutonium::AbstractBaseProjectile*> DancingPlutonium::Weapon_BasicShot::GetAllComponentBullets()
{
	auto retVal = std::vector<AbstractBaseProjectile*>();

	retVal.push_back(this);

	return retVal;
}
