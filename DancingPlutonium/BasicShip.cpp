#pragma once

#include "BasicShip.h"

// OLD!
//BasicShip::BasicShip(const sf::RenderTarget& _rt)
//{
//	value = 50;
//	health = 100;
//	fireRate = 1.25f;
//	fireDamage = 10;
//	speed = 1.0f;
//	isActive = true;
//	SetSpriteImage();
//	//EmplaceRandomly(_rt);
//	//SetPosition(sf::Vector2f(16.0f, 16.0f));
//}
//
//int BasicShip::GetValue() const
//{
//	return value;
//}
//
//int BasicShip::GetHealth() const
//{
//	return health;
//}
//
//float BasicShip::GetFireRate() const
//{
//	return fireRate;
//}
//
//int BasicShip::GetFireDamage() const
//{
//	return fireDamage;
//}
//
//float BasicShip::GetSpeed() const
//{
//	return speed;
//}
//
//bool BasicShip::GetActiveState() const
//{
//	return isActive;
//}
//
//sf::Sprite& BasicShip::GetSprite()
//{
//	return sprite;
//}
//
//sf::Vector2f BasicShip::GetPosition() const
//{
//	return sprite.getPosition();
//}
//
//sf::FloatRect BasicShip::GetBounds() const
//{
//	return sprite.getGlobalBounds();
//}
//
//void BasicShip::SetPosition(const sf::Vector2f& _pos)
//{
//	position = _pos;
//	sprite.setPosition(_pos);
//}
//
//void BasicShip::Draw(sf::RenderTarget& _rt)
//{
//	_rt.draw(sprite);
//}
//
//void BasicShip::EmplaceRandomly(const sf::RenderTarget& _rt)
//{
//	int randomX = _rt.getSize().x - sprite.getGlobalBounds().width / 2.0f;
//	randomX = RandomIntRange(sprite.getGlobalBounds().width / 2.0f, randomX) % randomX;
//
//	SetPosition(sf::Vector2f((float)randomX, 16.0f));
//}
//
//void BasicShip::SetSpriteImage()
//{
//	auto origin = sf::Vector2f(16.0f, 16.0f);
//
//	texture.loadFromFile("Content/Images/BasicShip.png");
//	sprite.setTexture(texture);		
//	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
//	sprite.setPosition(origin);
//	position = origin;
//}
//
//void BasicShip::SetSprite()
//{
//}
//
//void BasicShip::SetBulletPatterns()
//{
//}
//
//void BasicShip::ShootBullet()
//{
//}

BasicShip::BasicShip(const sf::RenderTarget & _rt)
{
}

void BasicShip::SetSpriteImage()
{
}

void BasicShip::SetSprite()
{
}

void BasicShip::SetBulletPatterns()
{
}

void BasicShip::ShootBullet()
{
}
