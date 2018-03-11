#pragma once

#include "BasicShip.h"

DancingPlutonium::BasicShip::BasicShip(const sf::RenderTarget& _rt)
{
	name = "BasicShip";
	value = 50;
	health = 100;
	fireRate = 1.25f;
	fireDamage = 10;
	speed = 1.0f;
	isActive = true;
	SetSprite();
	SetBulletPatterns();
	SetPosition(sf::Vector2f(16.0f, 16.0f));
}

void DancingPlutonium::BasicShip::SetSprite()
{
	sf::Vector2f origin = sf::Vector2f(16.0f, 16.0f);

	texture.loadFromFile("Content/Images/BasicShip.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(origin);
	position = origin;
}

void DancingPlutonium::BasicShip::SetBulletPatterns()
{
	bulletPatterns.push_back(BulletPattern::Pattern::s_enemyStandard);
}

void DancingPlutonium::BasicShip::ShootBullet()
{
}

