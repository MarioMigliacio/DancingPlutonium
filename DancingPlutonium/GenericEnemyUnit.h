#pragma once

#include<SFML/Graphics.hpp>
#include "IRng.h"

class GenericEnemyUnit
{
protected:
	int value;
	int health;	
	float fireRate;
	int fireDamage;
	float speed;
	bool isActive;
	sf::String name;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	
public:	
	virtual int GetValue() const = 0;
	virtual int GetHealth() const = 0;
	virtual float GetFireRate() const = 0;
	virtual int GetFireDamage() const = 0;
	virtual float GetSpeed() const = 0;
	virtual bool GetActiveState() const = 0;
	virtual sf::Sprite& GetSprite() = 0;
	virtual sf::Vector2f GetPosition() const = 0;
	virtual sf::FloatRect GetBounds() const = 0;
	virtual void SetPosition(const sf::Vector2f& _pos) = 0;
	virtual void Draw(sf::RenderTarget& _rt) = 0;
	virtual void EmplaceRandomly(const sf::RenderTarget& _rt) = 0;
};
