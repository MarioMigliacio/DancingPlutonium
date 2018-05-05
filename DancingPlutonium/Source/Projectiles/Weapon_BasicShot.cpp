#include "Weapon_BasicShot.h"

DancingPlutonium::Weapon_BasicShot::Weapon_BasicShot(const sf::Vector2f& _pos)
{
	position = _pos;
	speed = 200.0f;
	SetSprite(position);
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
	SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y - _dt * speed * allegiance));
}

void DancingPlutonium::Weapon_BasicShot::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(sprite);
}

std::vector<sf::FloatRect> DancingPlutonium::Weapon_BasicShot::GetBounds()
{
	auto basicBounds = sprite.getGlobalBounds();
	std::vector<sf::FloatRect> retVal = std::vector<sf::FloatRect>();
	retVal.push_back(basicBounds);

	return retVal;
}

