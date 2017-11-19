#pragma once

#include "GenericEnemyUnit.h"

class BasicShip : GenericEnemyUnit
{
public:
	BasicShip(const sf::RenderTarget& _rt);
	~BasicShip() {}

private:	
	void SetSpriteImage();
};