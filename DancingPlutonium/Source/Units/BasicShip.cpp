#pragma once

#include "BasicShip.h"

DancingPlutonium::BasicShip::BasicShip(const sf::RenderTarget& _rt)
{
	value = 50;
	health = 100;
	fireRate = 1.25f;
	damageMultiplier = 10;
	speed = 1.0f;
	isActive = true;
	SetSprite();
}

void DancingPlutonium::BasicShip::SetSprite()
{
	texture.loadFromFile("Content/Images/BasicShip.png");
	auto width = texture.getSize().x;
	auto height = texture.getSize().y;
	sf::Vector2f origin = sf::Vector2f(width / 2.0f, height / 2.0f);
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(origin);
	position = origin;
	SetPosition(origin);
	auto getRect = GetBounds();
}

void DancingPlutonium::BasicShip::ShootBullet()
{
}

// TODO this stuff maybe some day
void DancingPlutonium::BasicShip::Update(float _dt)
{
}

