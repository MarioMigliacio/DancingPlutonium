#pragma once

#include<SFML/Graphics.hpp>
#include "Bullet.h"

class BasicBullet : public Bullet
{
	//FIX
public:
	BasicBullet(const sf::RenderTarget& _rt, const sf::Vector2f& _origin);
	BasicBullet(const BasicBullet& _ref) {}
	~BasicBullet() {}

	// Inherited via Bullet
	virtual void SetSprite(const sf::Vector2f & _origin) override;
};
