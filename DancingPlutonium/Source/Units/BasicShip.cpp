#pragma once

#include "BasicShip.h"
#include <iostream>

DancingPlutonium::BasicShip::BasicShip(const sf::RenderTarget& _rt)
{
	value = 50.0f;
	health = 100.0f;
	fireRate = 1.25f;
	damageMultiplier = 10.0f;
	accumulator = 0.0f;
	speed = 50.0f;
	isActive = true;
	SetSprite();
	InitializeWeaponry();
}

DancingPlutonium::BasicShip::~BasicShip()
{
	delete weapon;
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
}

void DancingPlutonium::BasicShip::ShootBullet(float _dt)
{
	if (weapon->AddMunition(sf::Vector2f(position.x + 3, position.y - texture.getSize().y / 2.0f), _dt))
	{
		accumulator = 0.0f;
	}
}

// TODO this stuff maybe some day
void DancingPlutonium::BasicShip::Update(float _dt, sf::RenderTarget& _rt)
{
	accumulator += _dt;

	if (GetActiveState(_rt))
	{
		SetPosition(sf::Vector2f(position.x, position.y + speed * _dt));
		ShootBullet(accumulator);
		weapon->Update(_rt, _dt);
	}
}

void DancingPlutonium::BasicShip::InitializeWeaponry()
{
	ammunition = std::vector<AbstractBaseProjectile*>();
	weapon = new Weapon(fireRate, -1);
}

