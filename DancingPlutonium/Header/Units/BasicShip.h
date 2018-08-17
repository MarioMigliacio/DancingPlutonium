#pragma once

#include "AbstractBaseUnit.h"

namespace DancingPlutonium
{
	/* BasicShip class is the most basic stage enemy object which has a very simple behavior */
	class BasicShip : public AbstractBaseUnit
	{
	public:
		#pragma region Ctor/Dtors

		/* BasicShip constructor accepting a rendertarget input parameter */
		BasicShip(const sf::RenderTarget& _rt);
		/* BasicShip copy constructor */
		BasicShip(const BasicShip& _ref) {}
		/* BasicShip destructor */
		~BasicShip();

		#pragma endregion

		#pragma region Methods

		/* Sets this ships sprite, texture and default position */
		virtual void SetSprite(const sf::RenderTarget& _rt) override;
		/* Updates this unit in the world */
		virtual void Update(float _dt, sf::RenderTarget& _rt) override;
		/* Gets the sprite for THIS object, not the base abstract unit. This was causing issues. */
		virtual sf::Sprite& GetSprite() override;
		// /* Calls upon this unit to see if it can shoot */
		virtual bool CanShoot(const float & _dt) override;
		/* Calls upon this unit to Shoot a projectile */
		virtual AbstractBaseProjectile* Shoot() override;

		#pragma endregion		
	};
}