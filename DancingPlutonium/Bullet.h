#pragma once

#include<SFML/Graphics.hpp>
#include "BulletPattern.h"

class Bullet
{
protected:
	float speed;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	BulletPattern::Angle angle;
	BulletPattern::Pattern pattern;
	
public:
	Bullet() {}
	Bullet(sf::RenderTarget& _rt, sf::Vector2f& _pos);
	Bullet(const Bullet& _ref) {}
	~Bullet() {}

	float GetSpeed() const;
	bool GetActiveState(const sf::RenderTarget& _rt) const;
	virtual sf::Sprite& GetSprite();
	virtual sf::FloatRect GetBounds() const;
	virtual sf::Vector2f GetPosition() const;
	
	virtual void SetPosition(const sf::Vector2f& _pos);

	virtual void Update(float _dt);
	virtual void Draw(sf::RenderTarget& _rt) const;

	virtual void SetSprite(const sf::Vector2f& _origin) = 0;
};