#pragma once

#include "GenericEnemyUnit.h"

class BasicShip : public GenericEnemyUnit
{
public:
	BasicShip(const sf::RenderTarget& _rt);
	BasicShip(const BasicShip& _ref) {}
	~BasicShip() {}

	// Inherited via GenericEnemyUnit
	virtual void SetSprite() override;
	virtual void SetBulletPatterns() override;
	virtual void ShootBullet() override;
};