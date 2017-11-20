#include "BasicBullet.h"

BasicBullet::BasicBullet(const sf::RenderTarget& _rt, const sf::Vector2f& _origin)
{
	velocity = 0.5f;
	SetSprite(_origin);
}

float BasicBullet::GetSpeed() const
{
	return velocity;
}

bool BasicBullet::GetActiveState() const
{
	if (sprite.getPosition().y < 0)
	{
		return false;
	}

	return true;
}

sf::Sprite& BasicBullet::GetSprite()
{
	return sprite;
}

sf::Vector2f BasicBullet::GetPosition() const
{
	return sprite.getPosition();
}

sf::FloatRect BasicBullet::GetBounds() const
{
	return sprite.getGlobalBounds();
}

void BasicBullet::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}

void BasicBullet::Draw(sf::RenderTarget& _rt)
{
	if (GetActiveState())
	{
		_rt.draw(sprite);
	}
}

void BasicBullet::SetSprite(const sf::Vector2f& _origin)
{
	texture.loadFromFile("Content/Images/BulletBlue.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(_origin);
	position = _origin;
}
