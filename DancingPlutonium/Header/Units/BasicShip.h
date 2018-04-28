#pragma once

#include "GenericEnemyUnit.h"

namespace DancingPlutonium
{
	/* BasicShip class is the most basic stage enemy object which has a very simple behavior */
	class BasicShip : public GenericEnemyUnit
	{
	public:
		#pragma region Ctor/Dtors

		/* BasicShip constructor accepting a rendertarget input parameter */
		BasicShip(const sf::RenderTarget& _rt);
		/* BasicShip copy constructor */
		BasicShip(const BasicShip& _ref) {}
		/* BasicShip destructor */
		~BasicShip() {}

		#pragma endregion

		#pragma region Methods

		/* Sets this ships sprite, texture and default position */
		virtual void SetSprite() override;
		/* Activate a projectile that spawns from this ship */
		virtual void ShootBullet() override;
		/* Updates this unit in the world */
		virtual void Update(float _dt) override;

		#pragma endregion
	};
}