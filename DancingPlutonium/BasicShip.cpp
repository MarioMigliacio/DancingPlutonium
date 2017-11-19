#pragma once

#include "GenericEnemyUnit.h"

class BasicShip : GenericEnemyUnit
{
public:
	BasicShip(const sf::RenderTarget& _rt)
	{
		value = 50;
		health = 100;
		fireRate = 0.1f;
		fireDamage = 1;
		speed = 1.0f;
		isActive = true;
		SetSpriteImage();
		//EmplaceRandomly(_rt);
		//SetPosition(sf::Vector2f(16.0f, 16.0f));
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

	virtual sf::Sprite& GetSprite() override
	{
		return sprite;
	}

	virtual sf::Vector2f GetPosition() const override
	{
		return sprite.getPosition();
	}

	virtual sf::FloatRect GetBounds() const override
	{
		return sprite.getGlobalBounds();
	}

	virtual void SetPosition(const sf::Vector2f& _pos)
	{
		position = _pos;
		sprite.setPosition(_pos);
	}

	virtual void Draw(sf::RenderTarget& _rt) override
	{
		_rt.draw(sprite);
	}

	virtual void EmplaceRandomly(const sf::RenderTarget& _rt) override
	{
		int randomX = _rt.getSize().x - sprite.getGlobalBounds().width / 2.0f;
		randomX = RandomIntRange(sprite.getGlobalBounds().width / 2.0f, randomX) % randomX;

		SetPosition(sf::Vector2f((float)randomX, 16.0f));
	}

private:
	void SetSpriteImage()
	{
		auto origin = sf::Vector2f(16.0f, 16.0f);

		texture.loadFromFile("Content/Images/BasicShip.png");
		sprite.setTexture(texture);		
		sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
		sprite.setPosition(origin);
		position = origin;
	}
};