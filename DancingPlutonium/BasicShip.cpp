#include "GenericEnemyUnit.h"

class BasicShip : GenericEnemyUnit
{
	BasicShip()
	{
		value = 50;
		health = 100;
		fireRate = 0.1f;
		fireDamage = 1;
		isActive = true;
		SetSpriteImage();
		SetDefaultPosition();
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

private:
	sf::Sprite SetSpriteImage()
	{
		texture.loadFromFile("Content/Images/BasicShip.png");
		sprite.setTexture(texture);
	}

	sf::Vector2f SetDefaultPosition()
	{
		sprite.setPosition(0.0f, 0.0f);
	}
};