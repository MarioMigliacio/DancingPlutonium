#include "Weapon_GrowingShot.h"

DancingPlutonium::Weapon_GrowingShot::Weapon_GrowingShot(const sf::Vector2f& _pos)
{
	position = _pos;
	speed = 175.0f;
	SetSprite(position);
}

void DancingPlutonium::Weapon_GrowingShot::SetSprite(const sf::Vector2f& _origin)
{
	texture.loadFromFile("Content/Images/BulletRed.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(_origin);
	position = _origin;
}

void DancingPlutonium::Weapon_GrowingShot::Update(float _dt)
{
	sprite.setScale(sf::Vector2f(sprite.getScale().x + _dt * 2.0f, sprite.getScale().y + _dt * 2.0f));
	SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y - _dt * speed * allegiance));
}

void DancingPlutonium::Weapon_GrowingShot::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(sprite);
}

std::vector<sf::FloatRect> DancingPlutonium::Weapon_GrowingShot::GetBounds()
{
	auto growingBounds = sprite.getGlobalBounds();
	std::vector<sf::FloatRect> retVal = std::vector<sf::FloatRect>();
	retVal.push_back(growingBounds);

	return retVal;
}

bool DancingPlutonium::Weapon_GrowingShot::GetActiveState(const sf::RenderTarget& _rt)
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

std::vector<sf::Sprite> DancingPlutonium::Weapon_GrowingShot::GetAllSprites()
{
	auto thisguy = this->sprite;
	std::vector<sf::Sprite> retVal = std::vector<sf::Sprite>();
	retVal.push_back(thisguy);

	return retVal;
}

