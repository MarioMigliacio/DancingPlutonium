#pragma once

#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "AbstractBaseUnit.h"
#include "Enums.h"
#include "Weapon.h"

namespace DancingPlutonium
{
	/* PlutoniumShip represents the player in this game */
	class PlutoniumShip : public AbstractBaseUnit
	{
	public:
		#pragma region Ctor/Dtors

		/* PlutoniumShip constructor that accepts a RenderTarget as input parameter */
		PlutoniumShip(const sf::RenderTarget& _rt);
		/* PlutoniumShip copy constructor */
		PlutoniumShip(const PlutoniumShip& _ref) {}
		/* PlutoniumShip deconstructor */
		~PlutoniumShip();

		#pragma endregion

	public:
		#pragma region Public Methods

		/* Returns the amount lives remaining for this PlutoniumShip object */
		int LivesRemaining() const;
		/* Adds to the life count for this PlutoniumShip object */
		void AddLife();
		/* Minus one to the life count for this PlutoniumShip object */
		void RemoveLife();
		/* Add a bomb to our PlutoniumShip's bomb count */
		void AddBomb();
		/* Attempt to try to use a bomb */
		void ShootBomb();
		/* Returns the amount of bombs remaining for this PlutoniumShip object */
		int BombsRemaining() const;
		/* Returns the score the player has amassed for this PlutoniumShip object */
		int GetScore() const;
		/* Adds score to the this PlutoniumShip object based on the _value input parameter */
		void AddScore(const int _value);
		/* Returns true if this PlutoniumShip is within the bounds of the game window, false otherwise */
		bool IsWithinBounds(const sf::RenderTarget& _rt) override;
		/* Modifies this PlutoniumShip object's movement state based on _state input parameter*/
		void SetMovingState(bool _state);
		/* Allows access to this PlutoniumShip objects weapon pointer */
		Weapon* GetWeaponEquipped();
		/* Sets the movement state for this PlutoniumShip object based on the _state input parameter */
		void SetMoveState(const sf::Uint32 _state);
		/* Sets the position for this PlutoniumShip object based on the _pos input parameter */
		void SetPosition(const sf::Vector2f& _pos);
		/* Sets the health of this unit by subtracting the value of _val (behavior is different for regular units) */
		virtual void TakeDamage(const float _val) override;
		/* Update this PlutoniumShip in the world based on the clock and render winder input parameters */
		void Update(float dt, sf::RenderTarget& _rt);
		/* Draw this PlutoniumShip sprite onto the render window _rt */
		void Draw(sf::RenderTarget& _rt);
		/* Gets the sprite object for THIS unit. There was an issue with the abstract base class owning this method. */
		virtual sf::Sprite& GetSprite() override;
		/* Calls upon this unit to see if it can shoot */
		virtual bool CanShoot(const float & _dt) override;
		/* Calls upon this unit to Shoot a projectile */
		virtual AbstractBaseProjectile* Shoot() override;

		#pragma endregion

	private:
		#pragma region Private Methods

		/* Sets this PlutoniumShips sprite, texture and default position */
		void SetSprite(const sf::RenderTarget& _rt);

		#pragma endregion

	private:
		#pragma region Members

		float invulnerablePeriod;							/* Represents how long the player is allowed invulnerability */
		short bombs;										/* Represents the bombs count for this PlutoniumShip object */
		short lives;										/* Represents the lives count for this PlutoniumShip object */
		int score;											/* Represents the score for this PlutoniumShip object */
		bool isMoving;										/* Represents the isMoving state for this PlutoniumShip object */
		sf::String name;									/* Represents the name for this PlutoniumShip object */
		sf::Sprite sprite;									/* Represents the sprite for this PlutoniumShip object */
		sf::Texture texture;								/* Represents the texture for this PlutoniumShip object */
		sf::Vector2f position;								/* Represents the position for this PlutoniumShip object */
		Weapon* weapon;										/* Represents the weapon for this PlutoniumShip object */

		#pragma endregion
		
	private:
		static sf::Uint32 m_movement;						/* Static variable which maintains the state for this PlutoniumShips movement */
	};
}