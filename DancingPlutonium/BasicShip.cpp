#pragma once

#include "GenericEnemyUnit.h"

class BasicShip : GenericEnemyUnit
{
public:
	BasicShip()
	{
		value = 50;
		health = 100;
		fireRate = 0.1f;
		fireDamage = 1;
		speed = 1.0f;
		isActive = true;
		SetSpriteImage();
	}

	virtual int GetValue() const override
	{
		return value;
	}

	virtual int GetHealth() const override
	{
		return health;
	}

	virtual float GetFireRate() const override
	{
		return fireRate;
	}

	virtual int GetFireDamage() const override
	{
		return fireDamage;
	}

	virtual float GetSpeed() const override
	{
		return speed;
	}

	virtual bool GetActiveState() const override
	{
		return isActive;
	}

	virtual sf::Sprite GetSprite() const override
	{
		return sprite;
	}

	virtual sf::Vector2f GetPosition() const override
	{
		return sprite.getPosition();
	}

	virtual void Draw(sf::RenderTarget& _rt) const override
	{
		_rt.draw(sprite);
	}

	virtual void SetPosition(const sf::Vector2f& _pos) override
	{
		sprite.setPosition(_pos);
	}

private:
	void SetSpriteImage()
	{
		texture.loadFromFile("Content/Images/BasicShip.png");
		sprite.setTexture(texture);
		sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
		sprite.setPosition(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	}
};